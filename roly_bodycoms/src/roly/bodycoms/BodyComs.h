#ifndef __ROLY_BODYCOMS_BODYCOMS_H
#define __ROLY_BODYCOMS_BODYCOMS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "roly/bodycore/BodyBus.h"
//#include "roly/bodycore/config/AmyConfig.h"
#include "roly/bodycoms/modules/BodyAware.h"
//#include "roly/bodycoms/modules/BodyServer.h"

namespace roly
{
class BodyComs
{
private:    
    static log4cxx::LoggerPtr logger;      
    //AmyConfig oAmyConfig;
    BodyAware oBodyAware;            // communications module to inspect sensor info from external nodes
//    BodyServer oBodyServer;        // communications module to listen to control commands from external nodes

public:
  BodyComs();
  ~BodyComs();

   // launches the coms modules
   bool launch(BodyBus& oBodyBus);
   // ends the coms modules
   bool end();
   
    // checks if roly body end has been requested
    bool checkEndRequested();      
};
}		

#endif
