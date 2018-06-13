/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/bodycoms/modules/BodyAware.h"
#include "amy/interface/ArmSensors.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr BodyAware::logger(Logger::getLogger("roly.body.coms"));

// Constructor 
BodyAware::BodyAware()
{    
   modName = "BodyAware";
   pBodyBus = 0;
   benabled = false;
 }

void BodyAware::init(BodyBus& oBodyBus)
{
    pBodyBus = &oBodyBus;
    benabled = true;
    LOG4CXX_INFO(logger, modName + " initialized");                                
}

void BodyAware::first()
{    
    log4cxx::NDC::push(modName);   	
}

void BodyAware::loop()
{
    // sense arm data
    if (oArmListener.senseChannels())
    {
        amy::AxesData& axesPositions = oArmListener.getAxesPositions();
        amy::AxesData& axesSpeeds = oArmListener.getAxesSpeeds();
        // inform bus with arm axes positions
        pBodyBus->getSI_ARM_PAN().setValue(axesPositions.pan);
        pBodyBus->getSI_ARM_TILT().setValue(axesPositions.tilt);
        pBodyBus->getSI_ARM_RADIUS().setValue(axesPositions.radial);
        // inform bus with arm axes speeds
        pBodyBus->getSI_ARM_PANSPEED().setValue(axesSpeeds.pan);
        pBodyBus->getSI_ARM_TILTSPEED().setValue(axesSpeeds.tilt);
        pBodyBus->getSI_ARM_RADIALSPEED().setValue(axesSpeeds.radial);        
    }
}

}