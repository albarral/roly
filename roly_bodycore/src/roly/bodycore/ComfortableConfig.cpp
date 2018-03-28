/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycore/ComfortableConfig.h"

namespace roly
{    
// Constructor
ComfortableConfig::ComfortableConfig ()
{    
    angleTol = 5.0;
    radiusTol = 5.0;
    tiredSensitivity4Still  = 20.0;        // 20 units/s
    tiredSensitivity4Moving = 2.0;        // 2 units/s
    relaxPosture[0] = 10;            // relax posture (pan = 10, tilt = 20, radius = 40)
    relaxPosture[1] = 20; 
    relaxPosture[2] = 40; 
}

//ComfortableConfig::~ComfortableConfig()
//{
//}
}

