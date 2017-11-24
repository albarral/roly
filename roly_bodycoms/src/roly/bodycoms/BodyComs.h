#ifndef __ROLY_BODYCOMS_BODYCOMS_H
#define __ROLY_BODYCOMS_BODYCOMS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "roly/bodycore/BodyBus.h"
#include "roly/bodycore/AmyTalker.h"
//#include "roly/bodycore/config/AmyConfig.h"
#include "roly/bodycoms/modules/BodyCommander.h"
#include "roly/bodycoms/modules/BodyInspector.h"

namespace roly
{
class BodyComs
{
private:    
    static log4cxx::LoggerPtr logger;      
    //AmyConfig oAmyConfig;
    BodyCommander oBodyCommander;   // communications module for commanding control info
    BodyInspector oBodyInspector;

public:
  BodyComs();
  ~BodyComs();

   // launches the coms modules
   bool launch(BodyBus& oBodyBus, AmyTalker& oAmyTalker);
   // ends the coms modules
   bool end();
   
    // checks if roly body end has been requested
    bool checkEndRequested();      
};
}		

#endif
