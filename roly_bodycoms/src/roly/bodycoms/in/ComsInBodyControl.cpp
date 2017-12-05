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

        case talky::BodyTopic::eCAT_BODY_ARTISTIC:
            bret = processArtisticCommand(oCommand);
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

bool ComsInBodyControl::processArtisticCommand(talky::Command& oCommand)
{
    bool bret = true;
    float quantity = oCommand.getQuantity();

    switch (oCommand.getConcept())
    {
        case talky::BodyTopic::eARTISTIC_FIGURE:
            LOG4CXX_INFO(logger, "> artistic figure " << (int)quantity);                        
            pBodyBus->getCO_ARTISTIC_FIGURE().request((int)quantity);
            break;
            
        case talky::BodyTopic::eARTISTIC_FREQ:
            LOG4CXX_INFO(logger, "> artistic freq " << quantity); 
            pBodyBus->getCO_ARTISTIC_FREQ().request(quantity);
            break;

        case talky::BodyTopic::eARTISTIC_SIZE:
            LOG4CXX_INFO(logger, "> artistic size " << quantity);                        
            pBodyBus->getCO_ARTISTIC_SIZE().request(quantity);
            break;

        case talky::BodyTopic::eARTISTIC_ORIENTATION:
            LOG4CXX_INFO(logger, "> artistic orientation " << quantity);                     
            pBodyBus->getCO_ARTISTIC_ORIENTATION().request(quantity);
            break;
            
        case talky::BodyTopic::eARTISTIC_RELFACTOR:
            LOG4CXX_INFO(logger, "> artistic relative factor " << quantity);                     
            pBodyBus->getCO_ARTISTIC_RELFACTOR().request(quantity);
            break;

        case talky::BodyTopic::eARTISTIC_HALT:
            LOG4CXX_INFO(logger, "> artistic halt");                     
            pBodyBus->getCO_ARTISTIC_HALT().request();
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ComsInBodyControl: can't process command, untreated artistic concept " << oCommand.getConcept());           
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