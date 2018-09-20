/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/interface2/control/ArtisticServer.h"
#include "roly/interface2/BodyNode.h"
#include "tron/topics/RobotNodes.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr ArtisticServer::logger2(Logger::getLogger("roly.interface"));

ArtisticServer::ArtisticServer()
{    
    // set topics for body artistic control
    BodyNode2 oBodyNode;
    tron::SectionServer::tune4Node(tron::RobotNodes::eNODE_BODYROLE, BodyNode2::eSECTION_ARTISTIC1, oBodyNode);

    if (isTuned())
    {
        // store channel pointers for faster access
        pFigureChannel = oComsReceiver.getChannel(BodyNode2::eARTISTIC_FIGURE);
        pChangesChannel = oComsReceiver.getChannel(BodyNode2::eARTISTIC_SET);
        pTurnsChannel = oComsReceiver.getChannel(BodyNode2::eARTISTIC_TURN);
        pHaltChannel = oComsReceiver.getChannel(BodyNode2::eARTISTIC_HALT);    
    }
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
        LOG4CXX_DEBUG(logger2, "ArtisticServer: get figure > " << value);
        return true;
    }
    else
        return false;
}

bool ArtisticServer::getMovementChange(std::string& value)
{    
    // if command received, get it
    if (pChangesChannel->hasNew())
    {
        value = pChangesChannel->getMessage();
        LOG4CXX_DEBUG(logger2, "ArtisticServer: get change > " << value);
        return true;
    }
    else
        return false;
}

bool ArtisticServer::getMovementTurn(std::string& value)
{    
    // if command received, get it
    if (pTurnsChannel->hasNew())
    {
        value = pTurnsChannel->getMessage();
        LOG4CXX_DEBUG(logger2, "ArtisticServer: get turn > " << value);
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
        LOG4CXX_DEBUG(logger2, "ArtisticServer: halt received > ");
        return true;
    }
    else
        return false;
}
}