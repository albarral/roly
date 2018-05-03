/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycoms/server/ArtisticChannelServer.h"
#include "roly/bodycore/config/BodyConfig.h"
#include "tron2/robot/RobotSystem.h"
#include "tron2/robot/body/BodyNode.h"
#include "tron2/robot/body/ArtisticTopic.h"

using namespace log4cxx;

namespace roly
{
ArtisticChannelServer::ArtisticChannelServer()
{    
    targetModule = 0;
    pArtisticBus = 0;    
    tron2::ChannelServer::tune4NodeAndTopic(tron2::RobotSystem::eNODE_BODYROLE, tron2::BodyNode::eBODY_ARTISTIC);
}

//ArtisticChannelServer::~ArtisticChannelServer()
//{    
//}

void ArtisticChannelServer::setTargetModule(int value)
{
    // safety check
    if (value == BodyConfig::ARTISTIC1 || value == BodyConfig::ARTISTIC2)
    {
        targetModule = value;
    }
}

void ArtisticChannelServer::connect2Bus(BodyBus& oBodyBus)
{
    // accept connection only if target cycler defined
    if (targetModule != 0)
    {
        BodyConnector::connect2Bus(oBodyBus);
        if (targetModule == BodyConfig::ARTISTIC1)
            pArtisticBus = &(oBodyBus.getArtisticBus1());
        else 
            pArtisticBus = &(oBodyBus.getArtisticBus2());
    }
}

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
                    case tron2::ArtisticTopic::eARTISTIC_FIGURE:
                        LOG4CXX_INFO(logger, "> artistic figure " << (int)value);                        
                        pArtisticBus->getCO_ARTISTIC_FIGURE().request((int)value);
                        break;

                    case tron2::ArtisticTopic::eARTISTIC_FREQ:
                        LOG4CXX_INFO(logger, "> artistic freq " << value); 
                        pArtisticBus->getCO_ARTISTIC_FREQ().request(value);
                        break;

                    case tron2::ArtisticTopic::eARTISTIC_SIZE:
                        LOG4CXX_INFO(logger, "> artistic size " << value);                        
                        pArtisticBus->getCO_ARTISTIC_SIZE().request(value);
                        break;

                    case tron2::ArtisticTopic::eARTISTIC_ORIENTATION:
                        LOG4CXX_INFO(logger, "> artistic orientation " << value);                     
                        pArtisticBus->getCO_ARTISTIC_ORIENTATION().request(value);
                        break;

                    case tron2::ArtisticTopic::eARTISTIC_RELFACTOR:
                        LOG4CXX_INFO(logger, "> artistic relative factor " << value);                     
                        pArtisticBus->getCO_ARTISTIC_RELFACTOR().request(value);
                        break;

                    case tron2::ArtisticTopic::eARTISTIC_HALT:
                        LOG4CXX_INFO(logger, "> artistic halt");                     
                        pArtisticBus->getCO_ARTISTIC_HALT().request();
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
