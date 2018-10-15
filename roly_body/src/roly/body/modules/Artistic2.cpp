/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/body/modules/Artistic2.h"
#include "roly/bodycore/config/ArtisticConfig.h"
#include "roly/bodycore/config/BodyConfig.h"
#include "tron2/moves/CyclicMovement.h"
#include "tron2/language/Language.h"
#include "tron2/language/categories/FeaturesCategory.h"
// module knowledge
#include "tron2/language/features/DirectionsTheme.h"
#include "tron2/language/features/LengthTheme.h"
#include "tron2/language/features/QuantityTheme.h"
#include "tron2/language/features/SizeTheme.h"
#include "tron2/language/features/SpeedTheme.h"
#include "tron2/language/objects/FiguresTheme.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr Artistic2::logger(Logger::getLogger("roly.body"));

Artistic2::Artistic2() : BodyBehaviour("Artistic")
{
    addStateName("idle");
    addStateName("launch");
    addStateName("move");
    addStateName("update");
    addStateName("stop");

    id = -1;
    pArtisticBus = 0;
    
    // set module knowledge 
    tron2::DirectionsTheme oDirectionsTheme; // directions
    tron2::LengthTheme oLengthTheme; // length
    tron2::QuantityTheme oQuantityTheme; // quantity
    tron2::SizeTheme oSizeTheme; // size
    tron2::SpeedTheme oSpeedTheme; // speed
    tron2::FiguresTheme oFiguresTheme; // figures 
    oKnowledge.addTheme(oDirectionsTheme);
    oKnowledge.addTheme(oLengthTheme);
    oKnowledge.addTheme(oQuantityTheme);
    oKnowledge.addTheme(oSizeTheme);
    oKnowledge.addTheme(oSpeedTheme);
    oKnowledge.addTheme(oFiguresTheme);    
}

//Artistic2::~Artistic2()
//{
//}


bool Artistic2::setID(int value)
{
    // check valid id
    if (value == BodyConfig::ARTISTIC1 || value == BodyConfig::ARTISTIC2)
    {
        id = value;
        name += std::to_string(id);
        return true;
    }
    else
    {
        LOG4CXX_WARN(logger, "Artistic2: invalid ID given: " << value);
        return false;
    }
}

void Artistic2::start()
{
    log4cxx::NDC::push(name);   	
    LOG4CXX_INFO(logger, " initialized");          

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
        LOG4CXX_WARN(logger, "Artistic2: invalid ID");
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
    LOG4CXX_INFO(logger, ">> " << getStateName());          
}
                    
void Artistic2::sense()
{
    // TO DO ... get from BUS
    bcontinuous = true;
    bool bnewFigure = false;     
        
     // check inhibition
     inhibit(pArtisticBus->getCO_INHIBIT_ARTISTIC().isRequested());

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

// performs a cyclic wave movement of the elbow
void Artistic2::actuate()
{
    // method skipped when behaviour inhibited

    if (isStateChanged())
        LOG4CXX_INFO(logger, ">> " << getStateName());          

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
}


bool Artistic2::checkMovementFinished()
{
    // TO DO ...
    return false;    
}

void Artistic2::triggerMove()
{    
    int movement;

    // get movement code (movement factory) for requested figure
    // it involves a translation from tron2_language figure to a tron2_moves movement    
    switch (figure) 
    {
        case tron2::FiguresTheme::eFIGURE_CIRCLE:
            movement = tron2::CyclicFactory::eMOVEMENT_CIRCLE;
            // circles have relative factor 1
            oRelFactor.setNormal(1.0);
            oRelFactor.set2Normal();
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

void Artistic2::stopMove()
{    
    // stop movement
    oArmCyclerClient.run(false);
}

void Artistic2::performChange()
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

void Artistic2::transmitMovement()
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

int Artistic2::analyseFigure(std::string word)
{
    // interpret requested figure (only accept objects)
    tron2::Concept* pConcept = checkValidConcept(word, tron2::Language::eLANGUAGE_OBJECT);
    if (pConcept != nullptr)
        return pConcept->getCode();
    // unknown or invalid
    else
        return -1;
}

int Artistic2::analyseChange(std::string word)
{
    changedFeature =  -1;
    bchangeAll = false;

    // interpret requested change (only accept features)
    tron2::Concept* pConcept = checkValidConcept(word, tron2::Language::eLANGUAGE_FEATURE);
    if (pConcept != nullptr)
    {
        int theme = pConcept->getTheme();
        int code = pConcept->getCode();
        // special case: if normal quantity requested, change all features
        if (theme == tron2::FeaturesCategory::eFEATURE_QUANTITY && code == tron2::QuantityTheme::eQUANTITY_NORMAL)
            bchangeAll = true;
        else
            changedFeature = theme;
        
        return code;
    }
    // unknown or invalid
    else
        return -1;
}

int Artistic2::analyseTurn(std::string word)
{
    // interpret requested turn (only accept features)
    tron2::Concept* pConcept = checkValidConcept(word, tron2::Language::eLANGUAGE_FEATURE);
    if (pConcept != nullptr)
    {
        // check that it's a direction command
        if (pConcept->getTheme() == tron2::FeaturesCategory::eFEATURE_DIRECTION)
            return pConcept->getCode();
        else
        {
            LOG4CXX_WARN(logger, "not a direction command. Request ignored!");                     
            return -1;
        }
    }
    // unknown or invalid
    else
        return -1;
}

tron2::Concept* Artistic2::checkValidConcept(std::string word, int category)
{
    // interpret requested command
    tron2::Concept* pConcept = oKnowledge.interpret(word);
    if (pConcept != nullptr)
    {
        // if concept has proper category, return it
        if (pConcept->getCategory() == category)
            return pConcept;
        // otherwise, it's invalid
        else
        {
            LOG4CXX_WARN(logger, "invalid command. Request ignored!");                     
            return nullptr;
        }
    }
    // unknown word
    else
    {
        LOG4CXX_WARN(logger, "unknown command. Request ignored!");                     
        return nullptr;
    }
}

bool Artistic2::changeMovementSpeed(int code)
{    
    switch (code)
    {
        case tron2::SpeedTheme::eSPEED_SLOW:
            oFrequency.set2Low();
            break;
        case tron2::SpeedTheme::eSPEED_FAST:
            oFrequency.set2High();
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

bool Artistic2::changeMovementSize(int code)
{    
    switch (code)
    {
        case tron2::SizeTheme::eSIZE_SMALL:
            oSize.set2Low();
            break;
        case tron2::SizeTheme::eSIZE_BIG:
            oSize.set2High();
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

bool Artistic2::changeMovementOrientation(int code)
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

bool Artistic2::changeMovementFactor(int code)
{    
    switch (code)
    {
        case tron2::LengthTheme::eLENGTH_SHORT:
            oRelFactor.set2Low();
            break;
        case tron2::LengthTheme::eLENGTH_LONG:
            oRelFactor.set2High();
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


void Artistic2::setNormalMovement()
{    
    oFrequency.set2Normal();
    oSize.set2Normal();
    
    if (figure != -1)
    {
        oCyclicMovement.updateFreq(oFrequency.getValue());
        oCyclicMovement.updateAmplitude(oSize.getValue());
    }
}

}