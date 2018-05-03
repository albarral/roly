#ifndef __ROLY_BODYCOMS_BODYSERVER_H
#define __ROLY_BODYCOMS_BODYSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>


#include "roly/bodycoms/server/ArtisticChannelServer.h"
#include "roly/bodycoms/server/ExpressiveChannelServer.h"
#include "roly/bodycoms/server/ExtraChannelServer.h"
#include "tron2/coms/ChannelServer.h"
#include "roly/bodycore/BodyBus.h"
#include "tron/control/module3.h"

namespace roly
{
// This module serves external control request for body control. 
// It uses a dedicated channel server for each communications channel (one for each topic).
class BodyServer : public tron::Module3
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
    ExpressiveChannelServer oExpressiveChannelServer;     // communications server for expressive channel
    ArtisticChannelServer oArtisticChannelServer;   // communications server for artistic channel
    ExtraChannelServer oExtraChannelServer;    // communications server for extra channel

public:
    BodyServer();
    //~BodyServer();

    void init(BodyBus& oBodyBus);       
    bool isEnabled() {return benabled;};
        
    bool getBodyEndRequested();        

private:
    virtual void first();
    // executes the behaviour
    virtual void loop();
    // check given channel server for received messages and process them
    bool checkChannelServer(tron2::ChannelServer& oChannelServer);
};
}		
#endif
