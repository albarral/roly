/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycore/config/ComfortConfig.h"

namespace roly
{    
// Constructor
ComfortConfig::ComfortConfig ()
{    
    tiredTime4Relax  = 3.0;        // 3 s
    relaxPosture[0] = 10;            // relax posture (pan = 10, tilt = 20, radius = 40)
    relaxPosture[1] = 20; 
    relaxPosture[2] = 40; 
}

//ComfortableConfig::~ComfortableConfig()
//{
//}
}

