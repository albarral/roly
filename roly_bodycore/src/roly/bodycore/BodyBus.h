#ifndef __ROLY_BODYCORE_BODYBUS_H
#define __ROLY_BODYCORE_BODYBUS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <opencv2/core/core.hpp>

#include "roly/bodycore/ArtisticBus.h"
#include "tron/control/brooks/control.h"
#include "tron/control/brooks/control2.h"
#include "tron/control/brooks/control3.h"
#include "tron/control/brooks/controlT.h"
#include "tron/control/brooks/inhibition.h"
#include "tron/control/brooks/sensor.h"
#include "tron/control/brooks/sensor3.h"

namespace roly
{
class BodyBus
{
    private:        
        bool benabled;

        // INHIBITIONS
        tron::Inhibition CO_INHIBIT_EXPRESSIVE;       // inhibit expressive module
        tron::Inhibition CO_INHIBIT_COMFORTABLE;    // inhibit comfortable module
        
        // CONTROLS                
        // Artistic modules
        ArtisticBus oArtisticBus1;
        ArtisticBus oArtisticBus2;
        
        // Expressive module
        tron::Control2 CO_EXPRESSIVE_ACTION;   // action to express 
        tron::Control CO_EXPRESSIVE_HALT;                // halt any ongoing action expression        
        
        // ArmComfort module
        tron::ControlT<cv::Vec3f> CO_RELAX_POSTURE;  // relax posture (pan, tilt, radial)
        tron::Control2 CO_RELAX_TILT;                 // relax position for pan axis
        tron::Control2 CO_RELAX_PAN;                 // relax position for pan axis
        // ArmSense module
        tron::Sensor SO_ARM_MOVING;                // arm moving state (boolean)
        tron::Sensor SO_ARM_COMFORT;             // arm comfort state (boolean)
        tron::Sensor3 SO_ARM_TIRED;                 // arm tired time (secs)
                
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
        tron::Inhibition& getCO_INHIBIT_EXPRESSIVE() {return CO_INHIBIT_EXPRESSIVE;};
        tron::Inhibition& getCO_INHIBIT_COMFORTABLE() {return CO_INHIBIT_COMFORTABLE;};

        // CONTROLS        
        // Artistic modules
        ArtisticBus& getArtisticBus1() {return oArtisticBus1;};
        ArtisticBus& getArtisticBus2() {return oArtisticBus2;};
        
        // Expressive module
        tron::Control2& getCO_EXPRESSIVE_ACTION() {return CO_EXPRESSIVE_ACTION;};
        tron::Control& getCO_EXPRESSIVE_HALT() {return CO_EXPRESSIVE_HALT;};

        // ArmSense module
        tron::ControlT<cv::Vec3f>& getCO_RELAX_POSTURE() {return CO_RELAX_POSTURE;};
        tron::Sensor& getSO_ARM_MOVING() {return SO_ARM_MOVING;};
        tron::Sensor& getSO_ARM_COMFORT() {return SO_ARM_COMFORT;};
        tron::Sensor3& getSO_ARM_TIRED() {return SO_ARM_TIRED;};
        
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
