#ifndef __ROLY_BODYCORE_BODYBUS_H
#define __ROLY_BODYCORE_BODYBUS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

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
        tuly::Inhibition CO_INHIBIT_EXPRESSIVE;       // inhibit expressive module
        tuly::Inhibition CO_INHIBIT_COMFORTABLE;    // inhibit comfortable module
        
        // CONTROLS        
        // Expressive module
        tuly::ControlT<int> CO_EXPRESSIVE_ACTION;   // action to express 
        tuly::ControlT<bool> CO_EXPRESSIVE_HALT;    // halt any ongoing action expression        
        
        // ArmMover module
        tuly::ControlT<int> CO_MOVER_TYPE;       // set movement type
        tuly::ControlT<bool> CO_MOVER_ACTION;    // start/stop movement
        tuly::ControlT<int> CO_MOVER_TURN;       // change movement orientation
        tuly::ControlT<bool> CO_MOVER_WIDER;    // change movement width
        tuly::ControlT<bool> CO_MOVER_TALLER;    // change movement height
        tuly::ControlT<bool> CO_MOVER_FASTER;    // change movement speed
        
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
        tuly::Inhibition& getCO_INHIBIT_EXPRESSIVE() {return CO_INHIBIT_EXPRESSIVE;};
        tuly::Inhibition& getCO_INHIBIT_COMFORTABLE() {return CO_INHIBIT_COMFORTABLE;};

        // CONTROLS        
        // Expressive module
        tuly::ControlT<int>& getCO_EXPRESSIVE_ACTION() {return CO_EXPRESSIVE_ACTION;};
        tuly::ControlT<bool>& getCO_EXPRESSIVE_HALT() {return CO_EXPRESSIVE_HALT;};
        // ArmMover module
        tuly::ControlT<int>& getCO_MOVER_TYPE() {return CO_MOVER_TYPE;};
        tuly::ControlT<bool>& getCO_MOVER_ACTION() {return CO_MOVER_ACTION;};
        tuly::ControlT<int>& getCO_MOVER_TURN() {return CO_MOVER_TURN;};
        tuly::ControlT<bool>& getCO_MOVER_WIDER() {return CO_MOVER_WIDER;};
        tuly::ControlT<bool>& getCO_MOVER_TALLER() {return CO_MOVER_TALLER;};
        tuly::ControlT<bool>& getCO_MOVER_FASTER() {return CO_MOVER_FASTER;};

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
