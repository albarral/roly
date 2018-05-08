/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include <opencv2/core/core.hpp>
#include "log4cxx/ndc.h"

#include "roly/body/modules/ArmSense.h"
#include "roly/bodycore/config/BodyConfig.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr ArmSense::logger(Logger::getLogger("roly.body"));

ArmSense::ArmSense()
{
    modName = "ArmSense";
}

//ArmSense::~ArmSense()
//{
//}

void ArmSense::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}


void ArmSense::first()
{
    // config
    BodyConfig oBodyConfig;
    tolAngle = oBodyConfig.getAngleTolerance();
    tolRadius = oBodyConfig.getRadialTolerance();
    tiredTime = 0.0;
    periodSecs = (float)tron::Module3::getPeriod()/1000000.0;
    log4cxx::NDC::push(modName);   
}
                    
void ArmSense::loop()
{
    senseBus();
    
    // skip if module is inhibited
    if (binhibited)            
        return;
    
    senseArm();

    // if arm still & out of comfort zone, increase tired time
    if (!barmMoving && !bcomfortZone)
        tiredTime += periodSecs;
    // otherwise, reset tired time (better alternative? decrease tiredness)
    else
        tiredTime = 0.0;
    
    writeBus();
}

void ArmSense::senseBus()
{
    // check inhibited control
    binhibited = pBodyBus->getCO_INHIBIT_COMFORTABLE().isRequested();
    
    // check relax posture changes
    if (pBodyBus->getCO_RELAX_POSTURE().checkRequested())
    {
        cv::Vec3f value = pBodyBus->getCO_RELAX_POSTURE().getValue();
        relaxPosture[0] = value[0];    
        relaxPosture[1] = value[1];    
        relaxPosture[2] = value[2];    
        LOG4CXX_INFO(logger, modName << " new relax posture defined " + std::to_string(value[0]) + ", " + std::to_string(value[1]) + ", " + std::to_string(value[2]));                     
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

void ArmSense::senseArm()
{    
    // check if arm is moving (some axis speed not zero)
    barmMoving = (armSpeed[0] != 0.0 || armSpeed[1] != 0.0 || armSpeed[2] != 00);

    // if distance to arm's relax posture is inside a tolerance the arm is in the comfort zone
    bcomfortZone = (fabs(relaxPosture[0] - armPosture[0]) <= tolAngle && 
            fabs(relaxPosture[1] - armPosture[1]) <= tolAngle && 
            fabs(relaxPosture[2] - armPosture[2]) <= tolRadius);
}

void ArmSense::writeBus()
{
    // inform sensor outputs
    pBodyBus->getSO_ARM_MOVING().setValue(barmMoving);
    pBodyBus->getSO_ARM_COMFORT().setValue(bcomfortZone);
    pBodyBus->getSO_ARM_TIRED().setValue(tiredTime);
}
}