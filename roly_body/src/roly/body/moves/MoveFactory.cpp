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
}

MoveFactory::~MoveFactory()
{
    clear();
}

void MoveFactory::clear()
{
    listCyclicComponents.clear();        
}

maty::CyclicMove* MoveFactory::getPrimaryCyclicComponent()
{
    if (listCyclicComponents.size() > 0)
    {
        return &(listCyclicComponents.at(0));
    }
    else
        return 0;
}

maty::CyclicMove* MoveFactory::getSecondaryCyclicComponent()
{
    if (listCyclicComponents.size() > 1)
    {
        return &(listCyclicComponents.at(1));
    }
    else
        return 0;
}

void MoveFactory::createLine(float amplitude, float angle, float freq)
{
    clear();
    
    maty::CyclicMove oCyclicMove;
    oCyclicMove.setFreq(freq);
    oCyclicMove.setAngle(angle);
    oCyclicMove.setAmp(amplitude);
    
    listCyclicComponents.push_back(oCyclicMove);
}

void MoveFactory::createCircle(float amplitude, int direction, float freq)
{
    // a circle is an ellipse with relative factor 1.0  ... 
    createEllipse(amplitude, amplitude, 0.0, direction, freq);
}

void MoveFactory::createEllipse(float amplitude, float height, float angle, int direction, float freq)
{
    clear();
    
    maty::CyclicMove oCyclicMove1;
    maty::CyclicMove oCyclicMove2;
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

    listCyclicComponents.push_back(oCyclicMove1);
    listCyclicComponents.push_back(oCyclicMove2);    
}

void MoveFactory::updateFreq(float freq)
{
    // if two components
    if (listCyclicComponents.size() == 2)
    {
        maty::CyclicMove& oCyclicMove1 = listCyclicComponents.at(0);
        maty::CyclicMove& oCyclicMove2 = listCyclicComponents.at(1);
        if (oCyclicMove1.getFreq() != 0 && oCyclicMove2.getFreq() != 0)
        {
            // keep relative frequency
            float relFreq = oCyclicMove2.getFreq() / oCyclicMove1.getFreq();
            oCyclicMove1.setFreq(freq);
            oCyclicMove2.setFreq(freq * relFreq);
        }
    }
    else if (listCyclicComponents.size() == 1)
    {
        listCyclicComponents.at(0).setFreq(freq);
    }    
}

void MoveFactory::updateAmplitude(float amplitude)
{
    // if two components
    if (listCyclicComponents.size() == 2)
    {
        maty::CyclicMove& oCyclicMove1 = listCyclicComponents.at(0);
        maty::CyclicMove& oCyclicMove2 = listCyclicComponents.at(1);
        if (oCyclicMove1.getAmp() != 0 && oCyclicMove2.getAmp() != 0)
        {
            // keep relative factor
            float relFactor = oCyclicMove2.getAmp() / oCyclicMove1.getAmp();
            oCyclicMove1.setAmp(amplitude);
            oCyclicMove2.setAmp(amplitude * relFactor);
        }
    }
    else if (listCyclicComponents.size() == 1)
    {
        listCyclicComponents.at(0).setAmp(amplitude);        
    }    
}

void MoveFactory::updateAngle(float angle)
{
    // if two components
    if (listCyclicComponents.size() == 2)
    {
        maty::CyclicMove& oCyclicMove1 = listCyclicComponents.at(0);
        maty::CyclicMove& oCyclicMove2 = listCyclicComponents.at(1);
        // keep relative angle
        float relAngle = oCyclicMove2.getAngle() - oCyclicMove1.getAngle();
        oCyclicMove1.setAngle(angle);
        // keep angles inside limits [0, 360)    
        float angle2 = maty::Angle::inLimits(angle + relAngle);
        oCyclicMove2.setAngle(angle2);       
    }
    else if (listCyclicComponents.size() == 1)
    {
        listCyclicComponents.at(0).setAngle(angle);
    }    
}

}
