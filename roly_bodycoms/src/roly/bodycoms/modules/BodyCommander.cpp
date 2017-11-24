/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/bodycoms/modules/BodyCommander.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr BodyCommander::logger(Logger::getLogger("roly.body"));

// Constructor 
BodyCommander::BodyCommander ()
{    
    modName = "BodyCommander";
    benabled = false;
    pAmyTalker = 0;    
 }

void BodyCommander::init(AmyTalker& oAmyTalker)
{
    pAmyTalker = &oAmyTalker;

    if (pAmyTalker != 0)
    {
        benabled = true;
        LOG4CXX_INFO(logger, modName + " initialized");                                
    }
    else
        LOG4CXX_ERROR(logger, modName + ": init failed");                        
}

void BodyCommander::first()
{    
    log4cxx::NDC::push(modName);   	
}

void BodyCommander::loop()
{      
    // send commands for arm cyclic category
    pAmyTalker->getCyclerClient().process();
    pAmyTalker->getCyclerClient().flush();
    // send commands for arm axis category
    pAmyTalker->getAxisClient().process();
    pAmyTalker->getAxisClient().flush();    
}

}