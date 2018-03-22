/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/body/moves/MoveFactory.h"
#include "maty/math/Angle.h"

namespace roly
{
MoveFactory::MoveFactory()
{
    bdual = false;
}

//MoveFactory::~MoveFactory()
//{
//}


void MoveFactory::createLine(float amplitude, float angle, float freq)
{
    bdual = false;
    oCyclicMove1.setFreq(freq);
    oCyclicMove1.setAngle(angle);
    oCyclicMove1.setAmp(amplitude);
}

void MoveFactory::createCircle(float amplitude, int direction, float freq)
{
    // a circle is an ellipse with relative factor 1.0  ... 
    createEllipse(amplitude, amplitude, 0.0, direction, freq);
}

void MoveFactory::createEllipse(float amplitude, float height, float angle, int direction, float freq)
{
    bdual = true;
    // same freq
    oCyclicMove1.setFreq(freq);
    oCyclicMove2.setFreq(freq);
    // orthogonal relationship
    // keep angles inside limits [0, 360)    
    float angle2 = maty::Angle::inLimits(angle + 90.0);
    oCyclicMove1.setAngle(angle);
    oCyclicMove2.setAngle(angle2);
    oCyclicMove1.setAmp(amplitude);
    oCyclicMove2.setAmp(height);
    // 90 degrees phase difference
    oCyclicMove1.setPhase(0);
    oCyclicMove2.setPhase(90);
}

void MoveFactory::updateFreq(float freq)
{
    // if two components
    if (bdual)
    {
        if (oCyclicMove1.getFreq() != 0.0 && oCyclicMove2.getFreq() != 0.0)
        {
            // keep relative frequency
            float relFreq = oCyclicMove2.getFreq() / oCyclicMove1.getFreq();
            oCyclicMove1.setFreq(freq);
            oCyclicMove2.setFreq(freq * relFreq);
        }
    }
    else          
        oCyclicMove1.setFreq(freq);
}

void MoveFactory::updateAmplitude(float amplitude)
{
    // if two components
    if (bdual)
    {
        if (oCyclicMove1.getAmp() != 0.0 && oCyclicMove2.getAmp() != 0.0)
        {
            // keep relative factor
            float relFactor = oCyclicMove2.getAmp() / oCyclicMove1.getAmp();
            oCyclicMove1.setAmp(amplitude);
            oCyclicMove2.setAmp(amplitude * relFactor);
        }
    }
    else
        oCyclicMove1.setAmp(amplitude);
}

void MoveFactory::updateAngle(float angle)
{
    // if two components
    if (bdual)
    {
        // keep relative angle
        float relAngle = oCyclicMove2.getAngle() - oCyclicMove1.getAngle();
        oCyclicMove1.setAngle(angle);
        // keep angles inside limits [0, 360)    
        float angle2 = maty::Angle::inLimits(angle + relAngle);
        oCyclicMove2.setAngle(angle2);       
    }
    else        
        oCyclicMove1.setAngle(angle);
}

}
