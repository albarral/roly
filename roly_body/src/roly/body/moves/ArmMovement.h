#ifndef __ROLY_BODY_ARMMOVEMENT_H
#define __ROLY_BODY_ARMMOVEMENT_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
 
namespace roly
{
// Class used to represent an arm movement.
// It can be of two types: posture or real move.
// - posture: defines a target arm 3D position    
// - move: defines a target arm 3D speed 
class ArmMovement
{
public:
    // movement types
    enum eType
    {
         eTYPE_POSTURE,           
         eTYPE_MOVE
    };
    
private:
    int type;       // movement type (eType)
    float pan;   // posture: arm pan position (degrees), move: arm pan speed (degrees/s)
    float tilt;  // posture: arm tilt position (degrees), move: arm tilt speed (degrees/s)
    float radius;   // posture: arm radial position (cm), move: arm radial speed (cm/s)
    int millis;        // duration of the movement (millis): time to hold the posture, or time to keep the move
    
public:  
    ArmMovement();
    //~ArmMovement();

    int getType() {return type;}
    
    void setPosture(float pan, float tilt, float rad, int time);
    void setMove(float vpan, float vtilt, float vrad, int time);
    
    float getPan() {return pan;}; 
    float getTilt() {return tilt;}; 
    float getRadius() {return radius;}; 
    int getTimeMillis() {return millis;};
};
}
#endif
