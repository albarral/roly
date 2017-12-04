#ifndef __ROLY_BODY_ARMFIGURE_H
#define __ROLY_BODY_ARMFIGURE_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
 
namespace roly
{
// Class used to represent an arm figure: a cyclic arm movement of given type, size and speed.
class ArmFigure
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
    int figure;       // figure id (eFigure)
    float freq;         // frequency of cyclic movement
    float size;         // size of cyclic movement (degrees/s)
    float relFactor;   // relative xy factor of cyclic movement
    float orientation;    // orientation of cyclic movement (degrees)
    
public:  
    ArmFigure();
    //~ArmFigure();

    int getFigure() {return figure;}
    float getFreq() {return freq;}; 
    float getSize() {return size;}; 
    float getRelativeFactor() {return relFactor;}; 
    float getOrientation() {return orientation;};
    
    void setFigure(int figure) {this->figure = figure;};
    void setFreq(float freq) {this->freq = freq;};
    void setSize(float size) {this->size = size;};
    void setRelativeFactor(float relFactor) {this->relFactor = relFactor;};
    void setOrientation(float orientation) {this->orientation = orientation;};
    
};
}
#endif
