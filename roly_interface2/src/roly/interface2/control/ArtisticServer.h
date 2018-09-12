#ifndef __ROLY_INTERFACE2_ARTISTICSERVER_H
#define __ROLY_INTERFACE2_ARTISTICSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

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
    tron::ChannelReader* pHSChannel;    // channel reader for HS joint
    tron::ChannelReader* pVSChannel;    // channel reader for VS joint
    tron::ChannelReader* pELBChannel;   // channel reader for ELB joint
    tron::ChannelReader* pHWRIChannel;  // channel reader for HWRI joint
    tron::ChannelReader* pVWRIChannel;  // channel reader for VWRI joint

public:
    ArtisticServer();
    //~ArtisticServer();

    // get HS joint position received command (degrees)
    bool getHS(float& value);
    // get VS joint position received command (degrees)
    bool getVS(float& value);
    // get ELB joint position received command (degrees)
    bool getELB(float& value);
    // get HWRI joint position received command (degrees)
    bool getHWRI(float& value);
    // get VWRI joint position received command (degrees)
    bool getVWRI(float& value);    
};

}
#endif
