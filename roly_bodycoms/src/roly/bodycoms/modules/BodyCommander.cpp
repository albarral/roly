/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/bodycoms/modules/BodyCommander.h"
#include "talky/Talk2Target.h"
#include "talky/topics/ArmTopic.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr BodyCommander::logger(Logger::getLogger("roly.body"));

// Constructor 
BodyCommander::BodyCommander ()
{    
    modName = "BodyCommander";
    benabled = false;
    pBodyTalk = 0;    
 }

void BodyCommander::init(BodyTalk& oBodyTalk)
{
    pBodyTalk = &oBodyTalk;

    oBody2Arm.init();

    if (oBody2Arm.isEnabled())
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
    talky::Talk2Target& oTalk2ArmCycler = pBodyTalk->getTalk2ArmCycler();
    while (oTalk2ArmCycler.isArmed())
    {
        if (oTalk2ArmCycler.processCommand())
        {
            oBody2Arm.sendMessage(oTalk2ArmCycler.getRawMessage(), talky::ArmTopic::eCAT_ARM_CYCLIC);
        }
    }
}

}