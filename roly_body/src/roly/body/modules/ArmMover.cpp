/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/body/modules/ArmMover.h"
#include "talky/Talk2Target.h"
#include "talky/topics/ArmTopic.h"


using namespace log4cxx;

namespace roly
{
LoggerPtr ArmMover::logger(Logger::getLogger("roly.body"));

ArmMover::ArmMover()
{
    modName = "ArmMover";
}

//ArmMover::~ArmMover()
//{
//}

void ArmMover::showInitialized()
{
    LOG4CXX_INFO(logger, modName << " initialized");          
}


void ArmMover::first()
{
    // start at WAIT
    setState(eSTATE_WAIT);
    
    log4cxx::NDC::push(modName);   	
}
                    
// performs a cyclic wave movement of the elbow
void ArmMover::loop()
{
    senseBus();
    
    // skip if WAIT 
    if (getState() == eSTATE_WAIT)            
        return;

    if (isStateChanged())
        showState();

    switch (getState())
    {
        case eSTATE_TALK:
            
            // send commands to cycler & go to WAIT    
            talk2Cyclers();
            setState(eSTATE_WAIT);
            break;
    }   // end switch        
    
    //writeBus();
}

void ArmMover::senseBus()
{
    // check move requests
    if (pBodyBus->getCO_MOVER_TYPE().checkRequested())
    {
        // compute movement 
        oCyclicMove = oMoveFactory.computeMove(pBodyBus->getCO_MOVER_TYPE().getValue());
        // and give it an elasticity to change
        oCyclicMove.setElasticity(0.1);
        // prepare to send a trigger message
        message = eMSG_TRIGGER;
        setState(eSTATE_TALK);                       
    }
    
    // check action requests
    if (pBodyBus->getCO_MOVER_ACTION().checkRequested())
    {                
        // prepare to send a trigger or stop message
        if (pBodyBus->getCO_MOVER_ACTION().getValue())
            message = eMSG_TRIGGER;
        else
            message = eMSG_STOP;
        setState(eSTATE_TALK);                       
    }
    
    // check turn requests
    if (pBodyBus->getCO_MOVER_TURN().checkRequested())
    {                
        // update movement orientation
        oCyclicMove.makeTurn(pBodyBus->getCO_MOVER_TURN().getValue());
        // prepare to send an update message
        message = eMSG_UPDATE;
        setState(eSTATE_TALK);                       
    }
        
    // check width requests
    if (pBodyBus->getCO_MOVER_WIDER().checkRequested())
    {                
        // make move wider or narrower
        oCyclicMove.makeWider(pBodyBus->getCO_MOVER_WIDER().getValue());
        // prepare to send an update message
        message = eMSG_UPDATE;
        setState(eSTATE_TALK);                       
    }
        
    // check height requests
    if (pBodyBus->getCO_MOVER_TALLER().checkRequested())
    {                
        // make move taller or shorter
        oCyclicMove.makeTaller(pBodyBus->getCO_MOVER_TALLER().getValue());
        // prepare to send an update message
        message = eMSG_UPDATE;
        setState(eSTATE_TALK);                       
    }
           
    // check speed requests
    if (pBodyBus->getCO_MOVER_FASTER().checkRequested())
    {                
        // make move faster or slower
        oCyclicMove.makeFaster(pBodyBus->getCO_MOVER_FASTER().getValue());
        // prepare to send an update message
        message = eMSG_UPDATE;
        setState(eSTATE_TALK);                       
    }
}

void ArmMover::talk2Cyclers()
{
    switch (message)
    {
        case eMSG_TRIGGER:
            // triggers the cyclic movement
            triggerMove();
            break;
            
        case eMSG_STOP:
            // stops the cyclic movement
            stopMove();
            break;
            
        case eMSG_UPDATE:            
            // changes the cyclic movement           
            updateMove();
            break;
    }
}

void ArmMover::triggerMove()
{    
     LOG4CXX_WARN(logger, modName << " triggerMove");          

     // modulates cyclic movement
    updateMove();
    // starts cycler move
    pBodyTalk->getTalk2ArmCycler().addCommand(talky::ArmTopic::eCYCLIC_FRONT_START);
}

void ArmMover::stopMove()
{    
     LOG4CXX_WARN(logger, modName << " stopMove");          
    // stops cycler move
    pBodyTalk->getTalk2ArmCycler().addCommand(talky::ArmTopic::eCYCLIC_FRONT_STOP);
}

void ArmMover::updateMove()
{        
     LOG4CXX_WARN(logger, modName << " updateMove");          
     
     talky::Talk2Target& oTalk2ArmCycler = pBodyTalk->getTalk2ArmCycler();
    // modulates move of both cycler components
    // first cycler component        
    oTalk2ArmCycler.addCommand(talky::ArmTopic::eCYCLIC_FRONT1_FREQ, oCyclicMove.getFreq1());
    oTalk2ArmCycler.addCommand(talky::ArmTopic::eCYCLIC_FRONT1_ANGLE, oCyclicMove.getAngle1());
    oTalk2ArmCycler.addCommand(talky::ArmTopic::eCYCLIC_FRONT1_AMP, oCyclicMove.getAmp1());
    // second cycler component        
    oTalk2ArmCycler.addCommand(talky::ArmTopic::eCYCLIC_FRONT2_FREQ, oCyclicMove.getFreq2());
    oTalk2ArmCycler.addCommand(talky::ArmTopic::eCYCLIC_FRONT2_ANGLE, oCyclicMove.getAngle2());
    oTalk2ArmCycler.addCommand(talky::ArmTopic::eCYCLIC_FRONT2_AMP, oCyclicMove.getAmp2());
}

void ArmMover::writeBus()
{
    // nothing to do here    
    // control already done by triggerMove, stopMove & updateMove methods
}

void ArmMover::showState()
{
    switch (getState())
    {
        case eSTATE_WAIT:
            LOG4CXX_INFO(logger, ">> wait");
            break;
                        
        case eSTATE_TALK:
            LOG4CXX_INFO(logger, ">> talk");
            break;
    }   // end switch    
}


}