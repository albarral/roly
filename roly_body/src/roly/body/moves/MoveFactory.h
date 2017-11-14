#ifndef __ROLY_BODY_MOVEFACTORY_H
#define __ROLY_BODY_MOVEFACTORY_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/body/moves/CyclicMove.h"
 
namespace roly
{
// Class used to generate complex cyclic movements.
// These movements result from the combination of two simple linear movements (also cyclic).
// Each linear movement has its proper frequency, angle and amplitude.
// And they are both related by a phase difference.
// Initially, default values are assigned to the components, but can be modified later.
class MoveFactory
{
public:
    enum eMoves
    {
        eMOV_LINE,
        eMOV_CIRCLE,
        eMOV_ELLIPSE,
      //  eMOV_PAJARITA,                
        eMOV_UNDEFINED                
    };
private:
    // default values
    float defFreq;     // frequency of the movement
    float defAngle;    // orientation angle (degrees)
    float defAmp;    // movement amplitude (degrees)
    
public:  
    MoveFactory();
    //~MoveFactory();

    // parameters
    void setDefFrequency(float value)  {defFreq = value;}    
    void setDefAngle(float value)  {defAngle = value;}    
    void setDefAmplitude(float value)  {defAmp = value;}    
    
    // compute the specified cyclic movement (one of eMoves)
    CyclicMove computeMove(int type);

private:
    // create linear movement
    void createMoveLine(CyclicMove& oCyclicMove); 
    // create circular movement
    void createMoveCircle(CyclicMove& oCyclicMove); 
    // create elliptic movement
    void createMoveEllipse(CyclicMove& oCyclicMove); 
    // create pajarita movement
    //void createMovePajarita(CyclicMove& oCyclicMove); 
};
}
#endif
