#ifndef __ROLY_BODY_ARTISTIC_H
#define __ROLY_BODY_ARTISTIC_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/bodycore/ArtisticBus.h"
#include "roly/body/modules/BodyModule.h"
#include "amy/interface2/control/CyclerClient.h"
#include "tron/math/CyclicComponent.h"
#include "tron/util/ControlMagnitude.h"
#include "tron2/moves/CyclicMovement.h"
#include "tron2/moves/MoveFactory.h"
// language themes
#include "tron2/language/features/DirectionsTheme.h"
#include "tron2/language/features/LengthTheme.h"
#include "tron2/language/features/QuantityTheme.h"
#include "tron2/language/features/SizeTheme.h"
#include "tron2/language/features/SpeedTheme.h"
#include "tron2/language/objects/FiguresTheme.h"

namespace roly
{
// Module to perform complex cyclic movements with the arm. It controls the frontal cycler module of amy node.
// Messages:
// It sends 3 types of messages to the cycler: trigger, stop & update.
class Artistic : public BodyModule
{
public:
    // states of Artistic module
    enum eType
    {
         eSTATE_IDLE,           // waits for requests
         eSTATE_LAUNCH,      // launches cycler movement
         eSTATE_MOVE,      // waits for movement to finish (until halt request in continuous mode)
         eSTATE_UPDATE,      // updates cycler movement
         eSTATE_STOP           // stops cycler movement
    };

private:    
    static log4cxx::LoggerPtr logger;
    int id;                                // id of artistic module (defines the target cycler)
    // bus        
    ArtisticBus* pArtisticBus;  // bus connection for this module
    // logic
    int figure;             // requested movement figure 
    int change;           // requested movement change    
    int changedFeature;    // feature to which the requested change applies (speed, size, ...)
    bool bchangeAll;        // requested change applies to all features (speed, size, ...)
    int turn;               // requested movement turn
    bool bnewChange;      // flag indicating a movement change was requested (speed, size or length)
    bool bnewTurn;           // flag indicating a movement turn was requested (angle)  
    bool bcontinuous;       // continuous or simple mode
    amy::CyclerClient oArmCyclerClient;     // client for control of arm cycler section (main or secondary)
    tron::ControlMagnitude oFrequency;
    tron::ControlMagnitude oSize;
    tron::ControlMagnitude oAngle;
    tron::ControlMagnitude oRelFactor;
    tron2::MoveFactory oMoveFactory; // utility class for movements creation
    tron2::CyclicMovement oCyclicMovement;
    // language themes
    tron2::DirectionsTheme oDirectionsTheme; // directions
    tron2::LengthTheme oLengthTheme; // length
    tron2::QuantityTheme oQuantityTheme; // quantity
    tron2::SizeTheme oSizeTheme; // size
    tron2::SpeedTheme oSpeedTheme; // speed
    tron2::FiguresTheme oFiguresTheme; // figures 

public:
        Artistic();
        //~Artistic();
                               
        void setID(int value);
        int getID() {return id;};
private:       
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        // read bus data
        virtual void senseBus();
        // write info (control & sensory) to bus
        virtual void writeBus();
        // show module initialization in logs
        virtual void showInitialized();
        // shows the present state name
        void showState();
        
        // triggers a cyclic movement
        void triggerMove();
        // stops a cyclic movement
        void stopMove();
        // performs a requested movement change
        void performChange();
        // transmit components of cyclic movement        
        void transmitMovement();
        
        // checks if ordered movement is finished (just for simple mode)
        bool checkMovementFinished();

        // analyzes requested movement figure
        int analyseFigure(std::string word);        
        // analyzes requested movement change
        int analyseChange(std::string word);        
        // analyzes requested movement turn        
        int analyseTurn(std::string word);    
        
        // changes speed of present movement
        bool changeMovementSpeed(int code);
        // changes size of present movement
        bool changeMovementSize(int code);
        // changes angle of present movement
        bool changeMovementOrientation(int code);
        // changes relative factor of present movement
        bool changeMovementFactor(int code);
        // set all movement properties to normal values
        void setNormalMovement();
};
}
#endif
