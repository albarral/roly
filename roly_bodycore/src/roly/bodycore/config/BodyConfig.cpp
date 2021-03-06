/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycore/config/BodyConfig.h"

namespace roly
{    
// Constructor
BodyConfig::BodyConfig ()
{    
    modulesFreq = 10;  // 10 Hz
    behaviourLevels = 4;
    
    angleTol = 5.0;     // 5 degrees
    radiusTol = 5.0;    // 5 cm
}

//BodyConfig::~BodyConfig()
//{
//}
}

