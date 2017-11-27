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
LoggerPtr BodyInspector::logger(Logger::getLogger("roly.body.coms"));

// Constructor 
BodyInspector::BodyInspector()
{    
    modName = "BodyInspector";
    benabled = false;
    pAmyTalker = 0;        
 }

void BodyInspector::init(BodyBus& oBodyBus, AmyTalker& oAmyTalker)
{
    pAmyTalker = &oAmyTalker;

    oComsInBodySense.connect2Bus(oBodyBus);
    
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
    talky::Command oCommand;

    // inspect ARM AXES data
    nety::NetNodeSubscriber& oArmAxisSubscriber = pAmyTalker->getArmAxisSubscriber();    
    // get received messages
    oArmAxisSubscriber.absorb();
    // process them to commands
    oArmAxisSubscriber.process();
    // consume commands queue
    while (oArmAxisSubscriber.hasCommands())
    {                    
        // process each command to a proper bus action
        if (oArmAxisSubscriber.fetchCommand(oCommand))
        {
            //LOG4CXX_INFO(logger, modName + ": cmd received - " + oCommand.toString());        
            oComsInBodySense.processArmAxesData(oCommand);
        }
    }                    
    
}

}