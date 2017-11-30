/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "roly/bodycoms/in/ComsInBodyControl.h"
#include "talky/topics/BodyTopic.h"

namespace roly
{
log4cxx::LoggerPtr ComsInBodyControl::logger(log4cxx::Logger::getLogger("roly.body.coms"));

ComsInBodyControl::ComsInBodyControl()
{    
    pBodyBus = 0;
}

void ComsInBodyControl::connect2Bus(BodyBus& oBodyBus)
{
    this->pBodyBus = &oBodyBus;
}


bool ComsInBodyControl::processCommand(talky::Command& oCommand)
{
    bool bret = true;

    // skip if no interface connection
    if (pBodyBus == 0)
    {
        LOG4CXX_ERROR(logger, "ComsInBodyControl: can't process command, no bus connection");           
        return false;
    }

    switch (oCommand.getCategory())
    {
        case talky::BodyTopic::eCAT_BODY_EXPRESSIVE:
            bret = processExpressiveCommand(oCommand);
            break;

        case talky::BodyTopic::eCAT_BODY_ARMMOVER:
            bret = processArmMoverCommand(oCommand);
            break;

        case talky::BodyTopic::eCAT_BODY_EXTRA:
            bret = processExtraCommand(oCommand);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ComsInBodyControl: can't process command, untreated category " << oCommand.getCategory());                        
    }                
    return bret;
}

bool ComsInBodyControl::processExpressiveCommand(talky::Command& oCommand)
{
    bool bret = true;
    float quantity = oCommand.getQuantity();

    switch (oCommand.getConcept())
    {
        case talky::BodyTopic::eEXPRESS_FEELING:
            LOG4CXX_INFO(logger, "> express feeling " << (int)quantity);                        
            pBodyBus->getCO_EXPRESSIVE_ACTION().request((int)quantity);
            break;
            
        case talky::BodyTopic::eEXPRESS_HALT:
            LOG4CXX_INFO(logger, "> halt expression");                     
            pBodyBus->getCO_EXPRESSIVE_HALT().request();
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ComsInBodyControl: can't process command, untreated expressive concept " << oCommand.getConcept());           
    }    
    return bret;
}

bool ComsInBodyControl::processArmMoverCommand(talky::Command& oCommand)
{
    bool bret = true;
    float quantity = oCommand.getQuantity();
    bool byes;

    switch (oCommand.getConcept())
    {
        case talky::BodyTopic::eARMMOVER_TYPE:
            LOG4CXX_INFO(logger, "> arm mover movement type " << (int)quantity);                        
            pBodyBus->getCO_MOVER_TYPE().request((int)quantity);
            break;
            
        case talky::BodyTopic::eARMMOVER_ACTION:
            byes = (quantity != 0.0);
            LOG4CXX_INFO(logger, "> arm mover start/stop " << byes); 
            pBodyBus->getCO_MOVER_ACTION().request(byes);
            break;

        case talky::BodyTopic::eARMMOVER_TURN:
            LOG4CXX_INFO(logger, "> arm mover turn " << (int)quantity);                        
            pBodyBus->getCO_MOVER_TURN().request((int)quantity);
            break;

        case talky::BodyTopic::eARMMOVER_WIDER:
            byes = (quantity != 0.0);
            LOG4CXX_INFO(logger, "> arm mover wider " << byes);                     
            pBodyBus->getCO_MOVER_WIDER().request(byes);
            break;
            
        case talky::BodyTopic::eARMMOVER_TALLER:
            byes = (quantity != 0.0);
            LOG4CXX_INFO(logger, "> arm mover taller " << byes);                     
            pBodyBus->getCO_MOVER_TALLER().request(byes);
            break;

        case talky::BodyTopic::eARMMOVER_FASTER:
            byes = (quantity != 0.0);
            LOG4CXX_INFO(logger, "> arm mover faster " << byes);                     
            pBodyBus->getCO_MOVER_FASTER().request(byes);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ComsInBodyControl: can't process command, untreated arm mover concept " << oCommand.getConcept());           
    }    
    return bret;
}

bool ComsInBodyControl::processExtraCommand(talky::Command& oCommand)
{
    bool bret = true;
    float quantity = oCommand.getQuantity();
    
    switch (oCommand.getConcept())
    {
        case talky::BodyTopic::eEXTRA_BODY_END:
            LOG4CXX_INFO(logger, "> end roly body");  
            oQueueSpecialActions.add(ComsInBodyControl::eACTION_BODY_END);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ComsInBodyControl: can't process command, untreated extra concept " << oCommand.getConcept());           
    }    
    return bret;
}


void ComsInBodyControl::toDoCommand(float value)
{
    // nothing done
    // dummy method for to do commands
    LOG4CXX_INFO(logger, "> to do");                        
}

}