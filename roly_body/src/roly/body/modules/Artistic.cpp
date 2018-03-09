/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/body/modules/Artistic.h"
#include "roly/body/moves/MoveFactory.h"

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
    oArmFigure.setFreq(0.5);
    oArmFigure.setSize(40.0);
    oArmFigure.setRelativeFactor(0.5);
    oArmFigure.setOrientation(0.0);
    
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
    bool bnewFigure = false;
        
     // check inhibition
    binhibited = pBodyBus->getCO_INHIBIT_ARTISTIC().isRequested();

    // check figure requests
    if (pBodyBus->getCO_ARTISTIC_FIGURE().checkRequested())
    {
        int figure = pBodyBus->getCO_ARTISTIC_FIGURE().getValue();
        // if figure valid -> LAUNCH movement
        if (figure > ArmFigure::eFIGURE_UNDEFINED && figure < ArmFigure::eFIGURE_DIM)
        {
            oArmFigure.setFigure(figure);
            bnewFigure = true;
            setState(eSTATE_LAUNCH);                       
        }
        else
            LOG4CXX_WARN(logger, modName << " invalid figure requested " + std::to_string(figure));                     
    }
        
    // check freq requests
    if (pBodyBus->getCO_ARTISTIC_FREQ().checkRequested())
    {  
        float freq = pBodyBus->getCO_ARTISTIC_FREQ().getValue();
        if (freq > 0)
        {
            oArmFigure.setFreq(freq);    
            // if not new figure -> UPDATE movement
            if (!bnewFigure)
                setState(eSTATE_UPDATE);                                       
        }
        else
            LOG4CXX_WARN(logger, modName << " invalid freq requested " + std::to_string(freq));                     
    }

    // check size requests
    if (pBodyBus->getCO_ARTISTIC_SIZE().checkRequested())
    {  
        float size = pBodyBus->getCO_ARTISTIC_SIZE().getValue();
        if (size > 0)
        {
            oArmFigure.setSize(size);    
            // if not new figure -> UPDATE movement
            if (!bnewFigure)
                setState(eSTATE_UPDATE);                                       
        }
        else
            LOG4CXX_WARN(logger, modName << " invalid size requested " + std::to_string(size));                     
    }

    // check orientation requests
    if (pBodyBus->getCO_ARTISTIC_ORIENTATION().checkRequested())
    {  
        float orientation = pBodyBus->getCO_ARTISTIC_ORIENTATION().getValue();
        // all orientations are valid
        oArmFigure.setOrientation(orientation);    
        // if not new figure -> UPDATE movement
        if (!bnewFigure)
            setState(eSTATE_UPDATE);                                       
    }

    // check relative factor requests
    if (pBodyBus->getCO_ARTISTIC_RELFACTOR().checkRequested())
    {  
        float relFactor = pBodyBus->getCO_ARTISTIC_RELFACTOR().getValue();
        if (relFactor > 0.0)
        {
            oArmFigure.setRelativeFactor(relFactor);    
            // if not new figure -> UPDATE movement
            if (!bnewFigure)
                setState(eSTATE_UPDATE);                                       
        }
        else
            LOG4CXX_WARN(logger, modName << " invalid relative factor requested " + std::to_string(relFactor));                     
    }

    // if halt requested -> STOP
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
    oCyclicMove = MoveFactory::createMove(oArmFigure);
    
    // sets cycler components
    // first cycler 
    oArmClient.setFrontCyclerAmp1(oCyclicMove.getAmp1());
    oArmClient.setFrontCyclerAngle1(oCyclicMove.getAngle1());
    oArmClient.setFrontCyclerFreq1(oCyclicMove.getFreq1());
    // second cycler
    oArmClient.setFrontCyclerAmp2(oCyclicMove.getAmp2());
    oArmClient.setFrontCyclerAngle2(oCyclicMove.getAngle2());
    oArmClient.setFrontCyclerFreq2(oCyclicMove.getFreq2());
    // phase
    oArmClient.setFrontCyclerPhase(oCyclicMove.getPhase());
    // start movement
    oArmClient.setFrontCyclerAction(1);
}

void Artistic::updateMove()
{        
    // update cyclic movement for requested figure changes
    oCyclicMove = MoveFactory::createMove(oArmFigure);

    // update cycler components
    oArmClient.setFrontCyclerAmp1(oCyclicMove.getAmp1());
    oArmClient.setFrontCyclerAngle1(oCyclicMove.getAngle1());
    oArmClient.setFrontCyclerFreq1(oCyclicMove.getFreq1());
    // second cycler
    oArmClient.setFrontCyclerAmp2(oCyclicMove.getAmp2());
    oArmClient.setFrontCyclerAngle2(oCyclicMove.getAngle2());
    oArmClient.setFrontCyclerFreq2(oCyclicMove.getFreq2());
    // phase
    oArmClient.setFrontCyclerPhase(oCyclicMove.getPhase());
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