/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycore/BodyTalk.h"
#include "talky/Topics.h"
#include "talky/topics/ArmTopic.h"

namespace roly
{
// Constructor
BodyTalk::BodyTalk ()
{    
    benabled = false;
}

void BodyTalk::init()
{
    // init arm talkers
    int armTopic = talky::Topics::eTOPIC_ARM;
    // cycler category
    oTalk2ArmCycler.init(armTopic, talky::ArmTopic::eCAT_ARM_CYCLIC);
    oTalk2ArmAxes.init(armTopic, talky::ArmTopic::eCAT_ARM_AXIS);
    
    // enabled if all talkers initialized
    benabled = oTalk2ArmCycler.isEnabled() && oTalk2ArmAxes.isEnabled();
}


}
