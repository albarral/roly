/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include <opencv2/core/core.hpp>
#include "log4cxx/ndc.h"

#include "roly/body/modules/ArmSense2.h"
#include "roly/bodycore/config/BodyConfig.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr ArmSense2::logger(Logger::getLogger("roly.body"));

ArmSense2::ArmSense2() : BodyBehaviour("ArmSense2")
{
    addStateName("ok");
    addStateName("tired");
}

//ArmSense2::~ArmSense2()
//{
//}



void ArmSense2::start()
{
    log4cxx::NDC::push(name);   
    LOG4CXX_INFO(logger, " initialized");          

    // config
    BodyConfig oBodyConfig;
    tolAngle = oBodyConfig.getAngleTolerance();
    tolRadius = oBodyConfig.getRadialTolerance();
    tiredTime = 0.0;

    // start at ok state
    setState(eSTATE_OK);    
    LOG4CXX_INFO(logger, ">> " << getStateName());          
}
                    
void ArmSense2::sense()
{
    // check inhibited control
    inhibit(pBodyBus->getCO_INHIBIT_COMFORTABLE().isRequested());
    
    // check relax posture changes
    if (pBodyBus->getCO_RELAX_POSTURE().checkRequested())
    {
        cv::Vec3f value = pBodyBus->getCO_RELAX_POSTURE().getValue();
        relaxPosture[0] = value[0];    
        relaxPosture[1] = value[1];    
        relaxPosture[2] = value[2];    
        LOG4CXX_INFO(logger, " new relax posture defined " + std::to_string(value[0]) + ", " + std::to_string(value[1]) + ", " + std::to_string(value[2]));                     
    }
    
    // sense arm posture
    armPosture[0] = pBodyBus->getSI_ARM_PAN().getValue();
    armPosture[1] = pBodyBus->getSI_ARM_TILT().getValue();
    armPosture[2] = pBodyBus->getSI_ARM_RADIUS().getValue();
    // sense arm speed
    armSpeed[0] = pBodyBus->getSI_ARM_PANSPEED().getValue(); 
    armSpeed[1] = pBodyBus->getSI_ARM_TILTSPEED().getValue();
    armSpeed[2] = pBodyBus->getSI_ARM_RADIALSPEED().getValue();
    //LOG4CXX_INFO(logger, pBodyBus->toString());    
}

void ArmSense2::actuate()
{
    // method skipped when behaviour inhibited
       
    // check if arm is moving (some axis speed not zero)
    barmMoving = (armSpeed[0] != 0.0 || armSpeed[1] != 0.0 || armSpeed[2] != 00);

    // checks if arm is in the comfort zone (near the relax posture)
    bcomfortZone = (fabs(relaxPosture[0] - armPosture[0]) <= tolAngle && 
            fabs(relaxPosture[1] - armPosture[1]) <= tolAngle && 
            fabs(relaxPosture[2] - armPosture[2]) <= tolRadius);

    switch (getState())
    {
        case eSTATE_OK:         
            
            // if arm not moving, but out of comfort zone -> TIRED
            if (!barmMoving && !bcomfortZone)
            {
                // reset tired time
                oClick.start();
                tiredTime = 0.0;
                setState(eSTATE_TIRED);
            }
            break;

        case eSTATE_TIRED:            

            // if arm moving again or in comfort zone -> OK
            if (barmMoving || bcomfortZone)
            {
                setState(eSTATE_OK);
                tiredTime = 0.0;
            }
            // if still tired
            else
            {
                // measure tired time
                oClick.read();
                tiredTime += (float)oClick.getMillis()/1000;
            }
                
            break;
    }  
    
    if (isStateChanged())
        LOG4CXX_INFO(logger, ">> " << getStateName());          
    
    writeBus();
}

void ArmSense2::writeBus()
{
    // inform sensor outputs
    pBodyBus->getSO_ARM_MOVING().setValue(barmMoving);
    pBodyBus->getSO_ARM_COMFORT().setValue(bcomfortZone);
    pBodyBus->getSO_ARM_TIRED().setValue(tiredTime);
}
}