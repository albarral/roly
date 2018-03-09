#ifndef __ROLY_BODYMAIN_BODYCONTROL_H
#define __ROLY_BODYMAIN_BODYCONTROL_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "roly/bodycore/BodyBus.h"
#include "roly/body/BodyManager.h"
#include "roly/bodycoms/BodyComs.h"

namespace roly
{
// This class is used to control the body roles.
// It instantiates the control bus & talk objects, and launches the body manager.
class BodyControl
{
    private:
        static log4cxx::LoggerPtr logger;
        BodyBus oBodyBus;                            
        BodyManager oBodyManager;
        BodyComs oBodyComs;

    public:
        BodyControl();
        ~BodyControl();

       // launches the body manager and body coms (returns false if something fails)
       bool launch();
       // ends all modules
       bool end();

        // checks if end process has been requested from outside
        bool checkEndRequested();        
        
        // shows the present values of all bus elements
        void showBusState();        
        
        // access body bus (JUST FOR TEST)
        BodyBus& getBodyBus4Test() {return oBodyBus;};        
};

}    
#endif
