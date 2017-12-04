/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/body/modules/Artistic.h"
#include "roly/body/moves/MoveFactory.h"
#include "talky/topics/ArmTopic.h"


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
    oArmFigure.setFreq(1.0);
    oArmFigure.setSize(30.0);
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
        if (orientation > 0)
        {
            oArmFigure.setOrientation(orientation);    
            // if not new figure -> UPDATE movement
            if (!bnewFigure)
                setState(eSTATE_UPDATE);                                       
        }
        else
            LOG4CXX_WARN(logger, modName << " invalid orientation requested " + std::to_string(orientation));                     
    }

    // check relative factor requests
    if (pBodyBus->getCO_ARTISTIC_RELFACTOR().checkRequested())
    {  
        float relFactor = pBodyBus->getCO_ARTISTIC_RELFACTOR().getValue();
        if (relFactor > 0)
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
    
     nety::NetNodeClient& oCyclerClient = pAmyTalker->getArmCyclerClient();
    // sets cycler components
    // first cycler 
    oCyclerClient.addCommand(talky::ArmTopic::eCYCLIC_FRONT1_FREQ, oCyclicMove.getFreq1());
    oCyclerClient.addCommand(talky::ArmTopic::eCYCLIC_FRONT1_ANGLE, oCyclicMove.getAngle1());
    oCyclerClient.addCommand(talky::ArmTopic::eCYCLIC_FRONT1_AMP, oCyclicMove.getAmp1());
    // second cycler
    oCyclerClient.addCommand(talky::ArmTopic::eCYCLIC_FRONT2_FREQ, oCyclicMove.getFreq2());
    oCyclerClient.addCommand(talky::ArmTopic::eCYCLIC_FRONT2_ANGLE, oCyclicMove.getAngle2());
    oCyclerClient.addCommand(talky::ArmTopic::eCYCLIC_FRONT2_AMP, oCyclicMove.getAmp2());
    // start movement
    oCyclerClient.addCommand(talky::ArmTopic::eCYCLIC_FRONT_START);
}

void Artistic::updateMove()
{        
    // update cyclic movement for requested figure changes
    oCyclicMove = MoveFactory::createMove(oArmFigure);

    nety::NetNodeClient& oCyclerClient = pAmyTalker->getArmCyclerClient();
    // update cycler components
    // first cycler component        
    oCyclerClient.addCommand(talky::ArmTopic::eCYCLIC_FRONT1_FREQ, oCyclicMove.getFreq1());
    oCyclerClient.addCommand(talky::ArmTopic::eCYCLIC_FRONT1_ANGLE, oCyclicMove.getAngle1());
    oCyclerClient.addCommand(talky::ArmTopic::eCYCLIC_FRONT1_AMP, oCyclicMove.getAmp1());
    // second cycler component        
    oCyclerClient.addCommand(talky::ArmTopic::eCYCLIC_FRONT2_FREQ, oCyclicMove.getFreq2());
    oCyclerClient.addCommand(talky::ArmTopic::eCYCLIC_FRONT2_ANGLE, oCyclicMove.getAngle2());
    oCyclerClient.addCommand(talky::ArmTopic::eCYCLIC_FRONT2_AMP, oCyclicMove.getAmp2());
}

void Artistic::stopMove()
{    
    // stop movement
    pAmyTalker->getArmCyclerClient().addCommand(talky::ArmTopic::eCYCLIC_FRONT_STOP);
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