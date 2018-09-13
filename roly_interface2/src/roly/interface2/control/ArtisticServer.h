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
    tron::ChannelReader* pFrequencyChannel;    // channel reader for cyclic frequency
    tron::ChannelReader* pSizeChannel;   // channel reader for figure size
    tron::ChannelReader* pOrientationChannel;  // channel reader for figure orientation
    tron::ChannelReader* pRelFactorChannel;  // channel reader for figure relative factor
    tron::ChannelReader* pHaltChannel;  // channel reader for movement halt

public:
    ArtisticServer();
    //~ArtisticServer();

    // get artistic figure received command (figure name)
    bool getFigure(std::string& value);
    // get cyclic frequency received command (Hz)
    bool getFrequency(float& value);
    // get figure size received command (degrees)
    bool getSize(float& value);
    // get figure orientation received command (degrees)
    bool getOrientation(float& value);
    // get figure relative factor received command
    bool getRelativeFactor(float& value);    
    // get movement halt received command 
    bool getHalt();    
};

}
#endif
