#ifndef __BODY_CORE_ARTISTICCONFIG_H
#define __BODY_CORE_ARTISTICCONFIG_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace roly
{
class ArtisticConfig 
{
private:                
    float freq;         // frequency of cyclic movements
    float size;         // size of cyclic movement (degrees)
    float angle;    // orientation of cyclic movement (degrees)
    float relFactor;   // relative xy factor of cyclic movement
    float relFreq;   // relative frequency of wave movements
    bool brotation;     // rotation sign of circular movements (positive is anticlockwise)
            
    public:
        ArtisticConfig();
        //~ArtisticConfig();

    void setFreq(float value) {freq = value;}
    void setSize(float value) {size = value;}
    void setAngle(float value) {angle = value;}
    void setRelativeFactor(float value) {relFactor = value;}
    void setRelativeFreq(float value) {relFreq = value;}
    void setRotation(bool value) {brotation = value;};
    float getFreq() {return freq;}; 
    float getSize() {return size;}; 
    float getAngle() {return angle;}; 
    float getRelativeFactor() {return relFactor;};
    float getRelativeFreq() {return relFreq;};
    float getRotation() {return brotation;};
};

}

#endif
