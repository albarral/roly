/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/body/modules/Artistic.h"
#include "maty/moves/CyclicComponent.h"

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
            oCircularMovement.updateFreq(freq);
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
            oCircularMovement.updateAmplitude(size);
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
        oCircularMovement.updateAngle(orientation);
    }

    // check relative factor requests
    if (pBodyBus->getCO_ARTISTIC_RELFACTOR().checkRequested())
    {  
        float value = pBodyBus->getCO_ARTISTIC_RELFACTOR().getValue();
        if (value > 0.0)
        {
            relFactor = value;
            bmoveChanged = true;
            oCircularMovement.updateRelFactor(relFactor); 
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
    if (!generateMovement())
        return;    
    
    // first cycler 
    maty::CyclicComponent& oCyclicComponent1 = oCircularMovement.getPrimaryComponent();
    oArmClient.setFrontCyclerAmp1(oCyclicComponent1.getAmp());
    oArmClient.setFrontCyclerAngle1(oCyclicComponent1.getAngle());
    oArmClient.setFrontCyclerFreq1(oCyclicComponent1.getFreq());
    oArmClient.setFrontCyclerPhase1(oCyclicComponent1.getPhase());
    
    // second cycler
    if (oCircularMovement.isDual())
    {
        maty::CyclicComponent& oCyclicComponent2 = oCircularMovement.getSecondaryComponent();
        oArmClient.setFrontCyclerAmp2(oCyclicComponent2.getAmp());
        oArmClient.setFrontCyclerAngle2(oCyclicComponent2.getAngle());
        oArmClient.setFrontCyclerFreq2(oCyclicComponent2.getFreq());
        oArmClient.setFrontCyclerPhase2(oCyclicComponent2.getPhase());
    }
    else
    {
        oArmClient.setFrontCyclerFreq2(0.0);
        oArmClient.setFrontCyclerAmp2(0.0);        
    }
    
    // start movement
    oArmClient.setFrontCyclerAction(1);
}

void Artistic::updateMove()
{        
    // first cycler 
    maty::CyclicComponent& oCyclicComponent1 = oCircularMovement.getPrimaryComponent();
    oArmClient.setFrontCyclerAmp1(oCyclicComponent1.getAmp());
    oArmClient.setFrontCyclerAngle1(oCyclicComponent1.getAngle());
    oArmClient.setFrontCyclerFreq1(oCyclicComponent1.getFreq());
    oArmClient.setFrontCyclerPhase1(oCyclicComponent1.getPhase());
    
    // second cycler
    if (oCircularMovement.isDual())
    {
        maty::CyclicComponent& oCyclicComponent2 = oCircularMovement.getSecondaryComponent();
        oArmClient.setFrontCyclerAmp2(oCyclicComponent2.getAmp());
        oArmClient.setFrontCyclerAngle2(oCyclicComponent2.getAngle());
        oArmClient.setFrontCyclerFreq2(oCyclicComponent2.getFreq());
        oArmClient.setFrontCyclerPhase2(oCyclicComponent2.getPhase());
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

bool Artistic::generateMovement()
{
    bool bok = true;
    switch (figure)
    {
//        case MoveFactory::eFIGURE_LINE:
//            oMoveFactory.createLine(size, orientation, freq);
//            break;            
        case MoveFactory::eFIGURE_CIRCLE:
            oCircularMovement.createCircle(freq, size, orientation, true);
            break;
        case MoveFactory::eFIGURE_ELLIPSE:
            oCircularMovement.createEllipse(freq, size, relFactor, orientation, true);
            break;            
        default: 
            bok = false;
            break;
    }
    return bok;
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