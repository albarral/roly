/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/bodycoms/modules/BodyAware.h"

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
    float value;

    // inform bus with arm axes positions
    if (oArmAxesListener.sensePan(value))
        pBodyBus->getSI_ARM_PAN().setValue(value);        
    if (oArmAxesListener.senseTilt(value))
        pBodyBus->getSI_ARM_TILT().setValue(value);                
    if (oArmAxesListener.senseRadial(value))        
        pBodyBus->getSI_ARM_RADIUS().setValue(value);
        
        // inform bus with arm axes speeds
    if (oArmAxesListener.sensePanSpeed(value))
        pBodyBus->getSI_ARM_PANSPEED().setValue(value);    
    if (oArmAxesListener.senseTiltSpeed(value))
        pBodyBus->getSI_ARM_TILTSPEED().setValue(value);
    if (oArmAxesListener.senseRadialSpeed(value))
        pBodyBus->getSI_ARM_RADIALSPEED().setValue(value);        
}

}