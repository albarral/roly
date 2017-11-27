/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "roly/bodycoms/in/ComsInBodySense.h"
#include "talky/topics/ArmTopic.h"

namespace roly
{
log4cxx::LoggerPtr ComsInBodySense::logger(log4cxx::Logger::getLogger("roly.body.coms"));

ComsInBodySense::ComsInBodySense()
{    
    pBodyBus = 0;
}

void ComsInBodySense::connect2Bus(BodyBus& oBodyBus)
{
    this->pBodyBus = &oBodyBus;
}


bool ComsInBodySense::processArmAxesData(talky::Command& oCommand)
{
    bool bret = true;
    
    // skip if no interface connection
    if (pBodyBus == 0)
    {
        LOG4CXX_ERROR(logger, "ComsInBodySense: can't process command, no bus connection");           
        return false;
    }
    
    float quantity = oCommand.getQuantity();
    
    switch (oCommand.getConcept())
    {
        case talky::ArmTopic::eAXIS_PAN_POS:
            pBodyBus->getSI_ARM_PAN().setValue(quantity);
            break;
            
        case talky::ArmTopic::eAXIS_TILT_POS:
            pBodyBus->getSI_ARM_TILT().setValue(quantity);
            break;

        case talky::ArmTopic::eAXIS_RAD_POS:
            pBodyBus->getSI_ARM_RADIUS().setValue(quantity);
            break;

        case talky::ArmTopic::eAXIS_PAN_SPEED:
            pBodyBus->getSI_ARM_PANSPEED().setValue(quantity);
            break;
            
        case talky::ArmTopic::eAXIS_TILT_SPEED:
           pBodyBus->getSI_ARM_TILTSPEED().setValue(quantity);
            break;

        case talky::ArmTopic::eAXIS_RAD_SPEED:
            pBodyBus->getSI_ARM_RADIALSPEED().setValue(quantity);
            break;
            
        default:
            bret = false;
            LOG4CXX_WARN(logger, "ComsInBodySense: can't process command, untreated axis concept " << oCommand.getConcept());           
    }    
    return bret;
}

void ComsInBodySense::toDoCommand(float value)
{
    // nothing done
    // dummy method for to do commands
    LOG4CXX_INFO(logger, "> to do");                        
}

}