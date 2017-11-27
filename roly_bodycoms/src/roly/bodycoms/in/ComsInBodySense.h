#ifndef __ROLY_BODYCOMS_IN_BODYSENSE_H
#define __ROLY_BODYCOMS_IN_BODYSENSE_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "roly/bodycore/BodyBus.h"
#include "talky/coms/Command.h"

namespace roly
{
// Class used to process external sensor info.
// Data are converted to proper bus SI signals.
class ComsInBodySense 
{    
private:
    static log4cxx::LoggerPtr logger;            
    BodyBus* pBodyBus;      // access to body bus
    
public:
    ComsInBodySense();
    //~ComsInBodySense();
    
    void connect2Bus(BodyBus& oBodyBus);

    // process sensor data of arm axis category
    bool processArmAxesData(talky::Command& oCommand);

    // dummy method for to do commands
    void toDoCommand(float value);
};
}
#endif
