#ifndef __ROLY_BODYCOMS_ARTISTIC_CHANNELSERVER_H
#define __ROLY_BODYCOMS_ARTISTIC_CHANNELSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron2/talky/channel/ChannelServer.h"
#include "roly/bodycoms/BodyConnector.h"
#include "roly/bodycore/ArtisticBus.h"

namespace roly
{
// Channel server implementation for body artistic topic.
class ArtisticChannelServer : public tron2::ChannelServer, public BodyConnector
{            
private: 
    int targetModule;
    ArtisticBus* pArtisticBus;

public:
    ArtisticChannelServer();
    //~ArtisticChannelServer();
    
    // sets target module
    void setTargetModule(int value);

    virtual void connect2Bus(BodyBus& oBodyBus);

    // process commands from received messages
    virtual void processCommands();
};

}
#endif
