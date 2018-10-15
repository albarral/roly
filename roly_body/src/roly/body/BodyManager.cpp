/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>
#include "log4cxx/ndc.h"

#include "roly/body/BodyManager.h"
#include "roly/bodycore/config/BodyConfig.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr BodyManager::logger(Logger::getLogger("roly.body"));

// Constructor
BodyManager::BodyManager ()
{    
    blaunched = false;
    topLevel = 0;       
}

// Destructor
BodyManager::~BodyManager ()
{
    for (int i=0; i<=topLevel; i++)
        clearLevel(i);
}


bool BodyManager::launch(BodyBus& oBodyBus)
{  
    // launch it if not launched yet
    if (!blaunched)
    {
        log4cxx::NDC::push("BodyManager");   	
        LOG4CXX_INFO(logger, "Launching ");

        // skip if bus not enabled
        if (!oBodyBus.isEnabled())
        {      
            LOG4CXX_ERROR(logger, "launch failed: bus not enabled!");                    
            return false;
        }
        
        // read configuration
        BodyConfig oBodyConfig;
        float freq = oBodyConfig.getModulesFreq();
        topLevel = oBodyConfig.getBehaviourLevels();
                
        LOG4CXX_INFO(logger, "top level: " << topLevel);
        // organize control architecture in levels
        initArchitecture(oBodyBus);
        showArchitecture();

        // start modules
        startModules(freq);
        
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

void BodyManager::initArchitecture(BodyBus& oBodyBus)
{
    // level 1    
    // arm sense behaviour
    oArmSense2.connect(oBodyBus);
    listModules1.push_back(new tron::Module4(oArmSense2));

    // level 2    
    // expressive behaviour
    oExpressive2.connect(oBodyBus);
    listModules2.push_back(new tron::Module4(oExpressive2));

    // level 3    
    // artistic behaviours
    oArtistic1.setID(BodyConfig::ARTISTIC1);
    oArtistic2.setID(BodyConfig::ARTISTIC2);
    oArtistic1.connect(oBodyBus);
    oArtistic2.connect(oBodyBus);
    listModules3.push_back(new tron::Module4(oArtistic1));
    listModules3.push_back(new tron::Module4(oArtistic2));

    // level 4;    
    // comfortable arm behaviour    
    oComfort2.connect(oBodyBus);
    listModules4.push_back(new tron::Module4(oComfort2));
}

void BodyManager::showArchitecture()
{
    LOG4CXX_INFO(logger, ">> control architecture ...");
    for (int i=0; i<=topLevel; i++)
    {
        LOG4CXX_INFO(logger, "level " << std::to_string(i) << ":");        
        // get list of modules for given level
        std::vector<tron::Module4*>* pLevelModules = getModules4Level(i);
        if (pLevelModules != nullptr)
        {
            // show all modules in the level
            for (tron::Module4* pModule : *pLevelModules)
            {
                LOG4CXX_INFO(logger, "module " << pModule->getBehaviour()->getName());        
            }
        }    
    }
}

void BodyManager::startModules(float freq)
{
    LOG4CXX_INFO(logger, "STARTING MODULES ...");

    int microsWait = 100000;  // 100ms
    for (int i=0; i<=topLevel; i++)
    {
        startLevel(i, freq);
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

void BodyManager::startLevel(int num, float freq)
{
    LOG4CXX_INFO(logger, ">> START level " << num);

    // get list of modules for given level
    std::vector<tron::Module4*>* pLevelModules = getModules4Level(num);
    if (pLevelModules != nullptr)
    {
        // start each module in the level
        for (tron::Module4* pModule : *pLevelModules)
        {
            if (!pModule->isOn())
            {
                pModule->setFrequency(freq);  
                pModule->on();
            }
        }
    }    
}

void BodyManager::stopLevel(int num)
{
    LOG4CXX_INFO(logger, ">> STOP level " << num);

    // get list of modules for given level
    std::vector<tron::Module4*>* pLevelModules = getModules4Level(num);
    if (pLevelModules != nullptr)
    {
        // stop each module in the level
        for (tron::Module4* pModule : *pLevelModules)
        {
            if (pModule->isOn())
            {
                pModule->off();
                pModule->wait();
            }
        }
    }    
}

void BodyManager::clearLevel(int num)
{
    LOG4CXX_INFO(logger, ">> CLEAR level " << num);

    // get list of modules for given level
    std::vector<tron::Module4*>* pLevelModules = getModules4Level(num);
    if (pLevelModules != nullptr)
    {
        // clear each module in the level (from heap)
        for (tron::Module4* pModule : *pLevelModules)
        {
            if (pModule)
                delete(pModule);                    
        }
        // finally delete modules list
        pLevelModules->clear();        
    }    
}

std::vector<tron::Module4*>* BodyManager::getModules4Level(int level)
{
    switch (level)
    {
        case 1: 
            return &listModules1;
        case 2: 
            return &listModules2;
        case 3: 
            return &listModules3;
        case 4: 
            return &listModules4;
        default: 
            return nullptr;
    }
}

}



