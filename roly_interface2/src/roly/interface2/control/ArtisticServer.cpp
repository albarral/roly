/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/interface2/control/ArtisticServer.h"
#include "roly/interface2/BodyNode.h"
#include "tron/topics/RobotNodes.h"
#include "tron/topics/Topic.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr ArtisticServer::logger(Logger::getLogger("roly.interface"));

ArtisticServer::ArtisticServer()
{    
    // set topics for body artistic control
    int node = tron::RobotNodes::eNODE_BODYROLE;
    int section = BodyNode2::eSECTION_ARTISTIC1;
    int type = tron::Topic::eTYPE_CONTROL;
    
    tron::Topic oTopic;
    BodyNode2 oBodyNode;
    // for each channel in section
    for (int channel=0; channel<BodyNode2::eARTISTIC_DIM; channel++)
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
    pFigureChannel = oComsReceiver.getChannel(BodyNode2::eARTISTIC_FIGURE);
    pFrequencyChannel = oComsReceiver.getChannel(BodyNode2::eARTISTIC_FREQ);
    pSizeChannel = oComsReceiver.getChannel(BodyNode2::eARTISTIC_SIZE);
    pOrientationChannel = oComsReceiver.getChannel(BodyNode2::eARTISTIC_ORIENTATION);
    pRelFactorChannel = oComsReceiver.getChannel(BodyNode2::eARTISTIC_RELFACTOR);    
    pHaltChannel = oComsReceiver.getChannel(BodyNode2::eARTISTIC_HALT);    
}

//ArtisticServer::~ArtisticServer()
//{    
//}

bool ArtisticServer::getFigure(std::string& value)
{    
    // if command received, get it
    if (pFigureChannel->hasNew()) 
    {
        value = pFigureChannel->getMessage();
        LOG4CXX_DEBUG(logger, "ArtisticServer: get figure > " << value);
        return true;
    }
    else
        return false;
}

bool ArtisticServer::getFrequency(float& value)
{    
    // if command received, get it
    if (pFrequencyChannel->hasNew())
    {
        value = std::stof(pFrequencyChannel->getMessage());
        LOG4CXX_DEBUG(logger, "ArtisticServer: get freq > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool ArtisticServer::getSize(float& value)
{    
    // if command received, get it
    if (pSizeChannel->hasNew())
    {
        value = std::stof(pSizeChannel->getMessage());
        LOG4CXX_DEBUG(logger, "ArtisticServer: get size > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool ArtisticServer::getOrientation(float& value)
{    
    // if command received, get it
    if (pOrientationChannel->hasNew())
    {
        value = std::stof(pOrientationChannel->getMessage());
        LOG4CXX_DEBUG(logger, "ArtisticServer: get orientation > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool ArtisticServer::getRelativeFactor(float& value)
{    
    // if command received, get it
    if (pRelFactorChannel->hasNew())
    {
        value = std::stof(pRelFactorChannel->getMessage());
        LOG4CXX_DEBUG(logger, "ArtisticServer: get relative factor > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool ArtisticServer::getHalt()
{    
    // if command received, get it
    if (pHaltChannel->hasNew())
    {
        pHaltChannel->clear();
        LOG4CXX_DEBUG(logger, "ArtisticServer: halt received > ");
        return true;
    }
    else
        return false;
}
}