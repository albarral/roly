#ifndef __ROLY_INTERFACE2_EXPRESSIVESERVER_H
#define __ROLY_INTERFACE2_EXPRESSIVESERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "tron/interface/SectionServer.h"
#include "tron/coms/ChannelReader.h"

namespace roly
{
// Expressive section server to control a body.
class ExpressiveServer : public tron::SectionServer
{            
private:
    static log4cxx::LoggerPtr logger2;
    tron::ChannelReader* pFeelingChannel;    // channel reader for feeling topic
    tron::ChannelReader* pHaltChannel;        // channel reader for halt topic

public:
    ExpressiveServer();
    //~ExpressiveServer();

    // get requested feeling (name)
    bool getFeeling(std::string& value);
    // get movement halt received command 
    bool getHalt();
};

}
#endif
