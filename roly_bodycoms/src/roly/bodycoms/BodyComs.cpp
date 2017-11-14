/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics  *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycoms/BodyComs.h"

namespace roly
{
log4cxx::LoggerPtr BodyComs::logger(log4cxx::Logger::getLogger("roly.body"));

BodyComs::BodyComs() 
{
}

BodyComs::~BodyComs()
{    
}
     
 bool BodyComs::launch(BodyBus& oBodyBus, BodyTalk& oBodyTalk)
{
    LOG4CXX_INFO(logger, "BodyComs: launch modules");
    //float freq = oAmyConfig.getModulesFreq();
    float freq = 10; // TEMP to get from config
     
    // launch commander module
    oBodyCommander.init(oBodyTalk);
    oBodyCommander.setFrequency(freq);
    if (oBodyCommander.isEnabled())
        oBodyCommander.on();
  }

bool BodyComs::end()
{
    LOG4CXX_INFO(logger, "BodyComs: end modules");

    // finish commander module
    if (oBodyCommander.isOn())
    {
        oBodyCommander.off();
        oBodyCommander.wait();      
    }
}

bool BodyComs::checkEndRequested()
{
    bool byes = false;

    // TO DO from BodyListener
//    // if pending special actions
//    if (oAmyListener.checkSpecialActions())
//    {
//        // check if end action requested
//        for (int action : oAmyListener.getComsData().getListSpecialActions())
//        {
//            if (action == ComsData::eACTION_AMY_END)
//            {
//                byes = true;
//                break;
//            }
//        }
//
//        // reset special actions
//        oAmyListener.clearSpecialActions();
//    }
    return byes;    
}

}		