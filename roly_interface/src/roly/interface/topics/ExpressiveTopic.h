#ifndef __ROLY_INTERFACE_EXPRESSIVETOPIC_H
#define __ROLY_INTERFACE_EXPRESSIVETOPIC_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron2/robot/Topic.h"

namespace roly
{
// Concepts definition for the body expressive topic
 class ExpressiveTopic : public tron2::Topic
{
 public:
    /*! expressive concepts  */
    enum eConcepts
    {
        eEXPRESS_FEELING,                   /*! express given feeling */
        eEXPRESS_HALT,                        /*! halt expressive action */
        eEXPRESS_DIM
    };

    /*! expressive concepts */    
    const std::string EXPRESS_FEELING = "feel";      /*! set feeling to express (integer) */
    const std::string EXPRESS_HALT = "halt";          /*! halt expression */

 public:    
    ExpressiveTopic(); 
    
 private: 
    virtual void fillConcepts();      
    
};
}
#endif
