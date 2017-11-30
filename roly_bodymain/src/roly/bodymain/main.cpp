/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include <vector>
#include <string>
#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "roly/bodymain/BodyControl.h"
#include "roly/bodymain/BodyTest.h"

using namespace roly;

void runBody();
// obtains user's home path
std::string getHomePath();

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("roly.body"));

// main program
int main(int argc, char** argv) 
{
    std::string home = getHomePath();
    std::string configFile = home + "/.tron/log4cxx_config_body.xml";
    log4cxx::xml::DOMConfigurator::configure(configFile);    
        
    LOG4CXX_INFO(logger, "\n\nSTART roly_body\n");

    runBody();
      
    return 0;
}

// runs the body control
void runBody()
{        
    BodyControl oBodyControl; 

    // TEST SECTION
//    BodyTest oBodyTest;
//    oBodyTest.connect2Bus(oBodyControl.getBodyBus4Test());

    // launch body control & wait for it to end        
    if (oBodyControl.launch())
    {    
        while (!oBodyControl.checkEndRequested()) 
        {
//            oBodyTest.testExpressive();

            sleep(1);            
        }    

        LOG4CXX_INFO(logger, "\nbody end requested ...\n");
        oBodyControl.end();        
    }
    else
        LOG4CXX_ERROR(logger, "BodyControl could not be launched");
        
    return;
}

std::string getHomePath()
{    
    // obtain value of HOME environment variable
    char* pVar = getenv("HOME");    
    if (pVar!=NULL)
    {
        // transform it in a string
        std::string home(pVar);
        return home;
    }
    else
        return "";
}
