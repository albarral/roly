/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/body/modules/Expressive.h"

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
    log4cxx::NDC::push(modName);   
    feeling = -1;

    // start at rest state
    setState(eSTATE_REST);    
}
                    
void Expressive::loop()
{
    senseBus();
    
    // skip if module is inhibited
    if (binhibited)            
        return;

    if (getStable() == 0)
        showState();
    
    switch (getState())
    {
        case eSTATE_REST: 
            // nothing done
            break;

        case eSTATE_ACTION:  
            // do new step
            if (performStep())
                // -> WAIT
                setState(eSTATE_WAIT);
            // if no pending steps -> REST
            else
                setState(eSTATE_REST);                    
            break;

        case eSTATE_WAIT:            

            // if step finished, go for next step -> ACTION
            if (isStepFinished())        
            {
                step++;    
                setState(eSTATE_ACTION);
            }
            break;
    }  
    
    writeBus();
}

void Expressive::senseBus()
{
    // check inhibition
    binhibited = pBodyBus->getCO_INHIBIT_EXPRESSIVE().isRequested();

    // if action requested -> ACTION
    if (pBodyBus->getCO_EXPRESSIVE_ACTION().checkRequested())
    {
        std::string command = pBodyBus->getCO_EXPRESSIVE_ACTION().getValue();
        // analyze action validity 
        if (!command.empty())
        {
            LOG4CXX_INFO(logger, "< feeling: " + command);                     
            feeling = analyseFeeling(command);
            if (feeling != -1)
            {
                // if requested feeling has an associated movement, do it
                if (loadMovement4Action(feeling))
                {
                    step = 0;
                    setState(eSTATE_ACTION);                
                }
            }                
        }
    }
    
    // if halt requested -> REST
    if (pBodyBus->getCO_EXPRESSIVE_HALT().checkRequested())
        setState(eSTATE_REST);
}

int Expressive::analyseFeeling(std::string word)
{
    int code = -1;

    // check requested feeling
    if (oFeelingsTheme.getCode4Name(word, code))
        return code;            
    // inform of unknown request
    else
    {
        LOG4CXX_WARN(logger, "unknown feeling requested: " << word << ". Ignored!");                     
        return -1;
    }
}

bool Expressive::performStep()
{
    // if pending steps
    if (step < listMovements.size())
    {
        // get next step and request it 
        ArmMovement& oArmMovement = listMovements.at(step);
        transmitMovement(oArmMovement);
        // start timer and set duration
        oClickStep.start();
        stepDuration = oArmMovement.getTimeMillis();
        return true;
    }
    else
        return false;
}

bool Expressive::isStepFinished()
{
    // check if step duration finished
    oClickStep.read();
    return (oClickStep.getMillis() > stepDuration);         
}

void Expressive::transmitMovement(ArmMovement& oArmMovement)
{
    // if posture request, command arm position
    if (oArmMovement.getType() == ArmMovement::eTYPE_POSTURE)
    {
        oArmAxesClient.setPan(oArmMovement.getPan());
        oArmAxesClient.setTilt(oArmMovement.getTilt());
        oArmAxesClient.setRadial(oArmMovement.getRadius());
    }
    // if move request, command arm speed
    else
    {
        oArmAxesClient.setPanSpeed(oArmMovement.getPan());
        oArmAxesClient.setTiltSpeed(oArmMovement.getTilt());
        oArmAxesClient.setRadialSpeed(oArmMovement.getRadius());
    }                
}

bool Expressive::loadMovement4Action(int action)
{    
    bool bok; 
    // clear movement
    listMovements.clear();
    
    switch (action)
    {
        case tron2::FeelingsTheme::eFEELING_JOY:
            loadMovement4Joy();
            bok = true;
            break;

        default: 
            bok = false;       
    }
    
    // inform of unavailable movement
    if (!bok)
        LOG4CXX_WARN(logger, "requested action not available. Ignored!");      
    
    return bok;
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
    // inhibig comfortable arm while expressing a movement
    switch (getState())
    {
        case eSTATE_ACTION:            
        case eSTATE_WAIT:   
            pBodyBus->getCO_INHIBIT_COMFORTABLE().request(1);
            break;
    }
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