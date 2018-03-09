#ifndef __ROLY_BODYMANAGER_H
#define __ROLY_BODYMANAGER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "roly/bodycore/BodyBus.h"
//#include "amy/arm/config/ArmConfig.h"
#include "roly/body/modules/Artistic.h"
#include "roly/body/modules/Expressive.h"
#include "roly/body/modules/ComfortableArm.h"
#include "roly/body/modules/BodyModule.h"

namespace roly
{
// This class manages a robot's arm.
// It is composed of various modules, each running its own thread. 
// Modules are distributed on levels.     
class BodyManager
{
    private:
        static log4cxx::LoggerPtr logger;
        bool blaunched;     // indicates when the manager has been launched   
        //AmyConfig oAmyConfig;        
        BodyBus* pBodyBus;        // access to body bus
        int topLevel; // allow activation of modules until this level
        // modules ...
        // level 3
        Artistic oArtistic;
        // level 2
        Expressive oExpressive;
        // level 1
        ComfortableArm oComfortableArm;
        std::vector<BodyModule*> listModules;      // list of modules (pointers)

    public:
        BodyManager();
        ~BodyManager();

       // launches the arm manager to handle the specified robot arm (returns false if something fails)
       bool launch(BodyBus& oBodyBus);
       // ends the arm manager
       bool end();
       bool isLaunched() {return blaunched;};                
       
       friend class ArmTest;
       
private:
    // initialize control architecture (organize in levels)
    void initArchitecture();
    // show description of control architecture
    void showArchitecture();

    // initialize modules
    void initModules();
    // starts the task's modules 
    void startModules();        
    // stops the tasks' modules
    void stopModules();        
    
    
   // init the modules of a level
    void initLevel(int level);        
   // start the modules of a level
    void startLevel(int level);        
   // stop the modules of a level
    void stopLevel(int level);            
};

}    
#endif
