#ifndef __ROLY_BODYCORE_BODYBUS_H
#define __ROLY_BODYCORE_BODYBUS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "tuly/control/brooks/controlT.h"

namespace roly
{
class BodyBus
{
    private:        
        bool benabled;
        
        // ArmMover
        tuly::ControlT<int> CO_MOVER_TYPE;       // set movement type
        tuly::ControlT<bool> CO_MOVER_ACTION;    // start/stop movement
        tuly::ControlT<int> CO_MOVER_TURN;       // change movement orientation
        tuly::ControlT<bool> CO_MOVER_WIDER;    // change movement width
        tuly::ControlT<bool> CO_MOVER_TALLER;    // change movement height
        tuly::ControlT<bool> CO_MOVER_FASTER;    // change movement speed
        
    public:
        BodyBus();
        //~BodyBus();
        
        void init();        
        bool isEnabled() {return benabled;};
        
        // CONTROLS
        // ArmMover
        tuly::ControlT<int>& getCO_MOVER_TYPE() {return CO_MOVER_TYPE;};
        tuly::ControlT<bool>& getCO_MOVER_ACTION() {return CO_MOVER_ACTION;};
        tuly::ControlT<int>& getCO_MOVER_TURN() {return CO_MOVER_TURN;};
        tuly::ControlT<bool>& getCO_MOVER_WIDER() {return CO_MOVER_WIDER;};
        tuly::ControlT<bool>& getCO_MOVER_TALLER() {return CO_MOVER_TALLER;};
        tuly::ControlT<bool>& getCO_MOVER_FASTER() {return CO_MOVER_FASTER;};
                
        std::string toString();
};

}    
#endif
