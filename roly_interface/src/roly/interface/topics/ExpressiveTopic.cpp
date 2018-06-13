/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/interface/topics/ExpressiveTopic.h"
#include "roly/interface/BodyNode.h"

namespace roly
{
ExpressiveTopic::ExpressiveTopic() : Topic(BodyNode::eBODY_EXPRESSIVE, BodyNode::BODY_EXPRESSIVE)
{
    fillConcepts();    
}

void ExpressiveTopic::fillConcepts()
{
    addCode(eEXPRESS_FEELING, EXPRESS_FEELING);                        
    addCode(eEXPRESS_HALT, EXPRESS_HALT);                        
}
}