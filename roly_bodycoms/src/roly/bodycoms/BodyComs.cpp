/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics  *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycoms/BodyComs.h"

namespace roly
{
log4cxx::LoggerPtr BodyComs::logger(log4cxx::Logger::getLogger("roly.body.coms"));

BodyComs::BodyComs() 
{
}

BodyComs::~BodyComs()
{    
}
     
 bool BodyComs::launch(BodyBus& oBodyBus)
{
    LOG4CXX_INFO(logger, "BodyComs: launch modules");
    //float freq = oAmyConfig.getModulesFreq();
    float freq = 1; // TEMP to get from config
     
    // init and start modules
    
    oBodyAware.init(oBodyBus);
    oBodyAware.setFrequency(freq);
    if (oBodyAware.isEnabled())
        oBodyAware.on();
    
    oBodyServer.init(oBodyBus);
    oBodyServer.setFrequency(freq);
    if (oBodyServer.isEnabled())
        oBodyServer.on();

    return true;
}

bool BodyComs::end()
{
    LOG4CXX_INFO(logger, "BodyComs: end modules");

    // finish modules

    if (oBodyAware.isOn())
    {
        oBodyAware.off();
        oBodyAware.wait();      
    }

    if (oBodyServer.isOn())
    {
        oBodyServer.off();
        oBodyServer.wait();      
    }
}

bool BodyComs::checkEndRequested()
{
    return oBodyServer.getBodyEndRequested();    
}

}		
