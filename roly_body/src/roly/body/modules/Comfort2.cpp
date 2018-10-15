/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"
#include <opencv2/core/core.hpp>

#include "roly/body/modules/Comfort2.h"
#include "roly/bodycore/config/ComfortConfig.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr Comfort2::logger(Logger::getLogger("roly.body"));

Comfort2::Comfort2() : BodyBehaviour("Comfort2")
{
    addStateName("sense");
    addStateName("relax");
    addStateName("wait");
}

//Comfort2::~Comfort2()
//{
//}


void Comfort2::start()
{
    log4cxx::NDC::push(name);  
    LOG4CXX_INFO(logger, " initialized");          

    // config
    ComfortConfig oComfortConfig;
    int* pPosture = oComfortConfig.getRelaxPosture();
    for (int i=0; i<3; i++)
        relaxPosture[i] = pPosture[i];    
    maxTiredTime = oComfortConfig.getTiredTime4Relax();
    
    // start at sense state
    setState(eSTATE_SENSE);    
    LOG4CXX_INFO(logger, ">> " << getStateName());          
    
    // inform relax posture to ArmSense module
    cv::Vec3f posture = {(float)relaxPosture[0], (float)relaxPosture[1], (float)relaxPosture[2]};
    pBodyBus->getCO_RELAX_POSTURE().request(posture);
}
  
void Comfort2::sense()
{
    // check inhibited control
    inhibit(pBodyBus->getCO_INHIBIT_COMFORTABLE().isRequested());
    
    // sense arm posture
    barmMoving = pBodyBus->getSO_ARM_MOVING().getValue();
    bcomfortZone = pBodyBus->getSO_ARM_COMFORT().getValue();
    tiredTime = pBodyBus->getSO_ARM_TIRED().getValue();
}

void Comfort2::actuate()
{    
    // method skipped when behaviour inhibited

    switch (getState())
    {
        case eSTATE_SENSE:         
            
            // if arm still && not in comfort & too tired -> RELAX
            if (!barmMoving && !bcomfortZone && tiredTime > maxTiredTime)
                setState(eSTATE_RELAX);
            break;

        case eSTATE_RELAX:            

            // on relax request relax posture 
            requestComfort2Posture();
            // and -> WAIT
            setState(eSTATE_WAIT);
            waitCycles = 0;
            break;

        case eSTATE_WAIT:            

            // stay for a while and -> SENSE
            waitCycles++;
            if (waitCycles > 5)
                setState(eSTATE_SENSE);
            break;
    }  
    
    if (isStateChanged())
        LOG4CXX_INFO(logger, ">> " << getStateName());          
}

void Comfort2::requestComfort2Posture()
{
    // request arm relaxed posture
    oArmAxesClient.setPan(relaxPosture[0]);
    oArmAxesClient.setTilt(relaxPosture[1]);
    oArmAxesClient.setRadial(relaxPosture[2]);
}

}