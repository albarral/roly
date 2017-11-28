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
     
 bool BodyComs::launch(BodyBus& oBodyBus, AmyTalker& oAmyTalker)
{
    LOG4CXX_INFO(logger, "BodyComs: launch modules");
    //float freq = oAmyConfig.getModulesFreq();
    float freq = 10; // TEMP to get from config
     
    // init and start modules
    
    oBodyCommander.init(oAmyTalker);
    oBodyCommander.setFrequency(freq);
    if (oBodyCommander.isEnabled())
        oBodyCommander.on();

    oBodyInspector.init(oBodyBus, oAmyTalker);
    oBodyInspector.setFrequency(freq);
    if (oBodyInspector.isEnabled())
        oBodyInspector.on();
    
    oBodyListener.init(oBodyBus);
    oBodyListener.setFrequency(freq);
    if (oBodyListener.isEnabled())
        oBodyListener.on();

    return true;
}

bool BodyComs::end()
{
    LOG4CXX_INFO(logger, "BodyComs: end modules");

    // finish modules
    
    if (oBodyCommander.isOn())
    {
        oBodyCommander.off();
        oBodyCommander.wait();      
    }

    if (oBodyInspector.isOn())
    {
        oBodyInspector.off();
        oBodyInspector.wait();      
    }

    if (oBodyListener.isOn())
    {
        oBodyListener.off();
        oBodyListener.wait();      
    }
}

bool BodyComs::checkEndRequested()
{
    bool byes = false;

    // if pending special actions
    if (oBodyListener.checkSpecialActions())
    {
        byes = oBodyListener.getBodyEndRequested();
    }
    return byes;    
}

}		
