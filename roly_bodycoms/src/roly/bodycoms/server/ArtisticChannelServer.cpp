/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycoms/server/ArtisticChannelServer.h"
#include "tron2/talky/body/ArtisticTalker.h"
#include "tron2/robot/RobotNodes.h"
#include "tron2/robot/topics/BodyTopics.h"

using namespace log4cxx;

namespace roly
{
ArtisticChannelServer::ArtisticChannelServer() : ChannelServer(tron2::RobotNodes::eNODE_BODYROLE, tron2::BodyTopics::eBODY_ARTISTIC)
{    
}

//ArtisticChannelServer::~ArtisticChannelServer()
//{    
//}

void ArtisticChannelServer::processCommands()
{    
    int code;
    float value;
    
    if (!bconnected)
    {
        LOG4CXX_ERROR(logger, "ArtisticChannelServer: can't process data, not connected to body bus");
        return;        
    }
    
    if (btuned)    
    {        
        // process received messages
        for (std::string message : listMessages)
        {
            LOG4CXX_TRACE(logger, "ArtisticChannelServer: check msg " << message);
            // if message interpreted, call proper bus action
            if (pTalker->interpretMessage(message, code, value))
            {
                switch (code)
                {
                    case tron2::ArtisticTalker::eARTISTIC_FIGURE:
                        LOG4CXX_INFO(logger, "> artistic figure " << (int)value);                        
                        pBodyBus->getCO_ARTISTIC_FIGURE().request((int)value);
                        break;

                    case tron2::ArtisticTalker::eARTISTIC_FREQ:
                        LOG4CXX_INFO(logger, "> artistic freq " << value); 
                        pBodyBus->getCO_ARTISTIC_FREQ().request(value);
                        break;

                    case tron2::ArtisticTalker::eARTISTIC_SIZE:
                        LOG4CXX_INFO(logger, "> artistic size " << value);                        
                        pBodyBus->getCO_ARTISTIC_SIZE().request(value);
                        break;

                    case tron2::ArtisticTalker::eARTISTIC_ORIENTATION:
                        LOG4CXX_INFO(logger, "> artistic orientation " << value);                     
                        pBodyBus->getCO_ARTISTIC_ORIENTATION().request(value);
                        break;

                    case tron2::ArtisticTalker::eARTISTIC_RELFACTOR:
                        LOG4CXX_INFO(logger, "> artistic relative factor " << value);                     
                        pBodyBus->getCO_ARTISTIC_RELFACTOR().request(value);
                        break;

                    case tron2::ArtisticTalker::eARTISTIC_HALT:
                        LOG4CXX_INFO(logger, "> artistic halt");                     
                        pBodyBus->getCO_ARTISTIC_HALT().request();
                        break;

                    default:
                        LOG4CXX_WARN(logger, "ArtisticChannelServer: can't process command, untreated concept " << code);                                   
                }    
            }
            else
            {
                LOG4CXX_WARN(logger, "ArtisticChannelServer: artistic command not interpreted");
            }
        }
    }
    else
    {
        LOG4CXX_ERROR(logger, "ArtisticChannelServer: can't process data, communicator not tuned");
        return;
    }        
}

}
