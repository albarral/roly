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

    readFromArm();
    measureDistance();
    // check if arm is in the relax position (with a tolerance)
    bool brelaxed = (dif[0] <= tolAngle && dif[1] <= tolAngle && dif[3] <= tolRadius);
    
    switch (getState())
    {
        case eSTATE_IN: 
            // if out of relax position
            if (!brelaxed)
                setState(eSTATE_OUT);
            break;

        case eSTATE_OUT:            
            // send commands to arm & go to WAY
            talk2Arm();
            setState(eSTATE_WAY);
            break;

        case eSTATE_WAY:            
            // if relax position achieved, go to IN
            if (brelaxed)
                setState(eSTATE_IN);
            // if not approaching to relax position, go back to OUT
            else if (dif[0] >= dif0[0] || dif[1] >= dif0[1] || dif[2] >= dif0[2])
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
    talky::Talk2Target& oTalk2ArmAxes = pBodyTalk->getTalk2ArmAxes();
    oTalk2ArmAxes.addCommand(talky::ArmTopic::eAXIS_PAN_POS, relaxPosture[0]);
    oTalk2ArmAxes.addCommand(talky::ArmTopic::eAXIS_TILT_POS, relaxPosture[1]);
    oTalk2ArmAxes.addCommand(talky::ArmTopic::eAXIS_RAD_POS, relaxPosture[2]);
}

void Comfortable::readFromArm()
{
    LOG4CXX_INFO(logger, "read from arm TO DO");          
    realPosture[0] = 60;
    realPosture[1] = 40;
    realPosture[3] = 80;

    // sense arm posture
//    talky::Talk2Target& oTalk2ArmAxes = pBodyTalk->getTalk2ArmAxes();
//    oTalk2ArmAxes.addCommand(talky::ArmTopic::eAXIS_PAN_POS, relaxPosture[0]);
//    oTalk2ArmAxes.addCommand(talky::ArmTopic::eAXIS_TILT_POS, relaxPosture[1]);
//    oTalk2ArmAxes.addCommand(talky::ArmTopic::eAXIS_RAD_POS, relaxPosture[2]);
}

void Comfortable::measureDistance()
{    
    dif0[0] = dif[0];
    dif0[1] = dif[1];
    dif0[2] = dif[2];
    dif[0] = fabs(relaxPosture[0] - realPosture[0]);
    dif[1] = fabs(relaxPosture[1] - realPosture[1]);
    dif[2] = fabs(relaxPosture[2] - realPosture[2]);
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