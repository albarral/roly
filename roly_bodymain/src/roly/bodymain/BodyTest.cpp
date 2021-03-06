/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>

#include "roly/bodymain/BodyTest.h"
#include "roly/bodycore/ArtisticBus.h"
#include "tron2/language/objects/FiguresTheme.h"

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

void BodyTest::testExpressive()
{
    if (!isConnected())
    {
        LOG4CXX_WARN(logger, "testExpressive: no bus connection, skip test");    
        return;
    }
            
    switch (step)
    {
        case 5:
        case 10:
        case 15:
            pBodyBus->getCO_EXPRESSIVE_ACTION().request(0);
            break;            
    }
    
    step++;
}

void BodyTest::testArtistic()
{
    LOG4CXX_INFO(logger, "testArtistic - step " + std::to_string(step));    
    
    if (!isConnected())
    {
        LOG4CXX_WARN(logger, "testArtistic: no bus connection, skip test");    
        return;
    }
      
    ArtisticBus& oArtisticBus = pBodyBus->getArtisticBus1();
    switch (step)
    {
        case 2:
            oArtisticBus.getCO_ARTISTIC_FIGURE().request("circle");
            break;            
            
        case 5:
            oArtisticBus.getCO_ARTISTIC_SET().request("faster");
            break;

        case 10:
            oArtisticBus.getCO_ARTISTIC_SET().request("bigger");            
            break;            

        case 15:   
            oArtisticBus.getCO_ARTISTIC_HALT().request();            
            break;            
    }
    
    step++;
}

}