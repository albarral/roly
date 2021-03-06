/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>

#include "roly/bodymain/BodyControl.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr BodyControl::logger(Logger::getLogger("roly.body"));

// Constructor
BodyControl::BodyControl ()
{    
}

// Destructor
BodyControl::~BodyControl ()
{
}

bool BodyControl::launch() 
{      
    bool bok = false;
    LOG4CXX_INFO(logger, "Launch control of body roles");
            
    // init bus
    oBodyBus.init();

    // launch body coms
    bok = oBodyComs.launch(oBodyBus);        

    if (bok)
        // launch body manager
        bok = oBodyManager.launch(oBodyBus);        

    return bok;
}

bool BodyControl::end()
{
    // finish arm manager
    oBodyManager.end();

    // end coms
    oBodyComs.end();
}

bool BodyControl::checkEndRequested()
{
    return oBodyComs.checkEndRequested();
}

}



