#ifndef __ROLY_INTERFACE2_EXPRESSIVESERVER_H
#define __ROLY_INTERFACE2_EXPRESSIVESERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "tron/coms/ComsReceiver.h"
#include "tron/coms/ChannelReader.h"

namespace roly
{
// Expressive section server to control a body.
// Uses tron ComsReceiver for communications    
class ExpressiveServer
{            
private:
    static log4cxx::LoggerPtr logger;
    tron::ComsReceiver oComsReceiver;  // communications object     
    tron::ChannelReader* pPanChannel;    // channel reader for Pan axis
    tron::ChannelReader* pTiltChannel;    // channel reader for Tilt axis

public:
    ExpressiveServer();
    //~ExpressiveServer();

    // get received Pan axis position (degrees)
    bool getPan(float& value);
    // get received Tilt axis position  (degrees)
    bool getTilt(float& value);
    // get received Radial axis position  (cm)
    bool getRadial(float& value);
    // get received  Pan axis speed (degrees/s)
    bool getPanSpeed(float& value);
    // get received  Tilt axis speed  (degrees/s)
    bool getTiltSpeed(float& value);    
    // get received  Radial axis speed (cm/s)
    bool getRadialSpeed(float& value);    
    // get received keep tilt (flag))
    bool getKeepTilt(bool& value);    
};

}
#endif
