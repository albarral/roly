#ifndef __ROLY_BODYCOMS_AMYCOMSINFORMER_H
#define __ROLY_BODYCOMS_AMYCOMSINFORMER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "comy/file/ComyFileClient.h"

namespace roly
{
// Sends commands from body modules to the arm nodes. 
// It uses comy client connections, one for each category.
class Body2Arm
{    
private:
    static log4cxx::LoggerPtr logger;      
    bool benabled;        // connected to amy control interfaces
    comy::ComyFileClient oClient2ArmCycler;   // communications client for arm cyclic category
    comy::ComyFileClient oClient2ArmAxes;   // communications client for arm axes category
        
public:
    Body2Arm();

   bool isEnabled() {return benabled;};
   void init();
   
   // sends message to arm node
   bool sendMessage(std::string message, int category);    

private:
    //  send message through specified channel
    bool sendMessage2Channel(comy::ComyFileClient& oComyClient, std::string message);
    
};
}
#endif
