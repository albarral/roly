#ifndef __ROLY_INTERFACE2_ARTISTICSERVER_H
#define __ROLY_INTERFACE2_ARTISTICSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "tron/coms/ComsReceiver.h"
#include "tron/coms/ChannelReader.h"

namespace roly
{
// Artistic section server to control a body.
// Uses tron ComsReceiver for communications    
class ArtisticServer
{            
private:
    static log4cxx::LoggerPtr logger;
    tron::ComsReceiver oComsReceiver;  // communications object     
    tron::ChannelReader* pFigureChannel;    // channel reader for artistic figure
    tron::ChannelReader* pChangesChannel;    // channel reader for movement changes
    tron::ChannelReader* pTurnsChannel;   // channel reader for movement turns
    tron::ChannelReader* pHaltChannel;  // channel reader for movement halt

public:
    ArtisticServer();
    //~ArtisticServer();

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
