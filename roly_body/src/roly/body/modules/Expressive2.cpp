/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/body/modules/Expressive2.h"
#include "tron2/moves/SequentialFactory.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr Expressive2::logger(Logger::getLogger("roly.body"));

Expressive2::Expressive2() : BodyBehaviour("Expressive2")
{
    addStateName("rest");
    addStateName("action");
    addStateName("wait");
}

//Expressive2::~Expressive2()
//{
//}


void Expressive2::start()
{
    log4cxx::NDC::push(name);   
    LOG4CXX_INFO(logger, " initialized");          

    feeling = -1;
    // start at rest state
    setState(eSTATE_REST);    
    LOG4CXX_INFO(logger, ">> " << getStateName());          
}
                    
void Expressive2::sense()
{
    // check inhibition
    inhibit(pBodyBus->getCO_INHIBIT_EXPRESSIVE().isRequested());

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
                if (loadMovement(feeling))
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

void Expressive2::actuate()
{
    // method skipped when behaviour inhibited

    if (isStateChanged())
        LOG4CXX_INFO(logger, ">> " << getStateName());          
    
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

    if (isStateChanged())
        LOG4CXX_INFO(logger, ">> " << getStateName());          
    
    writeBus();
}


int Expressive2::analyseFeeling(std::string word)
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

// TO DO ... extend available movements
bool Expressive2::loadMovement(int action)
{    
    bool bok; 
    
    // use sequential factory to generate proper movement
    switch (action)
    {
        case tron2::FeelingsTheme::eFEELING_JOY:
            bok = tron2::SequentialFactory::generateMovement(oSequentialMovement, tron2::SequentialFactory::eMOVEMENT_JOY);
            break;

        default: 
            bok = false;       
    }
    
    // inform of unavailable movement
    if (!bok)
        LOG4CXX_WARN(logger, "requested action not available. Ignored!");      
    
    return bok;
}

bool Expressive2::performStep()
{
    // if pending steps
    if (step < oSequentialMovement.getNumSteps())
    {
        // get next step and request it 
        tron2::BasicMovement& oBasicMovement = oSequentialMovement.getMovementsList().at(step);
        transmitMovement(oBasicMovement);
        // start timer and set duration
        oClickStep.start();
        stepDuration = oBasicMovement.getTime();
        return true;
    }
    else
        return false;
}

bool Expressive2::isStepFinished()
{
    // check if step duration finished
    oClickStep.read();
    return (oClickStep.getMillis() > stepDuration);         
}

void Expressive2::transmitMovement(tron2::BasicMovement& oBasicMovement)
{
    // if posture request, command arm position
    if (oBasicMovement.isPosture())
    {
        oArmAxesClient.setPan(oBasicMovement.getPan());
        oArmAxesClient.setTilt(oBasicMovement.getTilt());
        oArmAxesClient.setRadial(oBasicMovement.getRadius());
    }
    // if move request, command arm speed
    else if (oBasicMovement.isMove())
    {
        oArmAxesClient.setPanSpeed(oBasicMovement.getPan());
        oArmAxesClient.setTiltSpeed(oBasicMovement.getTilt());
        oArmAxesClient.setRadialSpeed(oBasicMovement.getRadius());
    }                
}

void Expressive2::writeBus()
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


}