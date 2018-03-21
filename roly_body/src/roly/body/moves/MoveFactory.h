#ifndef __ROLY_BODY_MOVEFACTORY_H
#define __ROLY_BODY_MOVEFACTORY_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "maty/moves/CyclicMove.h"
 
namespace roly
{
// Class used to generate complex cyclic movements.
// These movements result from the combination of simple cyclic movements (each with its own frequency, angle, amplitude and phase).
class MoveFactory
{  
public:
    enum eFigure
    {
        eFIGURE_UNDEFINED,
        eFIGURE_LINE,
        eFIGURE_CIRCLE,
        eFIGURE_ELLIPSE,
      //  eFIGURE_PAJARITA,                
        eFIGURE_DIM,                
    };

private: 
    std::vector<maty::CyclicMove> listCyclicComponents;  // cyclic components for requested movement
    
public:  
    MoveFactory();
    ~MoveFactory();

    maty::CyclicMove* getPrimaryCyclicComponent();
    maty::CyclicMove* getSecondaryCyclicComponent();
    
    void clear();
    // create linear movement
    void createLine(float amplitude, float angle, float freq); 
    // create circular movement
    void createCircle(float amplitude, int direction, float freq); 
    // create elliptic movement
    void createEllipse(float amplitude, float height, float angle, int direction, float freq); 
    
    void updateFreq(float freq);
    void updateAmplitude(float amplitude);
    void updateAngle(float angle);
    //void updateRelFactor(float factor);   // TO DO ... (only valid for ellipse)

private:
};
}
#endif
