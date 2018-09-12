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
    // set topics for arm joints control
    int node = tron::RobotNodes::eNODE_ARM;
    int section = BodyNode2::eeSECTION_JOINTS;
    int type = tron::Topic::eTYPE_CONTROL;
    
    tron::Topic oTopic;
    BodyNode2 oBodyNode;
    // for each channel in section
    for (int channel=0; channel<BodyNode2::eJOINTS_DIM; channel++)
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
    pHSChannel = oComsReceiver.getChannel(BodyNode2::eJOINTS_HS);
    pVSChannel = oComsReceiver.getChannel(BodyNode2::eJOINTS_VS);
    pELBChannel = oComsReceiver.getChannel(BodyNode2::eJOINTS_ELB);
    pHWRIChannel = oComsReceiver.getChannel(BodyNode2::eJOINTS_HWRI);
    pVWRIChannel = oComsReceiver.getChannel(BodyNode2::eJOINTS_VWRI);    
}

//ArtisticServer::~ArtisticServer()
//{    
//}

bool ArtisticServer::getHS(float& value)
{    
    // if hs command received, get it
    if (pHSChannel->hasNew()) 
    {
        value = std::stof(pHSChannel->getMessage());
        LOG4CXX_DEBUG(logger, "ArtisticServer: get HS > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool ArtisticServer::getVS(float& value)
{    
    // if vs command received, get it
    if (pVSChannel->hasNew())
    {
        value = std::stof(pVSChannel->getMessage());
        LOG4CXX_DEBUG(logger, "ArtisticServer: get VS > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool ArtisticServer::getELB(float& value)
{    
    // if elbow command received, get it
    if (pELBChannel->hasNew())
    {
        value = std::stof(pELBChannel->getMessage());
        LOG4CXX_DEBUG(logger, "ArtisticServer: get ELB > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool ArtisticServer::getHWRI(float& value)
{    
    // if h wrist command received, get it
    if (pHWRIChannel->hasNew())
    {
        value = std::stof(pHWRIChannel->getMessage());
        LOG4CXX_DEBUG(logger, "ArtisticServer: get HWRI > " << std::to_string(value));
        return true;
    }
    else
        return false;
}

bool ArtisticServer::getVWRI(float& value)
{    
    // if v wrist command received, get it
    if (pVWRIChannel->hasNew())
    {
        value = std::stof(pVWRIChannel->getMessage());
        LOG4CXX_DEBUG(logger, "ArtisticServer: get VWRI > " << std::to_string(value));
        return true;
    }
    else
        return false;
}
}