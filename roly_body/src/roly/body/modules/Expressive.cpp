/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/body/modules/Expressive.h"
#include "talky/topics/ArmTopic.h"


using namespace log4cxx;

namespace roly
{
LoggerPtr Expressive::logger(Logger::getLogger("roly.body"));

Expressive::Expressive()
{
    modName = "Expressive";
}

//Expressive::~Expressive()
//{
//}

void Expressive::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}


void Expressive::first()
{
    // start at rest state
    setState(eSTATE_REST);    
    log4cxx::NDC::push(modName);   
    showState();
}
                    
void Expressive::loop()
{
    senseBus();
    
    // skip if module is inhibited
    if (binhibited)            
        return;
    
    switch (getState())
    {
        case eSTATE_REST: 
            // nothing done
            break;

        case eSTATE_ACTION:            
            // if pending steps
            if (step < listMovements.size())
            {
                // get next step and request it 
                ArmMovement& oArmMovement = listMovements.at(step);
                performStep(oArmMovement);
                // start timer and set duration
                oClickTired.start();
                stepDuration = oArmMovement.getTimeMillis();
                // -> WAIT
                setState(eSTATE_WAIT);
            }
            // if no pending steps -> REST
            else
                setState(eSTATE_REST);                    
            break;

        case eSTATE_WAIT:            
            // check if step duration finished
            oClickTired.read();
            // if finished, go for next step -> ACTION
            if (oClickTired.getMillis() > stepDuration)        
            {
                step++;    
                setState(eSTATE_ACTION);
            }
            break;
    }  
    
    if (isStateChanged())
        showState();
    //writeBus();
}

void Expressive::senseBus()
{
    // check inhibition
    binhibited = pBodyBus->getCO_INHIBIT_EXPRESSIVE().isRequested();
    // if action requested -> ACTION
    if (pBodyBus->getCO_EXPRESSIVE_ACTION().checkRequested())
    {
        int action = pBodyBus->getCO_EXPRESSIVE_ACTION().getValue();
        // load new movement 
        loadMovement4Action(action);
        step = 0;
        setState(eSTATE_ACTION);
    }
    // if halt requested -> REST
    if (pBodyBus->getCO_EXPRESSIVE_HALT().checkRequested())
    {
        setState(eSTATE_REST);
    }
}

void Expressive::performStep(ArmMovement& oArmMovement)
{
    // get client for arm axis
    nety::NetNodeClient& oAxisClient = pAmyTalker->getArmAxisClient();
    // if posture request
    if (oArmMovement.getType() == ArmMovement::eTYPE_POSTURE)
    {
        oAxisClient.addCommand(talky::ArmTopic::eAXIS_PAN_POS, oArmMovement.getPan());
        oAxisClient.addCommand(talky::ArmTopic::eAXIS_TILT_POS, oArmMovement.getTilt());
        oAxisClient.addCommand(talky::ArmTopic::eAXIS_RAD_POS, oArmMovement.getRadius());
    }
    // if move request
    else
    {
        oAxisClient.addCommand(talky::ArmTopic::eAXIS_PAN_SPEED, oArmMovement.getPan());
        oAxisClient.addCommand(talky::ArmTopic::eAXIS_TILT_SPEED, oArmMovement.getTilt());
        oAxisClient.addCommand(talky::ArmTopic::eAXIS_RAD_SPEED, oArmMovement.getRadius());
    }                
}

void Expressive::loadMovement4Action(int action)
{    
    // clear movement
    listMovements.clear();
    
    switch (action)
    {
        case Expressive::eEXPRESS_JOY:
            loadMovement4Joy();
            break;
    }
}

void Expressive::loadMovement4Joy()
{
    int millis = 200;
    float pos1[3] = {60.0, 60.0, 80.0}; 
    float pos2[3] = {60.0, 60.0, 40.0}; 

    ArmMovement oArmMovement;
    // four steps (pos1, pos2, pos1, pos2)
    oArmMovement.setPosture(pos1[0], pos1[1], pos1[2], millis);
    listMovements.push_back(oArmMovement);
    oArmMovement.setPosture(pos2[0], pos2[1], pos2[2], millis);
    listMovements.push_back(oArmMovement);
    oArmMovement.setPosture(pos1[0], pos1[1], pos1[2], millis);
    listMovements.push_back(oArmMovement);
    oArmMovement.setPosture(pos2[0], pos2[1], pos2[2], millis);
    listMovements.push_back(oArmMovement);    
}

void Expressive::writeBus()
{
    // nothing to do here    
    // control already done by talk2arm())
}

void Expressive::showState()
{
    switch (getState())
    {
        case eSTATE_REST:
            LOG4CXX_INFO(logger, ">> rest");
            break;
                        
        case eSTATE_ACTION:
            LOG4CXX_INFO(logger, ">> action");
            break;

        case eSTATE_WAIT:
            LOG4CXX_INFO(logger, ">> wait");
            break;
    }   // end switch    
}


}