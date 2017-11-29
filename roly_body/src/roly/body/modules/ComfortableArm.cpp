/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "log4cxx/ndc.h"

#include "roly/body/modules/ComfortableArm.h"
#include "talky/topics/ArmTopic.h"


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
    maxTiredMillis = 3000;               // max allowed time for a motionless arm out of relax position
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
    showState();
}
                    
void ComfortableArm::loop()
{
    senseBus();
    
    // skip if module is inhibited
    if (binhibited)            
        return;

    checkComfortZone();
    checkArmMovement();
    
    switch (getState())
    {
        case eSTATE_RELAXED: 
            // if arm not in comfort zone -> OUT
            if (!bcomfortZone)
                setState(eSTATE_OUT);
            break;

        case eSTATE_OUT:            
            // if arm in comfort zone -> RELAXED
            if (bcomfortZone)
                setState(eSTATE_RELAXED);
            // if not in comfort zone & motionless -> TIRED (start timer)
            else if (!barmMoving)
            {
                oClickTired.start();
                setState(eSTATE_TIRED);                    
            }
            break;

        case eSTATE_TIRED:            
            // if arm in comfort zone -> RELAXED
            if (bcomfortZone)
                setState(eSTATE_RELAXED);
            else
            {
                // if moving -> back to OUT
                if (barmMoving)
                    setState(eSTATE_OUT);
                // if still motionless, check tired time
                else
                {
                    oClickTired.read();
                    // if tired time too much -> RELAX
                    if (oClickTired.getMillis() > maxTiredMillis)        
                        setState(eSTATE_RELAX);
                }
            }
            break;

        case eSTATE_RELAX:            
            // request relax posture -> OUT
            requestComfortPosture();
            setState(eSTATE_OUT);
            break;
    }  
    
    if (isStateChanged())
        showState();
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

void ComfortableArm::requestComfortPosture()
{
    // request arm relaxed posture
    nety::NetNodeClient& oAxisClient = pAmyTalker->getArmAxisClient();
    oAxisClient.addCommand(talky::ArmTopic::eAXIS_PAN_POS, relaxPosture[0]);
    oAxisClient.addCommand(talky::ArmTopic::eAXIS_TILT_POS, relaxPosture[1]);
    oAxisClient.addCommand(talky::ArmTopic::eAXIS_RAD_POS, relaxPosture[2]);
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
                        
        case eSTATE_OUT:
            LOG4CXX_INFO(logger, ">> out");
            break;

        case eSTATE_TIRED:
            LOG4CXX_INFO(logger, ">> tired");
            break;

        case eSTATE_RELAX:
            LOG4CXX_INFO(logger, ">> relax");
            break;
    }   // end switch    
}


}