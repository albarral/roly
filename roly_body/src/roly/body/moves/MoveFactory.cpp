/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/body/moves/MoveFactory.h"
#include "maty/math/Angle.h"

namespace roly
{
//MoveFactory::MoveFactory()
//{
//}

CyclicMove MoveFactory::createMove(ArmFigure& oArmFigure)
{
    CyclicMove oCyclicMove;    

    switch (oArmFigure.getFigure())
    {
        case ArmFigure::eFIGURE_LINE:
            createLineMove(oArmFigure, oCyclicMove);
            break;            
        case ArmFigure::eFIGURE_CIRCLE:
            createCircularMove(oArmFigure, oCyclicMove);
            break;
        case ArmFigure::eFIGURE_ELLIPSE:
            createEllipticMove(oArmFigure, oCyclicMove);
            break;
//        case ArmFigure::eMOV_PAJARITA:                
//            createPajaritaMove(oCyclicMove);
//            break;
    }
    
    return oCyclicMove;
}

void MoveFactory::createLineMove(ArmFigure& oArmFigure, CyclicMove& oCyclicMove)
{
    oCyclicMove.setSimple();
    oCyclicMove.setFreq1(oArmFigure.getFreq());
    oCyclicMove.setAngle1(oArmFigure.getOrientation());
    oCyclicMove.setAmp1(oArmFigure.getSize());
}

void MoveFactory::createCircularMove(ArmFigure& oArmFigure, CyclicMove& oCyclicMove)
{
    // a circle is an ellipse ... 
    createEllipticMove(oArmFigure, oCyclicMove);
    // with relative factor 1.0    
    oCyclicMove.setAmp2(oCyclicMove.getAmp1());
}

void MoveFactory::createEllipticMove(ArmFigure& oArmFigure, CyclicMove& oCyclicMove)
{
    oCyclicMove.setComposed();
    // same freq
    oCyclicMove.setFreq1(oArmFigure.getFreq());
    oCyclicMove.setFreq2(oArmFigure.getFreq());
    // orthogonal relationship
    // keep angles inside limits [0, 360)    
    float angle2 = maty::Angle::inLimits(oArmFigure.getOrientation() + 90.0);
    oCyclicMove.setAngle1(oArmFigure.getOrientation());
    oCyclicMove.setAngle2(angle2);
    // take into account the figure's relative factor
    float amp2 = oArmFigure.getSize() * oArmFigure.getRelativeFactor();
    oCyclicMove.setAmp1(oArmFigure.getSize());
    oCyclicMove.setAmp2(amp2);
    // 90 degrees phase
    oCyclicMove.setPhase(90);
}
}
