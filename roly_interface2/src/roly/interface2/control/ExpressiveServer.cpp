/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/interface2/control/ExpressiveServer.h"
#include "roly/interface2/BodyNode.h"
#include "tron/topics/RobotNodes.h"
#include "tron/topics/Topic.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr ExpressiveServer::logger(Logger::getLogger("roly.interface"));

ExpressiveServer::ExpressiveServer()
{    
    // set topics for arm joints control
    int node = tron::RobotNodes::eNODE_ARM;
    int section = BodyNode2::eSECTION_EXPRESSIVE;
    int type = tron::Topic::eTYPE_CONTROL;
    
    tron::Topic oTopic;
    BodyNode2 oBodyNode;
    // for each channel in section
    for (int channel=0; channel<BodyNode2::eEXPRESS_DIM; channel++)
    {
        // set its topic 
        oTopic.set(node, section, channel, type);
        // and add a channel reader for it
        if (oBodyNode.buildTopicName(oTopic))
            oComsReceiver.addChannel(oTopic.getTopicName());            
    }
    
    // connect all readers
    oComsReceiver.connect();
    
    // store channel pointers for faster access
    pPanChannel = oComsReceiver.getChannel(BodyNode2::eEXPRESS_FEELING);
    pTiltChannel = oComsReceiver.getChannel(BodyNode2::eEXPRESS_HALT);
}

//ExpressiveServer::~ExpressiveServer()
//{    
//}

bool ExpressiveServer::getPan(float& value)
{    
    // if pan command received, get it
    if (pPanChannel->hasNew())
    {
        value = std::stof(pPanChannel->getMessage());
        LOG4CXX_DEBUG(logger, "ExpressiveServer: get Pan > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool ExpressiveServer::getTilt(float& value)
{    
    // if tilt command received, get it
    if (pTiltChannel->hasNew())
    {
        value = std::stof(pTiltChannel->getMessage());
        LOG4CXX_DEBUG(logger, "ExpressiveServer: get Tilt > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

}