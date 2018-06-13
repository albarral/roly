/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/interface/topics/ArtisticTopic.h"
#include "roly/interface/BodyNode.h"

namespace roly
{

ArtisticTopic::ArtisticTopic() : Topic(BodyNode::eBODY_ARTISTIC, BodyNode::BODY_ARTISTIC)
{
    fillConcepts();    
}

void ArtisticTopic::fillConcepts()
{
    addCode(eARTISTIC_FIGURE, ARTISTIC_FIGURE);                        
    addCode(eARTISTIC_FREQ, ARTISTIC_FREQ);                        
    addCode(eARTISTIC_SIZE, ARTISTIC_SIZE);                        
    addCode(eARTISTIC_ORIENTATION, ARTISTIC_ORIENTATION);                        
    addCode(eARTISTIC_RELFACTOR, ARTISTIC_RELFACTOR);                        
    addCode(eARTISTIC_HALT, ARTISTIC_HALT);                        
}
}