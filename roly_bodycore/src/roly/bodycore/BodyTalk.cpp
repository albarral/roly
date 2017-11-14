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
    int cyclicCategory = talky::ArmTopic::eCAT_ARM_CYCLIC;
    oTalk2ArmCycler.init(armTopic, cyclicCategory);
    
    // enabled if all talkers initialized
    benabled = oTalk2ArmCycler.isEnabled();
}


}
