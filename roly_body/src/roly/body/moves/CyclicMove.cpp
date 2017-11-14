/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/body/moves/CyclicMove.h"
//#include "amy/math/Angle.h"

namespace roly
{
CyclicMove::CyclicMove()
{
    bsimple = true;
    freq1 = 0.0;
    angle1 = 0.0;
    amp1 = 0.0;
    freq2 = 0.0;
    angle2 = 0.0;
    amp2 = 0.0;
    phase = 0.0;
    setElasticity(0.1);
}

void CyclicMove::setElasticity(float value)
{
    elasticity = value;
    changeUp = 1.0+elasticity;
    changeDown = 1.0/changeUp;
}
void CyclicMove::makeWider(bool bchange)
{
    float change = (bchange ? changeUp : changeDown);
    // just affects first component
    amp1 = change*amp1;    
}

void CyclicMove::makeTaller(bool bchange)
{
    float change = (bchange ? changeUp : changeDown);
    // just affects second component
    amp2 = change*amp2;    
}

void CyclicMove::makeFaster(bool bchange)
{
    float change = (bchange ? changeUp : changeDown);
    // affects both components equally
    freq1 = change*freq1;
    freq2 = change*freq2;
}

void CyclicMove::makeTurn(float degrees)
{
    // affects both components equally
    angle1 += degrees;
    angle2 += degrees;
    // keep angles inside limits [0, 360)
//    angle1 = amy::Angle::inLimits(angle1);
//    angle2 = amy::Angle::inLimits(angle2);    
}

}
