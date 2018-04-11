#ifndef __ROLY_BODYCOMS_ARTISTIC_CHANNELSERVER_H
#define __ROLY_BODYCOMS_ARTISTIC_CHANNELSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron2/talky/channel/ChannelServer.h"
#include "roly/bodycoms/BodyConnector.h"

namespace roly
{
// Channel server implementation for body artistic topic.
class ArtisticChannelServer : public tron2::ChannelServer, public BodyConnector
{            
public:
    ArtisticChannelServer();
    //~ArtisticChannelServer();
    
    // process commands from received messages
    virtual void processCommands();
};

}
#endif
