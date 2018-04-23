/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/body/modules/Artistic.h"
#include "roly/bodycore/ArtisticConfig.h"
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
    figure = -1;
    
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
            bnewMove = true;
            figure = value;
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
            bmoveChanged = true;
            oMoveFactory.setFreq(value);
            if (figure != -1)
                oCyclicMovement.updateFreq(value);
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
            bmoveChanged = true;
            oMoveFactory.setSize(value);
            if (figure != -1)
                oCyclicMovement.updateAmplitude(value);
        }
        else
            LOG4CXX_WARN(logger, modName << " invalid size requested " + std::to_string(value));                     
    }

    // check orientation requests
    if (pBodyBus->getCO_ARTISTIC_ORIENTATION().checkRequested())
    {  
        value = pBodyBus->getCO_ARTISTIC_ORIENTATION().getValue();
        // all orientations are valid
        bmoveChanged = true;
        oMoveFactory.setAngle(value);
        if (figure != -1)
            oCyclicMovement.updateAngle(value);
    }

    // check relative factor requests
    if (pBodyBus->getCO_ARTISTIC_RELFACTOR().checkRequested())
    {  
        float value = pBodyBus->getCO_ARTISTIC_RELFACTOR().getValue();
        if (value > 0.0)
        {
            bmoveChanged = true;
            oMoveFactory.setRelativeFactor(value);
            if (figure != -1)
                oCyclicMovement.updateRelFactor(value); 
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
    if (!oMoveFactory.generateMovement(oCyclicMovement, movement))
        return;    
        
    // set cycler 1 main component
    updateCyclerComponent(1, true, oCyclicMovement.getPrimaryComponent());        
    // if dual, set cycler 1 secondary component
    if (oCyclicMovement.isDual())
        updateCyclerComponent(1, false, oCyclicMovement.getSecondaryComponent());
    // otherwise clear it (the secondary component)
    else
        stopCyclerComponent(1, false);
    
    // start movement
    oArmClient.setCycler1Action(1);
}

void Artistic::updateMove()
{        
    // set cycler 1 main component
    updateCyclerComponent(1, true, oCyclicMovement.getPrimaryComponent());        
    // if dual, set cycler 1 secondary component
    if (oCyclicMovement.isDual())
        updateCyclerComponent(1, false, oCyclicMovement.getSecondaryComponent());
}

void Artistic::stopMove()
{    
    // stop movement
    oArmClient.setCycler1Action(0);
}

void Artistic::updateCyclerComponent(int cycler, bool bmain, tron::CyclicComponent& oCyclicComponent)
{        
    if (cycler == 1)
    {
        // cycler 1 main component
        if (bmain)
        {
            oArmClient.setCycler1MainAmp(oCyclicComponent.getAmp());
            oArmClient.setCycler1MainAngle(oCyclicComponent.getAngle());
            oArmClient.setCycler1MainFreq(oCyclicComponent.getFreq());
            oArmClient.setCycler1MainPhase(oCyclicComponent.getPhase());            
        }
        // cycler 1 secondary component
        else
        {
            oArmClient.setCycler1SecAmp(oCyclicComponent.getAmp());
            oArmClient.setCycler1SecAngle(oCyclicComponent.getAngle());
            oArmClient.setCycler1SecFreq(oCyclicComponent.getFreq());
            oArmClient.setCycler1SecPhase(oCyclicComponent.getPhase());            
        }
    }
    else if (cycler == 2)
    {
        // cycler 2 main component
        if (bmain)
        {
            oArmClient.setCycler2MainAmp(oCyclicComponent.getAmp());
            oArmClient.setCycler2MainAngle(oCyclicComponent.getAngle());
            oArmClient.setCycler2MainFreq(oCyclicComponent.getFreq());
            oArmClient.setCycler2MainPhase(oCyclicComponent.getPhase());            
        }
        // cycler 2 secondary component
        else
        {
            oArmClient.setCycler2SecAmp(oCyclicComponent.getAmp());
            oArmClient.setCycler2SecAngle(oCyclicComponent.getAngle());
            oArmClient.setCycler2SecFreq(oCyclicComponent.getFreq());
            oArmClient.setCycler2SecPhase(oCyclicComponent.getPhase());            
        }
    }
}

void Artistic::stopCyclerComponent(int cycler, bool bmain)
{        
    if (cycler == 1)
    {
        // cycler 1 main component
        if (bmain)
        {
            oArmClient.setCycler1MainAmp(0.0);
            oArmClient.setCycler1MainFreq(0.0);
        }
        // cycler 1 secondary component
        else
        {
            oArmClient.setCycler1SecAmp(0.0);
            oArmClient.setCycler1SecFreq(0.0);
        }
    }
    else if (cycler == 2)
    {
        // cycler 2 main component
        if (bmain)
        {
            oArmClient.setCycler2MainAmp(0.0);
            oArmClient.setCycler2MainFreq(0.0);
        }
        // cycler 2 secondary component
        else
        {
            oArmClient.setCycler2SecAmp(0.0);
            oArmClient.setCycler2SecFreq(0.0);
        }
    }
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