/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>

#include "roly/bodymain/BodyTest.h"
#include "roly/body/moves/MoveFactory.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr BodyTest::logger(Logger::getLogger("roly.body"));    

BodyTest::BodyTest()
{
    pBodyBus = 0;
}

void BodyTest::connect2Bus(BodyBus& oBodyBus)
{
    pBodyBus = &oBodyBus;
}


void BodyTest::testArmMover(int test)
{
    LOG4CXX_INFO(logger, "testArmMover " + std::to_string(test));    
    
    if (!isConnected())
    {
        LOG4CXX_WARN(logger, "testArmMover: no bus connection, skip test");    
        return;
    }
        
    switch (test)
    {
        case 0:
        {
            int movement = MoveFactory::eMOV_LINE;
            bool bgo = true;
            pBodyBus->getCO_MOVER_TYPE().request(movement);
            //pBodyBus->getCO_MOVER_ACTION().request(bgo);            
        }
            break;
            
        case 1:
        {
            bool bwider = true;
            //pBodyBus->getCO_MOVER_WIDER().request(bwider);
        }
            break;
            
        case 2:
        {
            bool bgo = false;
            //pBodyBus->getCO_MOVER_ACTION().request(bgo);            
        }
            break;            
    }
}

}