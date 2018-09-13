/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics  *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycoms/BodyComs.h"
#include "roly/bodycore/config/BodyConfig.h"

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
    BodyConfig oBodyConfig;
    float freq = oBodyConfig.getModulesFreq();
     
    // init and start modules
    
    oBodyAware.init(oBodyBus);
    oBodyAware.setFrequency(freq);
    if (oBodyAware.isEnabled())
        oBodyAware.on();
    
    oBodyServer2.init(oBodyBus);
    oBodyServer2.setFrequency(freq);
    if (oBodyServer2.isEnabled())
        oBodyServer2.on();

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

    if (oBodyServer2.isOn())
    {
        oBodyServer2.off();
        oBodyServer2.wait();      
    }
}

bool BodyComs::checkEndRequested()
{
    return oBodyServer2.getBodyEndRequested();    
}

}		
