#ifndef __ROLY_BODY_MOVEFACTORY_H
#define __ROLY_BODY_MOVEFACTORY_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/body/moves/ArmFigure.h"
#include "roly/body/moves/CyclicMove.h"
 
namespace roly
{
// Class used to generate complex cyclic movements.
// These movements result from the combination of two simple linear movements (also cyclic).
// Each linear movement has its proper frequency, angle and amplitude.
// And they are both related by a phase difference.
class MoveFactory
{    
public:  
    //MoveFactory();
    //~MoveFactory();
    
    // compute the cyclic move that produces the specified arm figure
    static CyclicMove createMove(ArmFigure& oArmFigure);

private:
    // create linear movement
    static void createLineMove(ArmFigure& oArmFigure, CyclicMove& oCyclicMove); 
    // create circular movement
    static void createCircularMove(ArmFigure& oArmFigure, CyclicMove& oCyclicMove); 
    // create elliptic movement
    static void createEllipticMove(ArmFigure& oArmFigure, CyclicMove& oCyclicMove); 
    // create pajarita movement
    //void createPajaritaMove(ArmFigure& oArmFigure, CyclicMove& oCyclicMove); 
};
}
#endif
