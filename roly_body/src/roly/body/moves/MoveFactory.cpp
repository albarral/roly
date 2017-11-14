/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/body/moves/MoveFactory.h"

namespace roly
{
MoveFactory::MoveFactory()
{
    // default values
    defFreq = 1.0;    
    defAngle = 0.0;
    defAmp = 30.0;
}

CyclicMove MoveFactory::computeMove(int type)
{
    CyclicMove oCyclicMove;    

    switch (type)
    {
        case MoveFactory::eMOV_LINE:
            this->createMoveLine(oCyclicMove);
            break;            
        case MoveFactory::eMOV_CIRCLE:
            this->createMoveCircle(oCyclicMove);
            break;
        case MoveFactory::eMOV_ELLIPSE:
            this->createMoveEllipse(oCyclicMove);
            break;
//        case MoveFactory::eMOV_PAJARITA:                
//            this->createMovePajarita(oCyclicMove);
//            break;
    }
    
    return oCyclicMove;
}

void MoveFactory::createMoveLine(CyclicMove& oCyclicMove)
{
    oCyclicMove.setSimple();
    oCyclicMove.setFreq1(defFreq);
    oCyclicMove.setAngle1(defAngle);
    oCyclicMove.setAmp1(defAmp);
}

void MoveFactory::createMoveCircle(CyclicMove& oCyclicMove)
{
    // a circle is an ellipse with both axes of same size
    createMoveEllipse(oCyclicMove);

    oCyclicMove.setAmp2(oCyclicMove.getAmp1());
}

void MoveFactory::createMoveEllipse(CyclicMove& oCyclicMove)
{
    oCyclicMove.setComposed();
    // same freq
    oCyclicMove.setFreq1(defFreq);
    oCyclicMove.setFreq2(defFreq);
    // ortogonal relationship
    oCyclicMove.setAngle1(defAngle);
    oCyclicMove.setAngle2(defAngle+90);
    // 0.5 relation factor
    oCyclicMove.setAmp1(defAmp);
    oCyclicMove.setAmp2(defAmp*0.5);
    // 90 degrees phase
    oCyclicMove.setPhase(90);
}
}
