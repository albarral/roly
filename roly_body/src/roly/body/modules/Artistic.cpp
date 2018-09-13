/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/body/modules/Artistic.h"
#include "roly/bodycore/config/ArtisticConfig.h"
#include "roly/bodycore/config/BodyConfig.h"
#include "tron2/moves/CyclicMovement.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr Artistic::logger(Logger::getLogger("roly.body"));

Artistic::Artistic()
{
    modName = "Artistic";
    id = -1;
    pArtisticBus = 0;
}

//Artistic::~Artistic()
//{
//}

void Artistic::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}

void Artistic::setID(int value)
{
    if (value == BodyConfig::ARTISTIC1 || value == BodyConfig::ARTISTIC2)
    {
        id = value;
        modName += std::to_string(id);
    }
}

void Artistic::first()
{
    // connect module to proper bus
    if (id == BodyConfig::ARTISTIC1)
    {
        pArtisticBus = &(pBodyBus->getArtisticBus1());
        oArmCyclerClient.tune2Cycler(1);
    }
    else if (id == BodyConfig::ARTISTIC2)
    {
        pArtisticBus = &(pBodyBus->getArtisticBus2());
        oArmCyclerClient.tune2Cycler(2);
    }
    else
    {
        LOG4CXX_WARN(logger, modName << " couldn't connect to proper bus. Ending module!");
        tron::Module3::off();
        return;
    }
    
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
    binhibited = pArtisticBus->getCO_INHIBIT_ARTISTIC().isRequested();

    // check figure requests
    if (pArtisticBus->getCO_ARTISTIC_FIGURE().checkRequested())
    {
        figure = pArtisticBus->getCO_ARTISTIC_FIGURE().getValue();
        if (!figure.empty())
            bnewMove = true;
        else
            LOG4CXX_WARN(logger, modName << " no figure requested");                     
    }
        
    // check freq requests
    if (pArtisticBus->getCO_ARTISTIC_FREQ().checkRequested())
    {  
        value = pArtisticBus->getCO_ARTISTIC_FREQ().getValue();
        if (value > 0)
        {
            bmoveChanged = true;
            oMoveFactory.setFreq(value);
            if (!figure.empty())
                oCyclicMovement.updateFreq(value);
        }
        else
            LOG4CXX_WARN(logger, modName << " invalid freq requested " + std::to_string(value));                     
    }

    // check size requests
    if (pArtisticBus->getCO_ARTISTIC_SIZE().checkRequested())
    {  
        value = pArtisticBus->getCO_ARTISTIC_SIZE().getValue();
        if (value > 0)
        {
            bmoveChanged = true;
            oMoveFactory.setSize(value);
            if (!figure.empty())
                oCyclicMovement.updateAmplitude(value);
        }
        else
            LOG4CXX_WARN(logger, modName << " invalid size requested " + std::to_string(value));                     
    }

    // check orientation requests
    if (pArtisticBus->getCO_ARTISTIC_ORIENTATION().checkRequested())
    {  
        value = pArtisticBus->getCO_ARTISTIC_ORIENTATION().getValue();
        // all orientations are valid
        bmoveChanged = true;
        oMoveFactory.setAngle(value);
        if (!figure.empty())
            oCyclicMovement.updateAngle(value);
    }

    // check relative factor requests
    if (pArtisticBus->getCO_ARTISTIC_RELFACTOR().checkRequested())
    {  
        float value = pArtisticBus->getCO_ARTISTIC_RELFACTOR().getValue();
        if (value > 0.0)
        {
            bmoveChanged = true;
            oMoveFactory.setRelativeFactor(value);
            if (!figure.empty())
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
    if (pArtisticBus->getCO_ARTISTIC_HALT().checkRequested())
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
        
    // set cycler main component
    updateCyclerComponent(true, oCyclicMovement.getPrimaryComponent());        
    // if dual, set cycler secondary component
    if (oCyclicMovement.isDual())
        updateCyclerComponent(false, oCyclicMovement.getSecondaryComponent());
    // otherwise clear the secondary component
    else
        stopCyclerComponent(false);
    
    // start movement
    oArmCyclerClient.run(true);
}

void Artistic::updateMove()
{        
    // set cycler 1 main component
    updateCyclerComponent(true, oCyclicMovement.getPrimaryComponent());        
    // if dual, set cycler 1 secondary component
    if (oCyclicMovement.isDual())
        updateCyclerComponent(false, oCyclicMovement.getSecondaryComponent());
}

void Artistic::stopMove()
{    
    // stop movement
    oArmCyclerClient.run(false);
}

void Artistic::updateCyclerComponent(bool bmain, tron::CyclicComponent& oCyclicComponent)
{        
    // cycler main component
    if (bmain)
    {
        oArmCyclerClient.setMainAmplitude(oCyclicComponent.getAmp());
        oArmCyclerClient.setMainAngle(oCyclicComponent.getAngle());
        oArmCyclerClient.setMainFreq(oCyclicComponent.getFreq());
        oArmCyclerClient.setMainPhase(oCyclicComponent.getPhase());            
    }
    // cycler secondary component
    else
    {
        oArmCyclerClient.setSecondaryAmplitude(oCyclicComponent.getAmp());
        oArmCyclerClient.setSecondaryAngle(oCyclicComponent.getAngle());
        oArmCyclerClient.setSecondaryFreq(oCyclicComponent.getFreq());
        oArmCyclerClient.setSecondaryPhase(oCyclicComponent.getPhase());            
    }
}

void Artistic::stopCyclerComponent(bool bmain)
{        
    // cycler main component
    if (bmain)
    {
        oArmCyclerClient.setMainAmplitude(0.0);
        oArmCyclerClient.setMainFreq(0.0);
    }
    // cycler secondary component
    else
    {
        oArmCyclerClient.setSecondaryAmplitude(0.0);
        oArmCyclerClient.setSecondaryFreq(0.0);
    }
}

// convert a generic figure code (from tron2 language) to a corresponding movement code (from tron2 moves)
int Artistic::translateFigure2Movement(std::string figure)
{    
    int movement = -1;
    
    int figureCode;
    // get the code for that figure name
    if (oFiguresTheme.getCode4Name(figure, figureCode))
    {
        // if known translate to movement factory
        switch (figureCode) 
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
            default:
                LOG4CXX_WARN(logger, modName << " figure not available in movements factory: " << figure);                     
        }
    }
    else                  
        LOG4CXX_WARN(logger, modName << " figure unknown: " << figure);                     
    
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