/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "log4cxx/ndc.h"

#include "roly/body/modules/ComfortableArm.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr ComfortableArm::logger(Logger::getLogger("roly.body"));

ComfortableArm::ComfortableArm()
{
    modName = "Comfortable";
    // configuration, should be in BodyConfig object
    relaxPosture[0] = 10;            // relax posture (pan = 10, tilt = 20, radius = 40)
    relaxPosture[1] = 20; 
    relaxPosture[2] = 40; 
    tolAngle = 5.0;                      // allowed (pan, tilt) tolerance = 5 deg
    tolRadius = 5.0;                    // allowed radial tolerance =  5cm
    maxTiredMillis = 300;            // 0.3s for tired timeout
}

//ComfortableArm::~ComfortableArm()
//{
//}

void ComfortableArm::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}


void ComfortableArm::first()
{
    // start at relaxed state
    setState(eSTATE_RELAXED);    
    log4cxx::NDC::push(modName);   
}
                    
void ComfortableArm::loop()
{
    senseBus();
    
    // skip if module is inhibited
    if (binhibited)            
        return;

    if (isStateChanged())
        showState();
    
    checkComfortZone();
    checkArmMovement();
    
    switch (getState())
    {
        case eSTATE_RELAXED: 
            // if arm moving -> MOVING
            if (barmMoving)
                setState(eSTATE_MOVING);
            // if arm still & not in comfort -> STILL
            else if (!bcomfortZone)
                enterSTILL();
            break;

        case eSTATE_STILL:            
            // if arm moving -> MOVING
            if (barmMoving)
                setState(eSTATE_MOVING);
            // if arm still ...
            else
            {
                // and also in comfort -> RELAXED
                if (bcomfortZone)
                    setState(eSTATE_RELAXED);
                // and not in comfort 
                else
                {
                    // check tired time
                    oClickTired.read();
                    // if too tired -> TIRED
                    if (oClickTired.getMillis() > maxTiredMillis)        
                        setState(eSTATE_TIRED);
                }
            }
            break;

        case eSTATE_MOVING:            
            // if arm not moving -> STILL
            if (!barmMoving)
                enterSTILL();
            break;

        case eSTATE_TIRED:            
            // if arm moving -> MOVING
            if (barmMoving)
                setState(eSTATE_MOVING);
            // if arm still ...
            else
            {
                // check tired time
                oClickTired.read();
                // if too tired -> request relax posture
                if (oClickTired.getMillis() > maxTiredMillis)        
                    requestComfortPosture();
            }
            break;
    }  
    
    //writeBus();
}

void ComfortableArm::senseBus()
{
    // check inhibited control
    binhibited = pBodyBus->getCO_INHIBIT_COMFORTABLE().isRequested();
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

void ComfortableArm::enterSTILL()
{
    // reset tired time
    oClickTired.start();
    // and -> STILL
    setState(eSTATE_STILL);                    
}

void ComfortableArm::requestComfortPosture()
{
    // request arm relaxed posture
    oArmClient.setPan(relaxPosture[0]);
    oArmClient.setTilt(relaxPosture[1]);
    oArmClient.setRadial(relaxPosture[2]);
}

void ComfortableArm::checkComfortZone()
{    
    // if distance to arm's relax posture is inside a tolerance the arm is in the comfort zone
    bcomfortZone = (fabs(relaxPosture[0] - armPosture[0]) <= tolAngle && 
            fabs(relaxPosture[1] - armPosture[1]) <= tolAngle && 
            fabs(relaxPosture[2] - armPosture[2]) <= tolRadius);
}

void ComfortableArm::checkArmMovement()
{    
    // check if arm is moving (some axis speed not zero)
    barmMoving = (armSpeed[0] != 0.0 || armSpeed[1] != 0.0 || armSpeed[2] != 00);
}

void ComfortableArm::writeBus()
{
    // nothing to do here    
    // control already done by talk2arm())
}

void ComfortableArm::showState()
{
    switch (getState())
    {
        case eSTATE_RELAXED:
            LOG4CXX_INFO(logger, ">> relaxed");
            break;
                        
        case eSTATE_STILL:
            LOG4CXX_INFO(logger, ">> still");
            break;

        case eSTATE_MOVING:
            LOG4CXX_INFO(logger, ">> moving");
            break;

        case eSTATE_TIRED:
            LOG4CXX_INFO(logger, ">> tired");
            break;
    }   // end switch    
}


}