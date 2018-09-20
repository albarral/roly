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
    log4cxx::NDC::push(modName);   	

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
        LOG4CXX_WARN(logger, "Couldn't connect to proper bus. Ending module!");
        tron::Module3::off();
        return;
    }
    
    // set default move factory values
    figure = -1;
    oFrequency.setValues(0.1, 0.5, 2.0);
    oFrequency.setChanges(0.1, 1.5);
    oSize.setValues(10, 30, 90);
    oSize.setChanges(5, 1.5);
    oRelFactor.setValues(0.1, 0.5, 2.0);
    oRelFactor.setChanges(0.1, 1.5);
    oAngle.setValues(-45, 0, 45);
    oAngle.setChanges(5, 1.5);
    
    ArtisticConfig oArtisticConfig;
//    oMoveFactory.setFreq(oArtisticConfig.getFreq());
//    oMoveFactory.setSize(oArtisticConfig.getSize());
//    oMoveFactory.setAngle(oArtisticConfig.getAngle());    
//    oMoveFactory.setRelativeFactor(oArtisticConfig.getRelativeFactor());
    oMoveFactory.setRelativeFreq(oArtisticConfig.getRelativeFreq());
    oMoveFactory.setRotation(oArtisticConfig.getRotation());
    
    // start at WAIT
    setState(eSTATE_IDLE);    
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
            // update the cyclic movement            
            performChange();
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
        
     // check inhibition
    binhibited = pArtisticBus->getCO_INHIBIT_ARTISTIC().isRequested();

    // check figure requests
    if (pArtisticBus->getCO_ARTISTIC_FIGURE().checkRequested())
    {
        figure = pArtisticBus->getCO_ARTISTIC_FIGURE().getValue();
        if (!figure.empty())
        {
            bfigureRequested = true;
            LOG4CXX_INFO(logger, "< figure: " + figure);                     
        }
        else
        {
            bfigureRequested = false;
            LOG4CXX_WARN(logger, "< empty figure requested. Ignored!");                     
        }
    }
    else if (bfigureRequested)
        bfigureRequested = false;
        
    // check change requests
    if (pArtisticBus->getCO_ARTISTIC_SET().checkRequested())
    {  
        change = pArtisticBus->getCO_ARTISTIC_SET().getValue();
        if (!change.empty())
        {
            bchangeRequested = true;
            LOG4CXX_INFO(logger, "< change: " + change);                     
        }
        else
        {
            bchangeRequested = false;
            LOG4CXX_WARN(logger, "< empty change requested. Ignored!");                     
        }
    }
    else if (bchangeRequested)
        bchangeRequested = false;

    // check turn requests
    if (pArtisticBus->getCO_ARTISTIC_TURN().checkRequested())
    {  
        turn = pArtisticBus->getCO_ARTISTIC_TURN().getValue();
        if (!turn.empty())
        {
            bturnRequested = true;
            LOG4CXX_INFO(logger, "< turn: " + turn);                     
        }
        else
        {
            bturnRequested = false;
            LOG4CXX_WARN(logger, "< empty turn requested. Ignored!");                     
        }
    }
    else if (bturnRequested)
        bturnRequested = false;


    // if new figure requested -> LAUNCH
    if (bfigureRequested)
        setState(eSTATE_LAUNCH);                                       
    // otherwise if movement change requested -> UPDATE
    else if (bchangeRequested || bturnRequested)
        setState(eSTATE_UPDATE);                                       
    
    // anyway, if halt requested -> STOP
    if (pArtisticBus->getCO_ARTISTIC_HALT().checkRequested())
        setState(eSTATE_STOP);
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
    
    // skip if figure unknown
    if (movement == -1)
        return;

    oMoveFactory.setFreq(oFrequency.getValue());
    oMoveFactory.setSize(oSize.getValue());
    oMoveFactory.setAngle(oAngle.getValue());
    oMoveFactory.setRelativeFactor(oRelFactor.getValue());
    oMoveFactory.setRelativeFreq(1.0);
    oMoveFactory.setRotation(true);

    // generate requested movement, skip if unknown
    if (!oMoveFactory.generateMovement(oCyclicMovement, movement))
        return;    
        
    transmitMovement();

    // if not dual movement, clear any ongoing secondary component
    if (!oCyclicMovement.isDual())
    {
        oArmCyclerClient.setSecondaryAmplitude(0.0);
        oArmCyclerClient.setSecondaryFreq(0.0);        
    }
    
    // start movement
    oArmCyclerClient.run(true);
}

void Artistic::stopMove()
{    
    // stop movement
    oArmCyclerClient.run(false);
}

void Artistic::performChange()
{
    bool bok1 = false, bok2 = false;
    int mode;
    // if change requested 
    if (bchangeRequested) 
    {
        // if speed change requested, change movement frequency
        if (oSpeedTheme.getCode4Name(change, mode))
            bok1 = changeMovementSpeed(mode);
        // if size change requested, change movement amplitude
        else if (oSizeTheme.getCode4Name(change, mode))
            bok1 = changeMovementSize(mode);
        // if length change requested, change movement relative factor
        else if (oLengthTheme.getCode4Name(change, mode))
            bok1 = changeMovementFactor(mode);

        // inform of unavailable changes
        if (!bok1)
            LOG4CXX_WARN(logger, " requested change not available: " << change << ". Ignored!");                     
    }
    
    // if turn requested 
    if (bturnRequested)
    {
        // if turn requested, change movement angle
        if (oDirectionsTheme.getCode4Name(turn, mode))
            bok2 = changeMovementOrientation(mode);

        // inform of unavailable turns
        if (!bok2)
            LOG4CXX_WARN(logger, " requested turn not available: " << turn << ". Ignored!");                     
    }
    
    if (bok1 || bok2)
        transmitMovement();
}

void Artistic::transmitMovement()
{        
    // update both cycler components
    // if dual, set cycler secondary component
   tron::CyclicComponent& oCyclicComponent1 = oCyclicMovement.getPrimaryComponent();
    tron::CyclicComponent& oCyclicComponent2 = oCyclicMovement.getSecondaryComponent();
    bool bdual = oCyclicMovement.isDual();
 
    // send frequency changes
    if (oCyclicMovement.isFreqChanged())
    {
        oArmCyclerClient.setMainFreq(oCyclicComponent1.getFreq());
        if (bdual)
            oArmCyclerClient.setSecondaryFreq(oCyclicComponent2.getFreq());                    
    }
    
    // send amplitude changes
    if (oCyclicMovement.isAmpChanged())
    {
        oArmCyclerClient.setMainAmplitude(oCyclicComponent1.getAmp());
        if (bdual)
            oArmCyclerClient.setSecondaryAmplitude(oCyclicComponent2.getAmp());
    }

    // send angle changes
    if (oCyclicMovement.isAngleChanged())
    {
        oArmCyclerClient.setMainAngle(oCyclicComponent1.getAngle());
        if (bdual)
            oArmCyclerClient.setSecondaryAngle(oCyclicComponent2.getAngle());
    }

    // send phase changes
    if (oCyclicMovement.isPhaseChanged())
    {
        oArmCyclerClient.setMainPhase(oCyclicComponent1.getPhase());            
        if (bdual)
            oArmCyclerClient.setSecondaryPhase(oCyclicComponent2.getPhase());            
    }    
    
    oCyclicMovement.clearFlags();    
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
                LOG4CXX_WARN(logger, " figure not available in movements factory: " << figure);                     
        }
    }
    else                  
        LOG4CXX_WARN(logger, " figure unknown: " << figure);                     
    
    return movement;
}


bool Artistic::changeMovementSpeed(int mode)
{    
    switch (mode)
    {
        case tron2::SpeedTheme::eSPEED_SLOW:
            oFrequency.setLow();
            break;
        case tron2::SpeedTheme::eSPEED_FAST:
            oFrequency.setHigh();
            break;
        case tron2::SpeedTheme::eSPEED_SLOWER:
            oFrequency.decrease();
            break;            
        case tron2::SpeedTheme::eSPEED_FASTER:
            oFrequency.increase();
            break;
        default:
            // return false if change unavailable
            return false;
    }
    
    if (!figure.empty())
        oCyclicMovement.updateFreq(oFrequency.getValue());

    return true;
}

bool Artistic::changeMovementSize(int mode)
{    
    switch (mode)
    {
        case tron2::SizeTheme::eSIZE_SMALL:
            oSize.setLow();
            break;
        case tron2::SizeTheme::eSIZE_BIG:
            oSize.setHigh();
            break;
        case tron2::SizeTheme::eSIZE_SMALLER:
            oSize.decrease();
            break;            
        case tron2::SizeTheme::eSIZE_BIGGER:
            oSize.increase();
            break;
        default:
            // return false if change unavailable
            return false;
    }
    
    if (!figure.empty())
        oCyclicMovement.updateAmplitude(oSize.getValue());
    
    return true;
}

bool Artistic::changeMovementOrientation(int mode)
{    
    switch (mode)
    {
        // turn left (go anticlockwise) -> increase angle
        case tron2::DirectionsTheme::eDIRECTION_LEFT:
            oAngle.increase();
            break;
        // turn right (go clockwise) (decrease angle)           
        case tron2::DirectionsTheme::eDIRECTION_RIGHT:
            oAngle.decrease();
            break;
        default:
            // return false if change unavailable
            return false;
    }    
    
    if (!figure.empty())
        oCyclicMovement.updateAngle(oAngle.getValue());
    
    return true;
}

bool Artistic::changeMovementFactor(int mode)
{    
    switch (mode)
    {
        case tron2::LengthTheme::eLENGTH_SHORT:
            oRelFactor.setLow();
            break;
        case tron2::LengthTheme::eLENGTH_LONG:
            oRelFactor.setHigh();
            break;
        case tron2::LengthTheme::eLENGTH_SHORTER:
            oRelFactor.decrease();
            break;            
        case tron2::LengthTheme::eLENGTH_LONGER:
            oRelFactor.increase();
            break;
        default:
            // return false if change unavailable
            return false;
    }
    
    if (!figure.empty())
        oCyclicMovement.updateRelFactor(oRelFactor.getValue()); 
    
    return true;
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