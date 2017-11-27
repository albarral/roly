/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "log4cxx/ndc.h"

#include "roly/body/modules/Comfortable.h"
#include "talky/Talk2Target.h"
#include "talky/topics/ArmTopic.h"


using namespace log4cxx;

namespace roly
{
LoggerPtr Comfortable::logger(Logger::getLogger("roly.body"));

Comfortable::Comfortable()
{
    modName = "Comfortable";
    relaxPosture[0] = 10;            // relax posture (pan = 10, tilt = 20, radius = 40)
    relaxPosture[1] = 20; 
    relaxPosture[2] = 40; 
    tolAngle = 5.0;                                   // allowed (pan, tilt) tolerance = 5 deg
    tolRadius = 5.0;                               // allowed radial tolerance =  5cm
}

//Comfortable::~Comfortable()
//{
//}

void Comfortable::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}


void Comfortable::first()
{
    // start at IN
    setState(eSTATE_IN);    
    log4cxx::NDC::push(modName);   
    showState();
}
                    
void Comfortable::loop()
{
    senseBus();
    
    // skip if module is inhibited
    if (binhibited)            
        return;

    senseArm();
    // check if arm is in the relax position (with a tolerance)
    bool brelaxed = (dif[0] <= tolAngle && dif[1] <= tolAngle && dif[3] <= tolRadius);
    
    switch (getState())
    {
        case eSTATE_IN: 
            // if arm fixed and out of relax position
            if (!barmMoving && !brelaxed)
                setState(eSTATE_OUT);
            break;

        case eSTATE_OUT:            
            // send commands to arm & go to WAY
            talk2Arm();
            setState(eSTATE_WAY);
            break;

        case eSTATE_WAY:            
            // if relax position achieved, go to IN
            if (!barmMoving && brelaxed)
                setState(eSTATE_IN);
            // if arm fixed, go back to OUT
            else if (!barmMoving)
                setState(eSTATE_OUT);
            break;
    }   // end switch        
    
    if (isStateChanged())
        showState();
    //writeBus();
}

void Comfortable::senseBus()
{
    // check inhibited control
    binhibited = pBodyBus->getCO_INHIBIT_COMFORTABLE().isRequested();
}

void Comfortable::talk2Arm()
{
    // request arm posture
    nety::NetNodeClient& oAxisClient = pAmyTalker->getArmAxisClient();
    oAxisClient.addCommand(talky::ArmTopic::eAXIS_PAN_POS, relaxPosture[0]);
    oAxisClient.addCommand(talky::ArmTopic::eAXIS_TILT_POS, relaxPosture[1]);
    oAxisClient.addCommand(talky::ArmTopic::eAXIS_RAD_POS, relaxPosture[2]);
}

void Comfortable::senseArm()
{
    // sense arm posture
    armPosture[0] = pBodyBus->getSI_ARM_PAN().getValue();
    armPosture[1] = pBodyBus->getSI_ARM_TILT().getValue();
    armPosture[2] = pBodyBus->getSI_ARM_RADIUS().getValue();
    
    measureDistance();
    // check if arm is moving (some axis speed not zero)
    barmMoving = (pBodyBus->getSI_ARM_PANSPEED().getValue() != 0.0 || 
            pBodyBus->getSI_ARM_TILTSPEED().getValue() != 0.0 || 
            pBodyBus->getSI_ARM_RADIALSPEED().getValue() != 00);
}

void Comfortable::measureDistance()
{    
    dif[0] = fabs(relaxPosture[0] - armPosture[0]);
    dif[1] = fabs(relaxPosture[1] - armPosture[1]);
    dif[2] = fabs(relaxPosture[2] - armPosture[2]);
}


void Comfortable::writeBus()
{
    // nothing to do here    
    // control already done by talk2arm())
}

void Comfortable::showState()
{
    switch (getState())
    {
        case eSTATE_IN:
            LOG4CXX_INFO(logger, ">> in");
            break;
                        
        case eSTATE_OUT:
            LOG4CXX_INFO(logger, ">> out");
            break;

        case eSTATE_WAY:
            LOG4CXX_INFO(logger, ">> way");
            break;
    }   // end switch    
}


}