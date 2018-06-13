/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/interface/BodyClient.h"
#include "roly/interface/BodyNode.h"
#include "roly/interface/topics/ArtisticTopic.h"
#include "roly/interface/topics/ExpressiveTopic.h"
#include "tron2/robot/RobotSystem.h"
#include "tron2/robot/common/ExtraTopic.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr BodyClient::logger(Logger::getLogger("tron2.coms"));

BodyClient::BodyClient()
{    
    int node = tron2::RobotSystem::eNODE_BODYROLE;
    int channel = BodyNode::eBODY_EXPRESSIVE_CHANNEL;
    oExpressiveChannelClient.connect2Channel(node, channel, BodyNode::getTopic4Channel(channel));
    channel = BodyNode::eBODY_ARTISTIC1_CHANNEL;
    oArtisticChannelClient1.connect2Channel(node, channel, BodyNode::getTopic4Channel(channel));
    channel = BodyNode::eBODY_ARTISTIC2_CHANNEL;
    oArtisticChannelClient2.connect2Channel(node, channel, BodyNode::getTopic4Channel(channel));
    channel = BodyNode::eBODY_EXTRA_CHANNEL;
    oExtraChannelClient.connect2Channel(node, channel, BodyNode::getTopic4Channel(channel));
}

BodyClient::~BodyClient()
{    
}

// EXPRESSIVE TOPIC ...

bool BodyClient::expressFeeling(int value)
{    
    LOG4CXX_DEBUG(logger, "BodyClient: express feeling > " << std::to_string(value));
    return oExpressiveChannelClient.sendMessage(ExpressiveTopic::eEXPRESS_FEELING, (float)value);
}

bool BodyClient::stopExpression()
{    
    LOG4CXX_DEBUG(logger, "BodyClient: stop expression > ");
    return oExpressiveChannelClient.sendMessage(ExpressiveTopic::eEXPRESS_HALT, 0.0);
}

// ARTISTIC TOPIC ...

bool BodyClient::makeFigure(int value)
{    
    LOG4CXX_DEBUG(logger, "BodyClient: make figure > " << std::to_string(value));
    return oExpressiveChannelClient.sendMessage(ArtisticTopic::eARTISTIC_FIGURE, value);
}

bool BodyClient::setFigureFreq(float value)
{    
    LOG4CXX_DEBUG(logger, "BodyClient: set figure freq > " << std::to_string(value));
    return oExpressiveChannelClient.sendMessage(ArtisticTopic::eARTISTIC_FREQ, value);
}

bool BodyClient::setFigureAmplitude(float value)
{    
    LOG4CXX_DEBUG(logger, "BodyClient: set figure amp > " << std::to_string(value));
    return oExpressiveChannelClient.sendMessage(ArtisticTopic::eARTISTIC_SIZE, value);
}

bool BodyClient::setFigureAngle(float value)
{    
    LOG4CXX_DEBUG(logger, "BodyClient: set figure angle > " << std::to_string(value));
     return oArtisticChannelClient1.sendMessage(ArtisticTopic::eARTISTIC_ORIENTATION, value);
}

bool BodyClient::setFigureFactor(float value)
{    
    LOG4CXX_DEBUG(logger, "BodyClient: set figure factor > " << std::to_string(value));
     return oArtisticChannelClient1.sendMessage(ArtisticTopic::eARTISTIC_RELFACTOR, value);
}

bool BodyClient::stopFigure()
{    
    LOG4CXX_DEBUG(logger, "BodyClient: stop figure > ");
     return oArtisticChannelClient1.sendMessage(ArtisticTopic::eARTISTIC_HALT, 0.0);
}

// EXTRA TOPIC ...

bool BodyClient::fullStop()
{
    LOG4CXX_DEBUG(logger, "BodyClient: full stop > ");     
    return oExtraChannelClient.sendMessage(tron2::ExtraTopic::eEXTRA_STOP, 0.0);        
}

bool BodyClient::endNode()
{
    LOG4CXX_DEBUG(logger, "BodyClient: end body node > ");     
    return oExtraChannelClient.sendMessage(tron2::ExtraTopic::eEXTRA_END, 0.0);        
}
}