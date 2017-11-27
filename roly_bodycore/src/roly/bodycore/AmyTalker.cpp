/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycore/AmyTalker.h"
#include "talky/Topics.h"
#include "talky/topics/ArmTopic.h"

namespace roly
{
// Constructor
AmyTalker::AmyTalker ()
{    
    benabled = false;
}

void AmyTalker::init()
{
    // connects all communication nodes to amy
    int topic = talky::Topics::eTOPIC_ARM;
    // clients
    oArmCyclerClient.init(topic, talky::ArmTopic::eCAT_ARM_CYCLIC);
    oArmAxisClient.init(topic, talky::ArmTopic::eCAT_ARM_AXIS);
    // subscribers
    oArmAxisSubscriber.init(topic, talky::ArmTopic::eCAT_ARM_AXIS);
    
    // enabled if all nodes initialized
    benabled = oArmCyclerClient.isConnected() && 
            oArmAxisClient.isConnected() &&
            oArmAxisSubscriber.isConnected();
}


}
