/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/interface2/control/ArtisticServer.h"
#include "roly/interface2/BodyNode.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr ArtisticServer::logger2(Logger::getLogger("roly.interface"));

ArtisticServer::ArtisticServer()
{    
    target = 0;
    serverName = "ArtisticServer";
    
    pFigureChannel = 0;
    pChangesChannel = 0;
    pTurnsChannel = 0;
    pHaltChannel = 0;
}

//ArtisticServer::~ArtisticServer()
//{    
//}

bool ArtisticServer::tune2Artistic(int i)
{
    if (i < 1 || i > 2)
    {
        LOG4CXX_WARN(logger2, serverName + ": invalid target, must be tuned to artistic module 1 or 2");
        return false;
    }
    
    target = i;
    serverName += std::to_string(target);

    // set proper section
    int section = (target == 1) ? BodyNode2::eSECTION_ARTISTIC1: BodyNode2::eSECTION_ARTISTIC2;
    
    // set topics for body artistic control
    BodyNode2 oBodyNode;
    tron::SectionServer::tune4Node(oBodyNode, section);

    if (isTuned())
    {
        // store channel pointers for faster access
        pFigureChannel = oComsReceiver.getChannel(BodyNode2::eARTISTIC_FIGURE);
        pChangesChannel = oComsReceiver.getChannel(BodyNode2::eARTISTIC_SET);
        pTurnsChannel = oComsReceiver.getChannel(BodyNode2::eARTISTIC_TURN);
        pHaltChannel = oComsReceiver.getChannel(BodyNode2::eARTISTIC_HALT);    
    }
        
    return btuned;
}

bool ArtisticServer::getFigure(std::string& value)
{    
    // if command received, get it
    if (pFigureChannel->hasNew()) 
    {
        value = pFigureChannel->getMessage();
        LOG4CXX_DEBUG(logger2, serverName + ": get figure > " << value);
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
        LOG4CXX_DEBUG(logger2, serverName + ": get change > " << value);
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
        LOG4CXX_DEBUG(logger2, serverName + ": get turn > " << value);
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
        LOG4CXX_DEBUG(logger2, serverName + ": halt received > ");
        return true;
    }
    else
        return false;
}
}