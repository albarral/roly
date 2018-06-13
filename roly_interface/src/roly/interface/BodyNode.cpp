/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/interface/BodyNode.h"
#include "roly/interface/topics/ArtisticTopic.h"
#include "roly/interface/topics/ExpressiveTopic.h"
#include "tron2/robot/common/ExtraTopic.h"
#include "tron2/robot/RobotSystem.h"

namespace roly
{    
const std::string BodyNode::BODY_EXPRESSIVE = "express";
const std::string BodyNode::BODY_ARTISTIC = "art";

BodyNode::BodyNode() : tron2::Node(tron2::RobotSystem::eNODE_BODYROLE, tron2::RobotSystem::BODYROLE_NODE)
{
    fillTopics();
}

void BodyNode::fillTopics()
{
    // build topics map
    addCode(eBODY_EXPRESSIVE, BODY_EXPRESSIVE);
    addCode(eBODY_ARTISTIC, BODY_ARTISTIC);
    addCode(tron2::Node::eEXTRA_TOPIC, tron2::Node::EXTRA_TOPIC);
}

tron2::Topic* BodyNode::getTopic4Channel(int channel)
{                
    switch (channel)
    {
        case eBODY_EXPRESSIVE_CHANNEL:
        {
            return new ExpressiveTopic();
            break;
        }            
        case eBODY_ARTISTIC1_CHANNEL: 
        case eBODY_ARTISTIC2_CHANNEL: 
        {
            return new ArtisticTopic();
            break;
        }            
        case eBODY_EXTRA_CHANNEL: 
        {
            return new tron2::ExtraTopic();
            break;
        }            
        default:
            return nullptr;
    }        
}        

}