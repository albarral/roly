/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/body/moves/ArmMovement.h"

namespace roly
{
ArmMovement::ArmMovement()
{
    type = -1;  // undefined
    pan = 0.0;
    tilt = 0.0;
    radius = 0.0;
    millis = 0;
}

void ArmMovement::setPosture(float pan, float tilt, float rad, int time)
{
    type = ArmMovement::eTYPE_POSTURE;
    this->pan = pan;
    this->tilt = tilt;
    this->radius = rad;
    millis = time;
}

void ArmMovement::setMove(float vpan, float vtilt, float vrad, int time)
{
    type = ArmMovement::eTYPE_MOVE;
    this->pan = vpan;
    this->tilt = vtilt;
    this->radius = vrad;
    millis = time;
}
}
