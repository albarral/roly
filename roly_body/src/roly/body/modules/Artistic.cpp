/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/body/modules/Artistic.h"
#include "roly/bodycore/ArtisticConfig.h"
#include "tron/math/CyclicComponent.h"
#include "tron2/moves/CyclicMovement.h"
#include "tron2/language/objects/FiguresTheme.h"

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
    // set default move factory values
    ArtisticConfig oArtisticConfig;
    oMoveFactory.setFreq(oArtisticConfig.getFreq());
    oMoveFactory.setSize(oArtisticConfig.getSize());
    oMoveFactory.setAngle(oArtisticConfig.getAngle());
    oMoveFactory.setRelativeFactor(oArtisticConfig.getRelativeFactor());
    oMoveFactory.setRelativeFreq(oArtisticConfig.getRelativeFreq());
    oMoveFactory.setRotation(oArtisticConfig.getRotation());
    
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

    if (getStable() == 0)
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
        if (value >= 0)
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
            oMoveFactory.setFreq(value);
            bmoveChanged = true;
            if (oMoveFactory.getCyclicMovement() != 0)
                oMoveFactory.getCyclicMovement()->updateFreq(value);
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
            oMoveFactory.setSize(value);
            bmoveChanged = true;
            if (oMoveFactory.getCyclicMovement() != 0)
                oMoveFactory.getCyclicMovement()->updateAmplitude(value);
        }
        else
            LOG4CXX_WARN(logger, modName << " invalid size requested " + std::to_string(value));                     
    }

    // check orientation requests
    if (pBodyBus->getCO_ARTISTIC_ORIENTATION().checkRequested())
    {  
        value = pBodyBus->getCO_ARTISTIC_ORIENTATION().getValue();
        // all orientations are valid
        oMoveFactory.setAngle(value);
        bmoveChanged = true;
        if (oMoveFactory.getCyclicMovement() != 0)
            oMoveFactory.getCyclicMovement()->updateAngle(value);
    }

    // check relative factor requests
    if (pBodyBus->getCO_ARTISTIC_RELFACTOR().checkRequested())
    {  
        float value = pBodyBus->getCO_ARTISTIC_RELFACTOR().getValue();
        if (value > 0.0)
        {
            oMoveFactory.setRelativeFactor(value);
            bmoveChanged = true;
            if (oMoveFactory.getCyclicMovement() != 0)
                oMoveFactory.getCyclicMovement()->updateRelFactor(value); 
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
    // get movement code for requested figure
    int movement = translateFigure2Movement(figure); 
    
    // generate cyclic movement 
    if (!oMoveFactory.generateMovement(movement))
        return;    
    
    tron2::CyclicMovement* pCyclicMovement = oMoveFactory.getCyclicMovement();
    // first cycler 
    tron::CyclicComponent& oCyclicComponent1 = pCyclicMovement->getPrimaryComponent();
    oArmClient.setFrontCyclerAmp1(oCyclicComponent1.getAmp());
    oArmClient.setFrontCyclerAngle1(oCyclicComponent1.getAngle());
    oArmClient.setFrontCyclerFreq1(oCyclicComponent1.getFreq());
    oArmClient.setFrontCyclerPhase1(oCyclicComponent1.getPhase());
    
    // second cycler
    if (pCyclicMovement->isDual())
    {
        tron::CyclicComponent& oCyclicComponent2 = pCyclicMovement->getSecondaryComponent();
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
    tron2::CyclicMovement* pCyclicMovement = oMoveFactory.getCyclicMovement();

    if (pCyclicMovement == 0)
        return;
    
    // first cycler 
    tron::CyclicComponent& oCyclicComponent1 = pCyclicMovement->getPrimaryComponent();
    oArmClient.setFrontCyclerAmp1(oCyclicComponent1.getAmp());
    oArmClient.setFrontCyclerAngle1(oCyclicComponent1.getAngle());
    oArmClient.setFrontCyclerFreq1(oCyclicComponent1.getFreq());
    oArmClient.setFrontCyclerPhase1(oCyclicComponent1.getPhase());
    
    // second cycler
    if (pCyclicMovement->isDual())
    {
        tron::CyclicComponent& oCyclicComponent2 = pCyclicMovement->getSecondaryComponent();
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

// convert a generic figure code (from tron2 language) to a corresponding movement code (from tron2 moves)
int Artistic::translateFigure2Movement(int value)
{
    int movement = -1;
    switch (value)
    {
        case tron2::FiguresTheme::eFIGURE_CIRCLE:                 
            movement = tron2::MoveFactory::eMOVEMENT_CIRCLE;
            break;
        case tron2::FiguresTheme::eFIGURE_ELLIPSE:                       
            movement = tron2::MoveFactory::eMOVEMENT_ELLIPSE;
            break;
        case tron2::FiguresTheme::eFIGURE_SQUARE:                       
            movement = tron2::MoveFactory::eMOVEMENT_SQUARE;
            break;
        case tron2::FiguresTheme::eFIGURE_RECTANGLE:                    
            movement = tron2::MoveFactory::eMOVEMENT_RECTANGLE;
            break;
        case tron2::FiguresTheme::eFIGURE_TRIANGLE:                    
            movement = tron2::MoveFactory::eMOVEMENT_TRIANGLE;
            break;
        case tron2::FiguresTheme::eFIGURE_LINE:                    
            movement = tron2::MoveFactory::eMOVEMENT_LINE;
            break;
        case tron2::FiguresTheme::eFIGURE_WAVE:
            movement = tron2::MoveFactory::eMOVEMENT_WAVE;
            break;
    }
    return movement;
}

void Artistic::writeBus()
{
    // nothing to do here    
    // control already done by triggerMove, stopMove & updateMove methods
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