#ifndef __ROLY_BODYCORE_ARTISTICBUS_H
#define __ROLY_BODYCORE_ARTISTICBUS_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "tron/control/brooks/control.h"
#include "tron/control/brooks/ControlS.h"
#include "tron/control/brooks/inhibition.h"

namespace roly
{
// Bus connections for a specific Artistic module
class ArtisticBus
{
    private:        
        // INHIBITIONS
        tron::Inhibition CO_INHIBIT_ARTISTIC;       // inhibit artistic module
        
        // CONTROLS                
        tron::ControlS CO_ARTISTIC_FIGURE;       // name of artistic figure (words of figures category)
        tron::ControlS CO_ARTISTIC_SET;           // name of movement setting or change (words of speed, size and length categories)
        tron::ControlS CO_ARTISTIC_TURN;        // name of orientation setting or change (words of direction category) 
        tron::Control CO_ARTISTIC_HALT;           // halt ongoing artistic movement
        
    public:
        ArtisticBus();
        //~ArtisticBus();
                
        // INHIBITIONS
        tron::Inhibition& getCO_INHIBIT_ARTISTIC() {return CO_INHIBIT_ARTISTIC;};

        // CONTROLS        
        tron::ControlS& getCO_ARTISTIC_FIGURE() {return CO_ARTISTIC_FIGURE;};
        tron::ControlS& getCO_ARTISTIC_SET() {return CO_ARTISTIC_SET;};
        tron::ControlS& getCO_ARTISTIC_TURN() {return CO_ARTISTIC_TURN;};
        tron::Control& getCO_ARTISTIC_HALT() {return CO_ARTISTIC_HALT;};
        
        std::string toString();
};

}    
#endif
