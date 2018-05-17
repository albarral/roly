/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"
#include <opencv2/core/core.hpp>

#include "roly/body/modules/Comfort.h"
#include "roly/bodycore/config/ComfortConfig.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr Comfort::logger(Logger::getLogger("roly.body"));

Comfort::Comfort()
{
    modName = "Comfort";
}

//Comfort::~Comfort()
//{
//}

void Comfort::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}


void Comfort::first()
{
    // config
    ComfortConfig oComfortConfig;
    int* pPosture = oComfortConfig.getRelaxPosture();
    for (int i=0; i<3; i++)
        relaxPosture[i] = pPosture[i];    
    maxTiredTime = oComfortConfig.getTiredTime4Relax();
    
    // start at sense state
    setState(eSTATE_SENSE);    
    log4cxx::NDC::push(modName);  
    
    // inform relax posture to ArmSense module
    cv::Vec3f posture = {(float)relaxPosture[0], (float)relaxPosture[1], (float)relaxPosture[2]};
    pBodyBus->getCO_RELAX_POSTURE().request(posture);
}
                    
void Comfort::loop()
{
    senseBus();
    
    // skip if module is inhibited
    if (binhibited)            
        return;

    int stableCycles = tron::Module3::getStable();
    
    // if state changed show name
    if (stableCycles == 0)
        showState();
    
    switch (getState())
    {
        case eSTATE_SENSE:         
            
            // if arm still && not in comfort & too tired -> RELAX
            if (!barmMoving && !bcomfortZone && tiredTime > maxTiredTime)
                setState(eSTATE_RELAX);
            break;

        case eSTATE_RELAX:            

            // on relax request relax posture 
            requestComfortPosture();
            // and -> WAIT
            setState(eSTATE_WAIT);
            break;

        case eSTATE_WAIT:            

            // stay for a while and -> SENSE
            if (stableCycles > 5)
                setState(eSTATE_SENSE);
            break;
    }  
    
    //writeBus();
}

void Comfort::senseBus()
{
    // check inhibited control
    binhibited = pBodyBus->getCO_INHIBIT_COMFORTABLE().isRequested();
    
    // sense arm posture
    barmMoving = pBodyBus->getSO_ARM_MOVING().getValue();
    bcomfortZone = pBodyBus->getSO_ARM_COMFORT().getValue();
    tiredTime = pBodyBus->getSO_ARM_TIRED().getValue();
}


void Comfort::requestComfortPosture()
{
    // request arm relaxed posture
    oArmClient.setPan(relaxPosture[0]);
    oArmClient.setTilt(relaxPosture[1]);
    oArmClient.setRadial(relaxPosture[2]);
}


void Comfort::writeBus()
{
    // nothing to do here    
}

void Comfort::showState()
{
    switch (getState())
    {
        case eSTATE_SENSE:
            LOG4CXX_INFO(logger, ">> sense");
            break;

        case eSTATE_RELAX:
            LOG4CXX_INFO(logger, ">> relax");
            break;

        case eSTATE_WAIT:
            LOG4CXX_INFO(logger, ">> wait");
            break;
    }   // end switch    
}


}