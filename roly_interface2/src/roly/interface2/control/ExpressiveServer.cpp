/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/interface2/control/ExpressiveServer.h"
#include "roly/interface2/BodyNode.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr ExpressiveServer::logger2(Logger::getLogger("roly.interface"));

ExpressiveServer::ExpressiveServer()
{    
    // set topics for body expressive control
    BodyNode2 oBodyNode;
    tron::SectionServer::tune4Node(oBodyNode, BodyNode2::eSECTION_EXPRESSIVE);

    if (isTuned())
    {
        // store channel pointers for faster access
        pFeelingChannel = oComsReceiver.getChannel(BodyNode2::eEXPRESS_FEELING);
        pHaltChannel = oComsReceiver.getChannel(BodyNode2::eEXPRESS_HALT);
    }
}

//ExpressiveServer::~ExpressiveServer()
//{    
//}

bool ExpressiveServer::getFeeling(std::string& value)
{    
    // if command received, get it
    if (pFeelingChannel->hasNew())
    {
        value = pFeelingChannel->getMessage();
        LOG4CXX_DEBUG(logger2, "ExpressiveServer: get feeling > " << value);
        return true;
    }
    else
        return false;
}

bool ExpressiveServer::getHalt()
{    
    // if command received, get it
    if (pHaltChannel->hasNew())
    {
        pHaltChannel->clear();
        LOG4CXX_DEBUG(logger2, "ExpressiveServer: halt received > ");
        return true;
    }
    else
        return false;
}

}