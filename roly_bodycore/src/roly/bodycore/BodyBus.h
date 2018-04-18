#ifndef __ROLY_BODYCORE_BODYBUS_H
#define __ROLY_BODYCORE_BODYBUS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "tron/control/brooks/control.h"
#include "tron/control/brooks/control2.h"
#include "tron/control/brooks/control3.h"
#include "tron/control/brooks/inhibition.h"
#include "tron/control/brooks/sensor3.h"

namespace roly
{
class BodyBus
{
    private:        
        bool benabled;

        // INHIBITIONS
        tron::Inhibition CO_INHIBIT_ARTISTIC;       // inhibit artistic module
        tron::Inhibition CO_INHIBIT_EXPRESSIVE;       // inhibit expressive module
        tron::Inhibition CO_INHIBIT_COMFORTABLE;    // inhibit comfortable module
        
        // CONTROLS                
        // Artistic module
        tron::Control2 CO_ARTISTIC_FIGURE;       // id of artistic figure to implement
        tron::Control3 CO_ARTISTIC_FREQ;       // frequency of cyclic figure (Hz) 
        tron::Control3 CO_ARTISTIC_SIZE;        // size of cyclic figure (degrees)
        tron::Control3 CO_ARTISTIC_ORIENTATION;  // orientation of cyclic figure (degrees)
        tron::Control3 CO_ARTISTIC_RELFACTOR;    // relative xy factor of cyclic figure 
        tron::Control CO_ARTISTIC_HALT;                // halt ongoing artistic movement
        
        // Expressive module
        tron::Control2 CO_EXPRESSIVE_ACTION;   // action to express 
        tron::Control CO_EXPRESSIVE_HALT;                // halt any ongoing action expression        
                
        // SENSORS
        tron::Sensor3 SI_ARM_PAN;                  // real pan position (degrees)
        tron::Sensor3 SI_ARM_TILT;                  // real tilt position (degrees)
        tron::Sensor3 SI_ARM_RADIUS;                  // real radial position (cm)
        tron::Sensor3 SI_ARM_PANSPEED;         // real pan speed (degrees/s)
        tron::Sensor3 SI_ARM_TILTSPEED;         // real tilt speed (degrees/s)
        tron::Sensor3 SI_ARM_RADIALSPEED;         // real radial speed (cm/s)
        
    public:
        BodyBus();
        //~BodyBus();
        
        void init();        
        bool isEnabled() {return benabled;};
        
        // INHIBITIONS
        tron::Inhibition& getCO_INHIBIT_ARTISTIC() {return CO_INHIBIT_ARTISTIC;};
        tron::Inhibition& getCO_INHIBIT_EXPRESSIVE() {return CO_INHIBIT_EXPRESSIVE;};
        tron::Inhibition& getCO_INHIBIT_COMFORTABLE() {return CO_INHIBIT_COMFORTABLE;};

        // CONTROLS        
        // Artistic module
        tron::Control2& getCO_ARTISTIC_FIGURE() {return CO_ARTISTIC_FIGURE;};
        tron::Control3& getCO_ARTISTIC_FREQ() {return CO_ARTISTIC_FREQ;};
        tron::Control3& getCO_ARTISTIC_SIZE() {return CO_ARTISTIC_SIZE;};
        tron::Control3& getCO_ARTISTIC_ORIENTATION() {return CO_ARTISTIC_ORIENTATION;};
        tron::Control3& getCO_ARTISTIC_RELFACTOR() {return CO_ARTISTIC_RELFACTOR;};
        tron::Control& getCO_ARTISTIC_HALT() {return CO_ARTISTIC_HALT;};
        
        // Expressive module
        tron::Control2& getCO_EXPRESSIVE_ACTION() {return CO_EXPRESSIVE_ACTION;};
        tron::Control& getCO_EXPRESSIVE_HALT() {return CO_EXPRESSIVE_HALT;};
        
        // SENSORS
        tron::Sensor3& getSI_ARM_PAN() {return SI_ARM_PAN;};        
        tron::Sensor3& getSI_ARM_TILT() {return SI_ARM_TILT;};        
        tron::Sensor3& getSI_ARM_RADIUS() {return SI_ARM_RADIUS;};        
        tron::Sensor3& getSI_ARM_PANSPEED() {return SI_ARM_PANSPEED;};        
        tron::Sensor3& getSI_ARM_TILTSPEED() {return SI_ARM_TILTSPEED;};        
        tron::Sensor3& getSI_ARM_RADIALSPEED() {return SI_ARM_RADIALSPEED;};        
        
        std::string toString();
};

}    
#endif
