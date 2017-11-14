/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "roly/bodycoms/out/Body2Arm.h"
#include "talky/Topics.h"
#include "talky/languages/ArmLanguage.h"
#include "talky/topics/ArmTopic.h"

namespace roly
{
log4cxx::LoggerPtr Body2Arm::logger(log4cxx::Logger::getLogger("roly.body"));

Body2Arm::Body2Arm()
{    
    benabled = false;
}

void Body2Arm::init()
{
    talky::ArmLanguage oArmLanguage;
    // prepare communication clients    
    oClient2ArmCycler.connect(talky::Topics::ARM_TOPIC, oArmLanguage.CAT_ARM_CYCLIC);

    benabled = oClient2ArmCycler.isConnected();
}
    
bool Body2Arm::sendMessage(std::string message, int category)
{
    if (!benabled)
    {
        LOG4CXX_ERROR(logger, "Body2Arm: module not enabled, can't send message!");                        
        return false;
    }    
       
    LOG4CXX_INFO(logger, "Body2Arm > " + message);                        

    bool bsent;
    switch (category)
    {
        case talky::ArmTopic::eCAT_ARM_CYCLIC:
            bsent = sendMessage2Channel(oClient2ArmCycler, message);
            break;

        default:
            bsent = false;
            LOG4CXX_WARN(logger, "Body2Arm: unknown category, message not sent");                        
            break;
    }
    
    return bsent;
}

bool Body2Arm::sendMessage2Channel(comy::ComyFileClient& oComyClient, std::string message)
{
    // send message 
    if (oComyClient.sendMessage(message))
    {
        return true;
    }    
    else
    {
        LOG4CXX_WARN(logger, "not sent");                        
        return false;
    }
}

}