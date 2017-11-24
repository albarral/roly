/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/bodycoms/modules/BodyInspector.h"
//#include "talky/Topics.h"
//#include "talky/topics/ArmTopic.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr BodyInspector::logger(Logger::getLogger("roly.body"));

// Constructor 
BodyInspector::BodyInspector()
{    
    modName = "BodyInspector";
    benabled = false;
    pAmyTalker = 0;        
 }

void BodyInspector::init(AmyTalker& oAmyTalker)
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

void BodyInspector::first()
{    
    log4cxx::NDC::push(modName);   	
}

void BodyInspector::loop()
{
    // listen to axis messages
    checkSubscriber(pAmyTalker->getAxisSubscriber());
}

void BodyInspector::checkSubscriber(nety::NetNodeSubscriber& oNetySubscriber)
{
    talky::Command oCommand;

    // get received messages
    oNetySubscriber.absorb();
    // process them to commands
    oNetySubscriber.process();
    // consume commands queue
    while (oNetySubscriber.hasCommands())
    {                    
        // process each command to a proper bus action
        if (oNetySubscriber.fetchCommand(oCommand))
        {
            LOG4CXX_INFO(logger, modName + ": cmd received - " + oCommand.toString());        
            //oComsArmControl.processCommand(oCommand);
        }
    }                
}
}