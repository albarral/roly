/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/body/moves/ArmFigure.h"

namespace roly
{
ArmFigure::ArmFigure()
{
    figure = ArmFigure::eFIGURE_UNDEFINED;  // undefined
    freq = 0.0;
    size = 0.0;
    relFactor = 0.0;
    orientation = 0.0;
}

}
