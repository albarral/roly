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
#include "roly/body/modules/ArmSense.h"
#include "roly/body/modules/Artistic.h"
#include "roly/body/modules/Expressive.h"
#include "roly/body/modules/Comfort.h"
#include "roly/body/modules/BodyModule.h"

namespace roly
{
// This class manages a robot's body role.
// It is composed of various modules, each running its own thread. 
// Modules are distributed in levels.     
class BodyManager
{
    private:
        static log4cxx::LoggerPtr logger;
        bool blaunched;     // indicates when the manager has been launched   
        int topLevel; // allow activation of modules until this level
        // modules ...
        // level 4
        Comfort oComfort;
        // level 3
        Artistic oArtistic1;
        Artistic oArtistic2;
        // level 2
        Expressive oExpressive;
        // level 1
        ArmSense oArmSense;
        std::vector<BodyModule*> listModules;      // list of modules (pointers)

    public:
        BodyManager();
        ~BodyManager();

       // launches the body manager (returns false if something fails)
       bool launch(BodyBus& oBodyBus);
       // ends the body manager
       bool end();
       bool isLaunched() {return blaunched;};                
              
private:
    // initialize control architecture (organize in levels)
    void initArchitecture();
    // show description of control architecture
    void showArchitecture();

    // initialize modules
    void initModules(BodyBus& oBodyBus, float freq);
    // starts the task's modules 
    void startModules();        
    // stops the tasks' modules
    void stopModules();        
    
    
   // init the modules of a level
    void initLevel(int level, BodyBus& oBodyBus, float freq);        
   // start the modules of a level
    void startLevel(int level);        
   // stop the modules of a level
    void stopLevel(int level);            
};

}    
#endif
