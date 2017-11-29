/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>
#include "log4cxx/ndc.h"

#include "roly/body/BodyManager.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr BodyManager::logger(Logger::getLogger("roly.body"));

// Constructor
BodyManager::BodyManager ()
{    
    blaunched = false;
    topLevel = 2;       
}

// Destructor
BodyManager::~BodyManager ()
{
    listModules.clear();
}


bool BodyManager::launch(BodyBus& oBodyBus, AmyTalker& oAmyTalker)
{  
    // launch it if not launched yet
    if (!blaunched)
    {
        log4cxx::NDC::push("BodyManager");   	
        LOG4CXX_INFO(logger, "Launching ");

        // skip if bus or talk not enabled
        if (!oBodyBus.isEnabled() || !oAmyTalker.isEnabled())
        {      
            LOG4CXX_ERROR(logger, "launch failed: bus or talk not enabled!");                    
            return false;
        }
        
        // store pointers to external objects
        pBodyBus = &oBodyBus;        
        pAmyTalker = &oAmyTalker;        
                
        LOG4CXX_INFO(logger, "top level: " << topLevel);
        // organize control architecture in levels
        initArchitecture();
        showArchitecture();
        // init modules & start them
        initModules();
        startModules();
        
        blaunched = true;    
    }
    // report problems
    else
        LOG4CXX_ERROR(logger, "Can't launch BodyManager: already launched!");        
    
    return blaunched;
}

bool BodyManager::end()
{
    stopModules();
}

void BodyManager::initArchitecture()
{
    // LEVEL 1    
    int nivel = 1;
    
    // arm mover
    oArmMover.setLevel(nivel);
    listModules.push_back(&oArmMover);
    // comfortable arm
    oComfortableArm.setLevel(nivel);
    listModules.push_back(&oComfortableArm);

    nivel = 2;
    
    // expressive
    oExpressive.setLevel(nivel);
    listModules.push_back(&oExpressive);
}

void BodyManager::showArchitecture()
{
    LOG4CXX_INFO(logger, ">> control architecture ...");
    for (BodyModule* pModule : listModules)
    {
        LOG4CXX_INFO(logger, "level " << std::to_string(pModule->getLevel()) << ": module " << pModule->getModuleName());        
    }        
}

void BodyManager::initModules()
{    
    LOG4CXX_INFO(logger, "INIT MODULES ...");

    for (int i=0; i<=topLevel; i++)
    {
        initLevel(i);
    }
}

void BodyManager::startModules()
{
    LOG4CXX_INFO(logger, "STARTING MODULES ...");

    int microsWait = 100000;  // 100ms
    for (int i=0; i<=topLevel; i++)
    {
        startLevel(i);
        usleep(microsWait);
    }
}

void BodyManager::stopModules()
{    
    LOG4CXX_INFO(logger, "STOPPING MODULES ...");

    if (!blaunched)
        return;

    for (int i=topLevel; i>=0; i--)
    {
        stopLevel(i);
    }
}

void BodyManager::initLevel(int num)
{    
    LOG4CXX_INFO(logger, ">> INIT level " << num);       

    //float freq = pAmyConfig->getModulesFreq();
    float freq = 10; // TEMP to get from config

    BodyBus& oBodyBus = *pBodyBus;
    AmyTalker& oAmyTalker = *pAmyTalker;
    
    // init BodyModule's
    for (BodyModule* pModule : listModules)
    {
        if (pModule->getLevel() == num)
        {                        
            pModule->init();
            pModule->connect(oBodyBus, oAmyTalker);
            pModule->setFrequency(freq);  
        }
    }
}

void BodyManager::startLevel(int num)
{
    LOG4CXX_INFO(logger, ">> START level " << num);

    // init BodyModule's
    for (BodyModule* pModule : listModules)
    {
        if (pModule->getLevel() == num)
        {
            if (pModule->isEnabled() && pModule->isConnected())
                pModule->on();
        }
    }
}

void BodyManager::stopLevel(int num)
{
    LOG4CXX_INFO(logger, ">> STOP level " << num);

    // stop BodyModule's
    for (BodyModule* pModule : listModules)
    {
        if (pModule->getLevel() == num && pModule->isOn())
        {            
            pModule->off();
            pModule->wait();
        }
    }
}

}



