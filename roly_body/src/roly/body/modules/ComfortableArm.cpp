/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "log4cxx/ndc.h"

#include "roly/body/modules/ComfortableArm.h"
#include "roly/bodycore/ComfortableConfig.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr ComfortableArm::logger(Logger::getLogger("roly.body"));

ComfortableArm::ComfortableArm()
{
    modName = "Comfortable";
    ComfortableConfig oComfortableConfig;
    int* pPosture = oComfortableConfig.getRelaxPosture();
    for (int i=0; i<3; i++)
        relaxPosture[i] = pPosture[i];    
    tolAngle = oComfortableConfig.getAngleTolerance();
    tolRadius = oComfortableConfig.getRadialTolerance();
    tiredChange4Still = getFrequency() * oComfortableConfig.getTiredSensitivity4Still();
    tiredChange4Moving = getFrequency() * oComfortableConfig.getTiredSensitivity4Moving();
}

//ComfortableArm::~ComfortableArm()
//{
//}

void ComfortableArm::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}


void ComfortableArm::first()
{
    // start at still state
    setState(eSTATE_STILL);    
    log4cxx::NDC::push(modName);   
}
                    
void ComfortableArm::loop()
{
    senseBus();
    
    // skip if module is inhibited
    if (binhibited)            
        return;

    if (isStateChanged())
        showState();
    
    senseArm();
    
    switch (getState())
    {
        case eSTATE_STILL:         
            
            updateTired(tiredChange4Still);
            // if arm moving -> MOVING
            if (barmMoving)
                setState(eSTATE_MOVING);
            // if arm still and too tired -> RELAX
            else if (!bcomfortZone && tired > 100.0)
            {
                setState(eSTATE_RELAX);
                relaxCounter = 0;
            }
            break;

        case eSTATE_MOVING:            

            updateTired(tiredChange4Moving);
            // if arm not moving -> STILL
            if (!barmMoving)
                setState(eSTATE_STILL);
            // if arm moving and too tired -> RELAX
            else if (!bcomfortZone && tired > 100.0)
            {
                setState(eSTATE_RELAX);
                relaxCounter = 0;
            }
            break;

        case eSTATE_RELAX:            

            relaxCounter++;
            if (relaxCounter == 1)
                // request relax posture once
                requestComfortPosture();
            else if (relaxCounter == 10)
            {
                if (barmMoving)
                    setState(eSTATE_MOVING);
                else
                    setState(eSTATE_STILL);
            }    
            break;
    }  
    
    //writeBus();
}

void ComfortableArm::senseBus()
{
    // check inhibited control
    binhibited = pBodyBus->getCO_INHIBIT_COMFORTABLE().isRequested();
    // sense arm posture
    armPosture[0] = pBodyBus->getSI_ARM_PAN().getValue();
    armPosture[1] = pBodyBus->getSI_ARM_TILT().getValue();
    armPosture[2] = pBodyBus->getSI_ARM_RADIUS().getValue();
    // sense arm speed
    armSpeed[0] = pBodyBus->getSI_ARM_PANSPEED().getValue(); 
    armSpeed[1] = pBodyBus->getSI_ARM_TILTSPEED().getValue();
    armSpeed[2] = pBodyBus->getSI_ARM_RADIALSPEED().getValue();
    //LOG4CXX_INFO(logger, pBodyBus->toString());    
}

void ComfortableArm::updateTired(float change)
{
    if (bcomfortZone)
    {
        if (tired > 0.0)
        {
            tired -= change;
            if (tired < 0.0)
                tired = 0.0;
        }
    }
    else
    {
        tired += change;
    }    
}


void ComfortableArm::requestComfortPosture()
{
    // request arm relaxed posture
    oArmClient.setPan(relaxPosture[0]);
    oArmClient.setTilt(relaxPosture[1]);
    oArmClient.setRadial(relaxPosture[2]);
}


void ComfortableArm::senseArm()
{    
    // check if arm is moving (some axis speed not zero)
    barmMoving = (armSpeed[0] != 0.0 || armSpeed[1] != 0.0 || armSpeed[2] != 00);

    // if distance to arm's relax posture is inside a tolerance the arm is in the comfort zone
    bcomfortZone = (fabs(relaxPosture[0] - armPosture[0]) <= tolAngle && 
            fabs(relaxPosture[1] - armPosture[1]) <= tolAngle && 
            fabs(relaxPosture[2] - armPosture[2]) <= tolRadius);
}

void ComfortableArm::writeBus()
{
    // nothing to do here    
}

void ComfortableArm::showState()
{
    switch (getState())
    {
        case eSTATE_STILL:
            LOG4CXX_INFO(logger, ">> still");
            break;

        case eSTATE_MOVING:
            LOG4CXX_INFO(logger, ">> moving");
            break;

        case eSTATE_RELAX:
            LOG4CXX_INFO(logger, ">> relax");
            break;
    }   // end switch    
}


}