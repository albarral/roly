/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/body/modules/Artistic.h"
#include "roly/bodycore/config/ArtisticConfig.h"
#include "roly/bodycore/config/BodyConfig.h"
#include "tron2/language/categories/FeaturesCategory.h"
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
    oCyclicFactory.setRelativeFreq(oArtisticConfig.getRelativeFreq());
    oCyclicFactory.setRotation(oArtisticConfig.getRotation());
    
    // start at IDLE
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
            // -> MOVE
            setState(eSTATE_MOVE);
            break;

        case eSTATE_MOVE:
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
            // -> MOVE
            setState(eSTATE_MOVE);
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
    bool bnewFigure = false;     
        
     // check inhibition
    binhibited = pArtisticBus->getCO_INHIBIT_ARTISTIC().isRequested();

    // check figure requests
    if (pArtisticBus->getCO_ARTISTIC_FIGURE().checkRequested())
    {
        bnewFigure = false;
        std::string command = pArtisticBus->getCO_ARTISTIC_FIGURE().getValue();
        if (!command.empty())
        {
            LOG4CXX_INFO(logger, "< figure: " + command);                     
            figure = analyseFigure(command);
            bnewFigure = (figure != -1);
        }
    }
        
    // check change requests
    if (pArtisticBus->getCO_ARTISTIC_SET().checkRequested())
    {  
        bnewChange = false;
        std::string command = pArtisticBus->getCO_ARTISTIC_SET().getValue();
        // analyze change validity 
        if (!command.empty())
        {
            LOG4CXX_INFO(logger, "< change: " + command);                     
            change = analyseChange(command);
            // if anything to be changed
            bnewChange = bchangeAll || (change != -1);
        }
    }
    else if (bnewChange)
        bnewChange = false;

    // check turn requests
    if (pArtisticBus->getCO_ARTISTIC_TURN().checkRequested())
    {      
        bnewTurn = false;        
        std::string command = pArtisticBus->getCO_ARTISTIC_TURN().getValue();
        // analyze turn validity            
        if (!command.empty())
        {
            LOG4CXX_INFO(logger, "< turn: " + command);                     
            turn = analyseTurn(command);
            bnewTurn = (turn != -1);
        }
    }
    else if (bnewTurn)
        bnewTurn = false;


    // if new figure requested -> LAUNCH
    if (bnewFigure)
        setState(eSTATE_LAUNCH);                                       
    // otherwise if movement change requested -> UPDATE
    else if (bnewChange || bnewTurn)
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
    int movement;

    // get movement code (movement factory) for requested figure
    // it involves a translation from tron2_language figure to a tron2_moves movement    
    switch (figure) 
    {
        case tron2::FiguresTheme::eFIGURE_CIRCLE:
            movement = tron2::CyclicFactory::eMOVEMENT_CIRCLE;
            break;
        case tron2::FiguresTheme::eFIGURE_ELLIPSE:
            movement = tron2::CyclicFactory::eMOVEMENT_ELLIPSE;
            break;
        case tron2::FiguresTheme::eFIGURE_SQUARE:
            movement = tron2::CyclicFactory::eMOVEMENT_SQUARE;
            break;
        case tron2::FiguresTheme::eFIGURE_RECTANGLE:
            movement = tron2::CyclicFactory::eMOVEMENT_RECTANGLE;
            break;
        case tron2::FiguresTheme::eFIGURE_TRIANGLE:
            movement = tron2::CyclicFactory::eMOVEMENT_TRIANGLE;
            break;
        case tron2::FiguresTheme::eFIGURE_LINE:
            movement = tron2::CyclicFactory::eMOVEMENT_LINE;
            break;
        case tron2::FiguresTheme::eFIGURE_WAVE:
            movement = tron2::CyclicFactory::eMOVEMENT_WAVE;
            break;                
        default:
            movement = -1;
            LOG4CXX_WARN(logger, " figure not available in movements factory");                     
    }
    
    // skip if figure unknown
    if (movement == -1)
        return;

    oCyclicFactory.setFreq(oFrequency.getValue());
    oCyclicFactory.setSize(oSize.getValue());
    oCyclicFactory.setAngle(oAngle.getValue());
    oCyclicFactory.setRelativeFactor(oRelFactor.getValue());
    oCyclicFactory.setRelativeFreq(1.0);
    oCyclicFactory.setRotation(true);

    // generate requested movement, skip if unknown
    if (!oCyclicFactory.generateMovement(oCyclicMovement, movement))
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
    // if change requested 
    if (bnewChange) 
    {
        // if global change 
        if (bchangeAll)
        {
            // change everything to normal            
            setNormalMovement();
            bok1 = true;            
        }
        // if particular change
        else
        {
            switch (changedFeature)
            {
                // if speed change requested, change movement frequency
                case tron2::FeaturesCategory::eFEATURE_SPEED:
                    bok1 = changeMovementSpeed(change);
                    break;

                // if size change requested, change movement amplitude
                case tron2::FeaturesCategory::eFEATURE_SIZE:
                    bok1 = changeMovementSize(change);
                    break;

                // if length change requested, change movement relative factor
                case tron2::FeaturesCategory::eFEATURE_LENGTH:
                    bok1 = changeMovementFactor(change);
                    break;
            }
            // inform of unavailable changes
            if (!bok1)
                LOG4CXX_WARN(logger, "requested change not available. Ignored!");      
        }
    }
            
    // if turn requested 
    if (bnewTurn)
    {
        // if turn requested, change movement angle
        bok2 = changeMovementOrientation(turn);

        // inform of unavailable turns
        if (!bok2)
            LOG4CXX_WARN(logger, " requested turn not available. Ignored!");                     
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

int Artistic::analyseFigure(std::string word)
{
    int code = -1;

    // check requested figure
    if (oFiguresTheme.getCode4Name(word, code))
        return code;            
    // inform of unknown request
    else
    {
        LOG4CXX_WARN(logger, "unknown figure requested: " << word << ". Ignored!");                     
        return -1;
    }
}

int Artistic::analyseChange(std::string word)
{
    int code = -1;
    bchangeAll = false;

    // check if generic change requested
    if (oQuantityTheme.getCode4Name(word, code))
    {
        // just accept normal word 
        bchangeAll = (code == tron2::QuantityTheme::eQUANTITY_NORMAL);
    }
    // check if speed change requested
    else if (oSpeedTheme.getCode4Name(word, code))
        changedFeature =  tron2::FeaturesCategory::eFEATURE_SPEED;
    // check if size change requested
    else if (oSizeTheme.getCode4Name(word, code))
        changedFeature =  tron2::FeaturesCategory::eFEATURE_SIZE;
    // check if length change requested
    else if (oLengthTheme.getCode4Name(word, code))
        changedFeature =  tron2::FeaturesCategory::eFEATURE_LENGTH;
    // inform of unknown request
    else
    {
        LOG4CXX_WARN(logger, "unknown change requested: " << word << ". Ignored!");                     
        changedFeature =  -1;
    }
    
    return code;
}

int Artistic::analyseTurn(std::string word)
{
    int code = -1;

    // check requested turn 
    if (oDirectionsTheme.getCode4Name(word, code))
        return code;            
    // inform of unknown request
    else
    {
        LOG4CXX_WARN(logger, "unknown turn requested: " << word << ". Ignored!");                     
        return -1;
    }
}


bool Artistic::changeMovementSpeed(int code)
{    
    switch (code)
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
    
    if (figure != -1)
        oCyclicMovement.updateFreq(oFrequency.getValue());

    return true;
}

bool Artistic::changeMovementSize(int code)
{    
    switch (code)
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
    
    if (figure != -1)
        oCyclicMovement.updateAmplitude(oSize.getValue());
    
    return true;
}

bool Artistic::changeMovementOrientation(int code)
{    
    switch (code)
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
    
    if (figure != -1)
        oCyclicMovement.updateAngle(oAngle.getValue());
    
    return true;
}

bool Artistic::changeMovementFactor(int code)
{    
    switch (code)
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
    
    if (figure != -1)
        oCyclicMovement.updateRelFactor(oRelFactor.getValue()); 
    
    return true;
}


void Artistic::setNormalMovement()
{    
    oFrequency.setNormal();
    oSize.setNormal();
    oRelFactor.setNormal();
    
    if (figure != -1)
    {
        oCyclicMovement.updateFreq(oFrequency.getValue());
        oCyclicMovement.updateAmplitude(oSize.getValue());
        oCyclicMovement.updateRelFactor(oRelFactor.getValue());         
    }
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
        case eSTATE_MOVE:
            LOG4CXX_INFO(logger, ">> move");
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