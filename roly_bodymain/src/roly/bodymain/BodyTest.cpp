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
    step = 0;
}

void BodyTest::connect2Bus(BodyBus& oBodyBus)
{
    pBodyBus = &oBodyBus;
}


void BodyTest::testArmMover()
{
    LOG4CXX_INFO(logger, "testArmMover - step " + std::to_string(step));    
    
    if (!isConnected())
    {
        LOG4CXX_WARN(logger, "testArmMover: no bus connection, skip test");    
        return;
    }
            
    switch (step)
    {
        case 0:
        {
            pBodyBus->getCO_MOVER_TYPE().request(MoveFactory::eMOV_CIRCLE);
            pBodyBus->getCO_MOVER_ACTION().request(true);            
        }
            break;
            
        case 1:
        case 2:
        case 3:
            pBodyBus->getCO_MOVER_WIDER().request(true);
//            pBodyBus->getCO_MOVER_TALLER().request(true);
            break;
            
        case 6:
        case 7:
        case 8:
            pBodyBus->getCO_MOVER_FASTER().request(true);
            break;

        case 11:
            pBodyBus->getCO_MOVER_ACTION().request(false);            
            break;            

        case 12:   
            // finish test 
            bfinished = true;            
            break;            
    }
    
    step++;
}

}