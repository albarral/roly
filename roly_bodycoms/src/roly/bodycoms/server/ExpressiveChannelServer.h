#ifndef __ROLY_BODYCOMS_EXPRESSIVE_CHANNELSERVER_H
#define __ROLY_BODYCOMS_EXPRESSIVE_CHANNELSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron/talky2/channel/ChannelServer.h"
#include "roly/bodycoms/BodyConnector.h"

namespace roly
{
// Channel server implementation for body expressive topic.
class ExpressiveChannelServer : public tron::ChannelServer, public BodyConnector
{            
public:
    ExpressiveChannelServer();
    //~ExpressiveChannelServer();
    
    // process commands from received messages
    virtual void processCommands();
};

}
#endif