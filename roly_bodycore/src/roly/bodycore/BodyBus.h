#ifndef __ROLY_BODYCORE_BODYBUS_H
#define __ROLY_BODYCORE_BODYBUS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "tuly/control/brooks/control.h"
#include "tuly/control/brooks/controlT.h"
#include "tuly/control/brooks/inhibition.h"
#include "tuly/control/brooks/sensorT.h"

namespace roly
{
class BodyBus
{
    private:        
        bool benabled;

        // INHIBITIONS
        tuly::Inhibition CO_INHIBIT_ARTISTIC;       // inhibit artistic module
        tuly::Inhibition CO_INHIBIT_EXPRESSIVE;       // inhibit expressive module
        tuly::Inhibition CO_INHIBIT_COMFORTABLE;    // inhibit comfortable module
        
        // CONTROLS                
        // Artistic module
        tuly::ControlT<int> CO_ARTISTIC_FIGURE;       // id of artistic figure to implement
        tuly::ControlT<float> CO_ARTISTIC_FREQ;       // frequency of cyclic figure (Hz) 
        tuly::ControlT<float> CO_ARTISTIC_SIZE;        // size of cyclic figure (degrees)
        tuly::ControlT<float> CO_ARTISTIC_ORIENTATION;  // orientation of cyclic figure (degrees)
        tuly::ControlT<float> CO_ARTISTIC_RELFACTOR;    // relative xy factor of cyclic figure 
        tuly::Control CO_ARTISTIC_HALT;                // halt ongoing artistic movement
        
        // Expressive module
        tuly::ControlT<int> CO_EXPRESSIVE_ACTION;   // action to express 
        tuly::Control CO_EXPRESSIVE_HALT;                // halt any ongoing action expression        
                
        // SENSORS
        tuly::SensorT<float> SI_ARM_PAN;                  // real pan position (degrees)
        tuly::SensorT<float> SI_ARM_TILT;                  // real tilt position (degrees)
        tuly::SensorT<float> SI_ARM_RADIUS;                  // real radial position (cm)
        tuly::SensorT<float> SI_ARM_PANSPEED;         // real pan speed (degrees/s)
        tuly::SensorT<float> SI_ARM_TILTSPEED;         // real tilt speed (degrees/s)
        tuly::SensorT<float> SI_ARM_RADIALSPEED;         // real radial speed (cm/s)
        
    public:
        BodyBus();
        //~BodyBus();
        
        void init();        
        bool isEnabled() {return benabled;};
        
        // INHIBITIONS
        tuly::Inhibition& getCO_INHIBIT_ARTISTIC() {return CO_INHIBIT_ARTISTIC;};
        tuly::Inhibition& getCO_INHIBIT_EXPRESSIVE() {return CO_INHIBIT_EXPRESSIVE;};
        tuly::Inhibition& getCO_INHIBIT_COMFORTABLE() {return CO_INHIBIT_COMFORTABLE;};

        // CONTROLS        
        // Artistic module
        tuly::ControlT<int>& getCO_ARTISTIC_FIGURE() {return CO_ARTISTIC_FIGURE;};
        tuly::ControlT<float>& getCO_ARTISTIC_FREQ() {return CO_ARTISTIC_FREQ;};
        tuly::ControlT<float>& getCO_ARTISTIC_SIZE() {return CO_ARTISTIC_SIZE;};
        tuly::ControlT<float>& getCO_ARTISTIC_ORIENTATION() {return CO_ARTISTIC_ORIENTATION;};
        tuly::ControlT<float>& getCO_ARTISTIC_RELFACTOR() {return CO_ARTISTIC_RELFACTOR;};
        tuly::Control& getCO_ARTISTIC_HALT() {return CO_ARTISTIC_HALT;};
        
        // Expressive module
        tuly::ControlT<int>& getCO_EXPRESSIVE_ACTION() {return CO_EXPRESSIVE_ACTION;};
        tuly::Control& getCO_EXPRESSIVE_HALT() {return CO_EXPRESSIVE_HALT;};
        
        // SENSORS
        tuly::SensorT<float>& getSI_ARM_PAN() {return SI_ARM_PAN;};        
        tuly::SensorT<float>& getSI_ARM_TILT() {return SI_ARM_TILT;};        
        tuly::SensorT<float>& getSI_ARM_RADIUS() {return SI_ARM_RADIUS;};        
        tuly::SensorT<float>& getSI_ARM_PANSPEED() {return SI_ARM_PANSPEED;};        
        tuly::SensorT<float>& getSI_ARM_TILTSPEED() {return SI_ARM_TILTSPEED;};        
        tuly::SensorT<float>& getSI_ARM_RADIALSPEED() {return SI_ARM_RADIALSPEED;};        
        
        std::string toString();
};

}    
#endif
