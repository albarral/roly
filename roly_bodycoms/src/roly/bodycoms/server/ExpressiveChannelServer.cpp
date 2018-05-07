/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycoms/server/ExpressiveChannelServer.h"
#include "tron2/robot/RobotNetwork.h"
#include "tron2/robot/RobotSystem.h"
#include "tron2/robot/body/BodyNode.h"
#include "tron2/robot/body/ExpressiveTopic.h"

using namespace log4cxx;

namespace roly
{
ExpressiveChannelServer::ExpressiveChannelServer()
{    
    tron2::ChannelServer::connect2Channel(tron2::RobotSystem::eNODE_BODYROLE, tron2::RobotNetwork::eBODY_EXPRESSIVE_CHANNEL, tron2::BodyNode::eBODY_EXPRESSIVE);    
}

//ExpressiveChannelServer::~ExpressiveChannelServer()
//{    
//}

void ExpressiveChannelServer::processCommands()
{    
    int code;
    float value;
    
    if (!bconnected)
    {
        LOG4CXX_ERROR(logger, "ExpressiveChannelServer: can't process data, not connected to body bus");
        return;        
    }
    
    if (btuned)    
    {        
        // process received messages
        for (std::string message : listMessages)
        {
            LOG4CXX_TRACE(logger, "ExpressiveChannelServer: check msg " << message);
            // if message interpreted, call proper bus action
            if (oTalker.interpretMessage(message, code, value))
            {
                switch (code)
                {
                    case tron2::ExpressiveTopic::eEXPRESS_FEELING:
                        LOG4CXX_INFO(logger, "> express feeling " << (int)value);                        
                        pBodyBus->getCO_EXPRESSIVE_ACTION().request((int)value);
                        break;

                    case tron2::ExpressiveTopic::eEXPRESS_HALT:
                        LOG4CXX_INFO(logger, "> halt expression");                     
                        pBodyBus->getCO_EXPRESSIVE_HALT().request();
                        break;

                    default:
                        LOG4CXX_WARN(logger, "ExpressiveChannelServer: can't process command, untreated concept " << code);                                   
                }    
            }
            else
            {
                LOG4CXX_WARN(logger, "ExpressiveChannelServer: expressive command not interpreted");
            }
        }
    }
    else
    {
        LOG4CXX_ERROR(logger, "ExpressiveChannelServer: can't process data, communicator not tuned");
        return;
    }        
}

}

