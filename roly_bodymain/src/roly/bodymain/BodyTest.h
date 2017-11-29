#ifndef __ROLY_BODYMAIN_BODYTEST_H
#define __ROLY_BODYMAIN_BODYTEST_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "roly/bodycore/BodyBus.h"

namespace roly
{
// class used to conduct tests
class BodyTest
{
 private:
     static log4cxx::LoggerPtr logger;
     BodyBus* pBodyBus;   // bus access
     int step;
     bool bfinished;        // flag indicating test is finished

public:
    BodyTest();
//    ~BodyTest();

    void connect2Bus(BodyBus& oBodyBus);
    bool isConnected() {return pBodyBus != 0;};
    
    void resetStep() {step = 0;}
    bool isTestFinished() {return bfinished;};

    void testArmMover();    
    void testExpressive();
};

}    
#endif
