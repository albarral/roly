/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycoms/server/ExtraChannelServer.h"
#include "tron2/talky/BasicTalker.h"
#include "tron2/robot/RobotNodes.h"
#include "tron2/robot/topics/BodyTopics.h"

using namespace log4cxx;

namespace roly
{
ExtraChannelServer::ExtraChannelServer() : ChannelServer(tron2::RobotNodes::eNODE_BODYROLE, tron2::BodyTopics::eBODY_EXTRA)
{    
    bEndRequested = false;
}

//ExtraChannelServer::~ExtraChannelServer()
//{    
//}

void ExtraChannelServer::processCommands()
{    
    int code;
    float value;
    
    if (!bconnected)
    {
        LOG4CXX_ERROR(logger, "ExtraChannelServer: can't process data, not connected to body bus");
        return;        
    }
    
    if (btuned)    
    {        
        // process received messages
        for (std::string message : listMessages)
        {
            LOG4CXX_TRACE(logger, "ExtraChannelServer: check msg " << message);
            // if message interpreted, call proper bus action
            if (pTalker->interpretMessage(message, code, value))
            {
                switch (code)
                {
                    case tron2::BasicTalker::eBASIC_FULL_STOP:
                        LOG4CXX_INFO(logger, "> body stop ... TO DO");                        
                        break;

                    case tron2::BasicTalker::eBASIC_CONTROL_END:
                        LOG4CXX_INFO(logger, "> end body");  
                        bEndRequested = true;
                        break;

                    default:
                        LOG4CXX_WARN(logger, "ExtraChannelServer: can't process command, untreated concept " << code);                                   
                }    
            }
            else
            {
                LOG4CXX_WARN(logger, "ExtraChannelServer: extra command not interpreted");
            }
        }
    }
    else
    {
        LOG4CXX_ERROR(logger, "ExtraChannelServer: can't process data, communicator not tuned");
        return;
    }        
}

}
