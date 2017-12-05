/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycore/BodyBus.h"

namespace roly
{
// Constructor
BodyBus::BodyBus ()
{    
    benabled = false;
}

void BodyBus::init()
{
    benabled = true;
}

std::string BodyBus::toString()
{
    std::string text = "BodyBus:[CO_INHIBIT_COMFORTABLE: " + std::to_string(CO_INHIBIT_COMFORTABLE.getLoops()) + "\n" + 
        "SI_ARM_PAN: " + std::to_string(SI_ARM_PAN.getValue()) + "\n" + 
        "SI_ARM_TILT: " + std::to_string(SI_ARM_TILT.getValue()) + "\n" +        
        "SI_ARM_RADIUS: " + std::to_string(SI_ARM_RADIUS.getValue()) + "\n" +         
        "SI_ARM_PANSPEED: " + std::to_string(SI_ARM_PANSPEED.getValue()) + "\n" +         
        "SI_ARM_TILTSPEED: " + std::to_string(SI_ARM_TILTSPEED.getValue()) + "\n" +         
        "SI_ARM_RADIALSPEED: " + std::to_string(SI_ARM_RADIALSPEED.getValue()) + "\n";
    
    return text;
}

}
