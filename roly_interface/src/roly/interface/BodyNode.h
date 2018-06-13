#ifndef __ROLY_INTERFACE_BODYNODE_H
#define __ROLY_INTERFACE_BODYNODE_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron2/robot/Node.h"
#include "tron2/robot/Topic.h"

namespace roly
{
// Definition of body node topics
 class BodyNode : public tron2::Node
{
public:
    /*! body topics */
    enum eBodyTopics
    {
//        eBODY_COMFORTABLE,            /*! comfortable topic */
        eBODY_EXPRESSIVE,                /*! expressive topic */
        eBODY_ARTISTIC,                     /*! artistic topic */
        eBODY_DIM
    };

    /*! body node channels */
    enum eBodyChannels
    {
        eBODY_EXPRESSIVE_CHANNEL,      /*! expressive channel */
        eBODY_ARTISTIC1_CHANNEL,         /*! artistic 1 channel */
        eBODY_ARTISTIC2_CHANNEL,         /*! artistic 2 channel */
        eBODY_EXTRA_CHANNEL,              /*! extra channel  */
        eBODY_CHANNELS_DIM
    };
    
    /*! body topic names */
//    static const std::string BODY_COMFORTABLE;        // uncontrollable behaviour
    static const std::string BODY_EXPRESSIVE;
    static const std::string BODY_ARTISTIC;

 public:     
     BodyNode();
     
     static tron2::Topic* getTopic4Channel(int channel);  
     
private:
     virtual void fillTopics();
};
}
#endif
