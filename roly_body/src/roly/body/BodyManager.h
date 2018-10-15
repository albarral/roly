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
#include "roly/body/modules/ArmSense2.h"
#include "roly/body/modules/Artistic2.h"
#include "roly/body/modules/Expressive2.h"
#include "roly/body/modules/Comfort2.h"
#include "tron/control/Module4.h"

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
//        Comfort oComfort;
        Comfort2 oComfort2;
        // level 3
        Artistic2 oArtistic1;
        Artistic2 oArtistic2;
        // level 2
//        Expressive oExpressive;
        Expressive2 oExpressive2;
        // level 1
        ArmSense2 oArmSense2;
        std::vector<tron::Module4*> listModules1;      // list of modules (level 1)
        std::vector<tron::Module4*> listModules2;      // list of modules (level 2)
        std::vector<tron::Module4*> listModules3;      // list of modules (level 3)
        std::vector<tron::Module4*> listModules4;      // list of modules (level 4)

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
    void initArchitecture(BodyBus& oBodyBus);
    // show description of control architecture
    void showArchitecture();

    // starts the task's modules 
    void startModules(float freq);        
    // stops the tasks' modules
    void stopModules();        
    
    
   // start the modules of a level
    void startLevel(int level, float freq);        
   // stop the modules of a level
    void stopLevel(int level);
    // clear modules from level
    void clearLevel(int level);
    
    std::vector<tron::Module4*>* getModules4Level(int level);
};

}    
#endif
