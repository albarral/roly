#ifndef __ROLY_BODYCOMS_EXTRA_CHANNELSERVER_H
#define __ROLY_BODYCOMS_EXTRA_CHANNELSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron/talky2/channel/ChannelServer.h"
#include "roly/bodycoms/BodyConnector.h"

namespace roly
{
// Channel server implementation for body extra topic.
class ExtraChannelServer : public tron::ChannelServer, public BodyConnector
{       
private:
    bool bEndRequested;         // end of body process requested
    
public:
    ExtraChannelServer();
    //~ExtraChannelServer();
    
    // process commands from received messages
    virtual void processCommands();
    
    bool getEndRequested() {return bEndRequested;};
};

}
#endif
