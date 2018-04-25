/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/bodycoms/modules/BodyServer.h"
#include "roly/bodycore/config/BodyConfig.h"

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
    // prepare communication servers
    oExpressiveChannelServer.connect2Bus(oBodyBus);    
    oArtisticChannelServer.setTargetModule(BodyConfig::ARTISTIC1);
    oArtisticChannelServer.connect2Bus(oBodyBus);    
    oExtraChannelServer.connect2Bus(oBodyBus);    
    
    // if servers enabled
    if (oExpressiveChannelServer.isTuned() && 
        oArtisticChannelServer.isTuned() && 
        oExtraChannelServer.isTuned())
    {
        benabled = true;
        LOG4CXX_INFO(logger, modName + " initialized");                                
    }
    else
        LOG4CXX_ERROR(logger, modName + ": failed initialization, channel servers not tuned!");                        
}

void BodyServer::first()
{    
    log4cxx::NDC::push(modName);   	
}

void BodyServer::loop()
{
    // check expressive channel
    checkChannelServer(oExpressiveChannelServer);        
    // check artistic channel
    checkChannelServer(oArtisticChannelServer);        
    // check extra channel
    checkChannelServer(oExtraChannelServer);        
}

bool BodyServer::checkChannelServer(tron2::ChannelServer& oChannelServer)
{    
    // receive messages from the given channel
    if (oChannelServer.senseChannel())
    {
        // and process them
        oChannelServer.processCommands();
        return true;
    }
    // if no messages could be read
    else
        return false;
}

bool BodyServer::getBodyEndRequested()
{
    return oExtraChannelServer.getEndRequested();
}

}