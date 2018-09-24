#ifndef __ROLY_INTERFACE2_ARTISTICSERVER_H
#define __ROLY_INTERFACE2_ARTISTICSERVER_H

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
// Artistic section server to control a body.
class ArtisticServer : public tron::SectionServer
{            
private:
    static log4cxx::LoggerPtr logger2;
    std::string serverName;
    int target;       // defines which artistic module is controlled
    tron::ChannelReader* pFigureChannel;    // channel reader for artistic figure
    tron::ChannelReader* pChangesChannel;    // channel reader for movement changes
    tron::ChannelReader* pTurnsChannel;   // channel reader for movement turns
    tron::ChannelReader* pHaltChannel;  // channel reader for movement halt

public:
    ArtisticServer();
    //~ArtisticServer();

    // tune server to given artistic module (connect channels to proper topics)
    bool tune2Artistic(int i);

    // get requested artistic figure (figure name)
    bool getFigure(std::string& value);
    // get requested movement change (speed, size or length features)
    bool getMovementChange(std::string& value);
    // get requested movement turn (left or right)
    bool getMovementTurn(std::string& value);
    // get movement halt received command 
    bool getHalt();    
};

}
#endif
