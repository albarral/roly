/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/body/modules/Artistic.h"
#include "maty/moves/CyclicMove.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr Artistic::logger(Logger::getLogger("roly.body"));

Artistic::Artistic()
{
    modName = "Artistic";
}

//Artistic::~Artistic()
//{
//}

void Artistic::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}


void Artistic::first()
{
    // set default figure values
    freq = 0.5;
    size = 40.0;
    relFactor = 0.5;
    orientation = 0.0;
    
    // start at WAIT
    setState(eSTATE_IDLE);
    
    log4cxx::NDC::push(modName);   	
}
                    
// performs a cyclic wave movement of the elbow
void Artistic::loop()
{
    senseBus();
    
    // skip if module is inhibited
    if (binhibited)            
        return;

    if (isStateChanged())
        showState();

    switch (getState())
    {
        case eSTATE_IDLE:
            // nothing done
            break;

        case eSTATE_LAUNCH:
            // triggers the cyclic movement            
            triggerMove();
            // -> WAIT
            setState(eSTATE_WAIT);
            break;

        case eSTATE_WAIT:
            // if simple mode
            if (!bcontinuous)
            {
                // when movement finished -> STOP
                if (checkMovementFinished())
                    setState(eSTATE_STOP);
            }
            break;

        case eSTATE_UPDATE:
            // updates the cyclic movement            
            updateMove();
            // -> WAIT
            setState(eSTATE_WAIT);
            break;                        

        case eSTATE_STOP:
            // stops the cyclic movement            
            stopMove();
            // -> IDLE
            setState(eSTATE_IDLE);
            break;
    }   // end switch        
    
    //writeBus();
}

void Artistic::senseBus()
{
    // TO DO ... get from BUS
    bcontinuous = true;
    // control flags
    bool bnewMove = false;
    bool bmoveChanged = false;
    float value;
        
     // check inhibition
    binhibited = pBodyBus->getCO_INHIBIT_ARTISTIC().isRequested();

    // check figure requests
    if (pBodyBus->getCO_ARTISTIC_FIGURE().checkRequested())
    {
        value = pBodyBus->getCO_ARTISTIC_FIGURE().getValue();
        if (value > MoveFactory::eFIGURE_UNDEFINED && value < MoveFactory::eFIGURE_DIM)
        {
            figure = value;
            bnewMove = true;
        }
        else
            LOG4CXX_WARN(logger, modName << " invalid figure requested " + std::to_string(value));                     
    }
        
    // check freq requests
    if (pBodyBus->getCO_ARTISTIC_FREQ().checkRequested())
    {  
        value = pBodyBus->getCO_ARTISTIC_FREQ().getValue();
        if (value > 0)
        {
            freq = value;
            bmoveChanged = true;
            oMoveFactory.updateFreq(freq);
        }
        else
            LOG4CXX_WARN(logger, modName << " invalid freq requested " + std::to_string(value));                     
    }

    // check size requests
    if (pBodyBus->getCO_ARTISTIC_SIZE().checkRequested())
    {  
        value = pBodyBus->getCO_ARTISTIC_SIZE().getValue();
        if (value > 0)
        {
            size = value;
            bmoveChanged = true;
            oMoveFactory.updateAmplitude(size);
        }
        else
            LOG4CXX_WARN(logger, modName << " invalid size requested " + std::to_string(value));                     
    }

    // check orientation requests
    if (pBodyBus->getCO_ARTISTIC_ORIENTATION().checkRequested())
    {  
        orientation = pBodyBus->getCO_ARTISTIC_ORIENTATION().getValue();
        // all orientations are valid
        bmoveChanged = true;
        oMoveFactory.updateAngle(orientation);
    }

    // check relative factor requests
    if (pBodyBus->getCO_ARTISTIC_RELFACTOR().checkRequested())
    {  
        float value = pBodyBus->getCO_ARTISTIC_RELFACTOR().getValue();
        if (value > 0.0)
        {
            relFactor = value;
            bmoveChanged = true;
            //oMoveFactory.updateRelFactor(relFactor);  // TO DO ...
        }
        else
            LOG4CXX_WARN(logger, modName << " invalid relative factor requested " + std::to_string(value));                     
    }

    // if new figure requested -> LAUNCH movement
    if (bnewMove)
        setState(eSTATE_LAUNCH);                                       
    // otherwise if movement change requested -> UPDATE movement
    else if (bmoveChanged)
        setState(eSTATE_UPDATE);                                       
    
    // anyway, if halt requested -> STOP
    if (pBodyBus->getCO_ARTISTIC_HALT().checkRequested())
    {
        setState(eSTATE_STOP);
    }
}



bool Artistic::checkMovementFinished()
{
    // TO DO ...
    return false;    
}

void Artistic::triggerMove()
{    
    // get cyclic movement for requested figure
    generateMovement();
    
    maty::CyclicMove* pCyclicMove1 = oMoveFactory.getPrimaryCyclicComponent();
    maty::CyclicMove* pCyclicMove2 = oMoveFactory.getSecondaryCyclicComponent();
    
    // first cycler 
    if (pCyclicMove1 != 0)
    {
        oArmClient.setFrontCyclerAmp1(pCyclicMove1->getAmp());
        oArmClient.setFrontCyclerAngle1(pCyclicMove1->getAngle());
        oArmClient.setFrontCyclerFreq1(pCyclicMove1->getFreq());
        oArmClient.setFrontCyclerPhase1(pCyclicMove1->getPhase());
    }
    
    // second cycler
    if (pCyclicMove2 != 0)
    {
        oArmClient.setFrontCyclerAmp2(pCyclicMove2->getAmp());
        oArmClient.setFrontCyclerAngle2(pCyclicMove2->getAngle());
        oArmClient.setFrontCyclerFreq2(pCyclicMove2->getFreq());
        oArmClient.setFrontCyclerPhase2(pCyclicMove2->getPhase());
    }
    
    // start movement
    oArmClient.setFrontCyclerAction(1);
}

void Artistic::updateMove()
{        
    maty::CyclicMove* pCyclicMove1 = oMoveFactory.getPrimaryCyclicComponent();
    maty::CyclicMove* pCyclicMove2 = oMoveFactory.getSecondaryCyclicComponent();
    
    // first cycler 
    if (pCyclicMove1 != 0)
    {
        oArmClient.setFrontCyclerAmp1(pCyclicMove1->getAmp());
        oArmClient.setFrontCyclerAngle1(pCyclicMove1->getAngle());
        oArmClient.setFrontCyclerFreq1(pCyclicMove1->getFreq());
        oArmClient.setFrontCyclerPhase1(pCyclicMove1->getPhase());
    }
    
    // second cycler
    if (pCyclicMove2 != 0)
    {
        oArmClient.setFrontCyclerAmp2(pCyclicMove2->getAmp());
        oArmClient.setFrontCyclerAngle2(pCyclicMove2->getAngle());
        oArmClient.setFrontCyclerFreq2(pCyclicMove2->getFreq());
        oArmClient.setFrontCyclerPhase2(pCyclicMove2->getPhase());
    }
}

void Artistic::stopMove()
{    
    // stop movement
    oArmClient.setFrontCyclerAction(0);
}

void Artistic::writeBus()
{
    // nothing to do here    
    // control already done by triggerMove, stopMove & updateMove methods
}

void Artistic::generateMovement()
{
    int direction = 0;  // TO SPECIFY (n, s, e, w, ne, nw, se, sw)

    switch (figure)
    {
        case MoveFactory::eFIGURE_LINE:
            oMoveFactory.createLine(size, orientation, freq);
            break;            
        case MoveFactory::eFIGURE_CIRCLE:
            oMoveFactory.createCircle(size, direction, freq);
            break;
        case MoveFactory::eFIGURE_ELLIPSE:
            oMoveFactory.createEllipse(size, size*relFactor, orientation, direction, freq);
            break;            
        default: 
            oMoveFactory.clear();
            break;
    }    
}

void Artistic::showState()
{
    switch (getState())
    {
        case eSTATE_IDLE:
            LOG4CXX_INFO(logger, ">> idle");
            break;
        case eSTATE_LAUNCH:
            LOG4CXX_INFO(logger, ">> launch");
            break;
        case eSTATE_WAIT:
            LOG4CXX_INFO(logger, ">> wait");
            break;
        case eSTATE_UPDATE:
            LOG4CXX_INFO(logger, ">> update");
            break;                        
        case eSTATE_STOP:
            LOG4CXX_INFO(logger, ">> stop");
            break;
    }   // end switch    
}

}