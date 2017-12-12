#ifndef __ROLY_BODY_CYCLICMOVE_H
#define __ROLY_BODY_CYCLICMOVE_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
 
namespace roly
{
// Class used to represent a cyclic movement. 
// It may be simple: single component for linear moves.
// Or may be composed: two components for curved moves.
class CyclicMove
{
private:
    bool bsimple;   // flag indicating simple or composed movement
    // first component
    float freq1;   // movement frequency (Hz)
    float angle1;  // movement frontal angle (degrees)
    float amp1;   // movement amplitude (degress)
    // second component
    float freq2;   // movement frequency (Hz)
    float angle2;  // movement frontal angle (degrees)
    float amp2;   // movement amplitude (degress)
    // general
    float phase;   // phase difference between both cyclic components
    float elasticity;
    float changeUp;
    float changeDown;
    
public:  
    CyclicMove();
    //~CyclicMove();

    void setSimple() {bsimple = true;}
    void setComposed() {bsimple = false;}
    bool isSimple() {return bsimple;}
    
    // first component
    void setFreq1(float value) {freq1 = value;}
    void setAngle1(float value) {angle1 = value;}
    void setAmp1(float value) {amp1 = value;}
    float getFreq1() {return freq1;}; 
    float getAngle1() {return angle1;}; 
    float getAmp1() {return amp1;}; 
    // second component
    void setFreq2(float value) {freq2 = value;}
    void setAngle2(float value) {angle2 = value;}
    void setAmp2(float value) {amp2 = value;}
    float getFreq2() {return freq2;}; 
    float getAngle2() {return angle2;}; 
    float getAmp2() {return amp2;}; 
    // general
    void setPhase(float value) {phase = value;}
    float getPhase() {return phase;};
    
    void setElasticity(float value);
    
    // update movement making it wider/narrower
    void makeWider(bool bchange); 
    // update movement making it taller/shorter
    void makeTaller(bool bchange); 
    // update movement making it faster/slower
    void makeFaster(bool bchange); 
    // update movement changing its orientation the specified angle
    void makeTurn(float degrees); 
};
}
#endif
