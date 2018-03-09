/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/bodycoms/modules/BodyServer.h"
#include "talky/Topics.h"
#include "talky/topics/BodyTopic.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr BodyServer::logger(Logger::getLogger("roly.body.coms"));

// Constructor 
BodyServer::BodyServer()
{    
    modName = "BodyServer";
    benabled = false;
 }

void BodyServer::init(BodyBus& oBodyBus)
{
    int topic = talky::Topics::eTOPIC_BODYROLE;
    // prepare communication servers
    oBodyServer4Expressive.init(topic, talky::BodyTopic::eCAT_BODY_EXPRESSIVE);
    oBodyServer4Artistic.init(topic, talky::BodyTopic::eCAT_BODY_ARTISTIC);
    oBodyServer4Extra.init(topic, talky::BodyTopic::eCAT_BODY_EXTRA);    
    
    oComsInBodyControl.connect2Bus(oBodyBus);
    
    // if servers enabled
    if (oBodyServer4Expressive.isConnected() &&            
        oBodyServer4Artistic.isConnected() &&
        oBodyServer4Extra.isConnected())
    {
        benabled = true;
        LOG4CXX_INFO(logger, modName + " initialized");                                
    }
    else
        LOG4CXX_ERROR(logger, modName + ": failed initialization, server nodes not connected!");                        
}

void BodyServer::first()
{    
    log4cxx::NDC::push(modName);   	
}

void BodyServer::loop()
{
    // listen to expressive messages
    checkServer(oBodyServer4Expressive);
    // listen to artistic messages
    checkServer(oBodyServer4Artistic);
    // listen to extra messages
    checkServer(oBodyServer4Extra);
}

void BodyServer::checkServer(nety::NetNodeServer& oNetyServer)
{
    talky::Command oCommand;

    // get received messages
    oNetyServer.absorb();
    // process them to commands
    oNetyServer.process();
    // consume commands queue
    while (oNetyServer.hasCommands())
    {                    
        // process each command to a proper bus action
        if (oNetyServer.fetchCommand(oCommand))
        {
            LOG4CXX_INFO(logger, modName + ": cmd received - " + oCommand.toString());        
            oComsInBodyControl.processCommand(oCommand);
        }
    }                
}

bool BodyServer::checkSpecialActions()
{
    // clear all flags
    brequestedBodyEnd = false;

    tuly::IntegerQueue& oQueue = oComsInBodyControl.getQueueSpecialActions();
    int numActions = oQueue.getSize();
    int action; 
    // consume queue of special actions
    while (oQueue.isFilled())
    {
         oQueue.fetch(action);
         // set flags proper to requested actions    
         switch (action)
         {
             case ComsInBodyControl::eACTION_BODY_END:
                 brequestedBodyEnd = true;
                 break;
         }
    }
        
    return (numActions > 0);    
}

}