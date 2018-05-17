#ifndef __ROLY_BODYCORE_ARTISTICBUS_H
#define __ROLY_BODYCORE_ARTISTICBUS_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "tron/control/brooks/control.h"
#include "tron/control/brooks/control2.h"
#include "tron/control/brooks/control3.h"
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
        tron::Control2 CO_ARTISTIC_FIGURE;       // id of artistic figure to implement
        tron::Control3 CO_ARTISTIC_FREQ;       // frequency of cyclic figure (Hz) 
        tron::Control3 CO_ARTISTIC_SIZE;        // size of cyclic figure (degrees)
        tron::Control3 CO_ARTISTIC_ORIENTATION;  // orientation of cyclic figure (degrees)
        tron::Control3 CO_ARTISTIC_RELFACTOR;    // relative xy factor of cyclic figure 
        tron::Control CO_ARTISTIC_HALT;                // halt ongoing artistic movement
        
    public:
        ArtisticBus();
        //~ArtisticBus();
                
        // INHIBITIONS
        tron::Inhibition& getCO_INHIBIT_ARTISTIC() {return CO_INHIBIT_ARTISTIC;};

        // CONTROLS        
        tron::Control2& getCO_ARTISTIC_FIGURE() {return CO_ARTISTIC_FIGURE;};
        tron::Control3& getCO_ARTISTIC_FREQ() {return CO_ARTISTIC_FREQ;};
        tron::Control3& getCO_ARTISTIC_SIZE() {return CO_ARTISTIC_SIZE;};
        tron::Control3& getCO_ARTISTIC_ORIENTATION() {return CO_ARTISTIC_ORIENTATION;};
        tron::Control3& getCO_ARTISTIC_RELFACTOR() {return CO_ARTISTIC_RELFACTOR;};
        tron::Control& getCO_ARTISTIC_HALT() {return CO_ARTISTIC_HALT;};
        
        std::string toString();
};

}    
#endif
