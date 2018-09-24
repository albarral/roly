/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/bodycoms/modules/BodyServer.h"
#include "roly/bodycore/config/BodyConfig.h"
#include "roly/interface2/BodyNode.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr BodyServer::logger(Logger::getLogger("roly.coms"));

// Constructor 
BodyServer::BodyServer()
{    
    modName = "BodyServer2";
    benabled = false;
    pArtisticBus1 = 0;
    pArtisticBus2 = 0;
    bEndRequested = false;
    // tune artistic servers
    oArtisticServer1.tune2Artistic(BodyConfig::ARTISTIC1);
    oArtisticServer2.tune2Artistic(BodyConfig::ARTISTIC2);
    // tune extra server
    BodyNode2 oBodyNode;
    oExtraServer.init(oBodyNode, BodyNode2::eSECTION_EXTRA);
 }

void BodyServer::init(BodyBus& oBodyBus)
{
    pArtisticBus1 = &(oBodyBus.getArtisticBus1());
    pArtisticBus2 = &(oBodyBus.getArtisticBus2());
        
    // if servers enabled
    if (oArtisticServer1.isTuned() && oArtisticServer2.isTuned())
    {
        benabled = true;
        LOG4CXX_INFO(logger, modName + " initialized");                                
    }
    else
        LOG4CXX_ERROR(logger, modName + ": failed initialization, some servers not tuned!");                        
}

void BodyServer::first()
{    
    log4cxx::NDC::push(modName);   	
}

void BodyServer::loop()
{
    // check artistic 1 section
    checkArtisticSection1();
    // check artistic 2 section
    checkArtisticSection2();
    // check extra section
    checkExtraSection();
}


void BodyServer::checkArtisticSection1()
{
    std::string value;
    
    if (oArtisticServer1.getFigure(value))
    {
        pArtisticBus1->getCO_ARTISTIC_FIGURE().request(value);
        LOG4CXX_INFO(logger, "< art1 figure: " << value);                        
    }

    if (oArtisticServer1.getMovementChange(value))
    {
        pArtisticBus1->getCO_ARTISTIC_SET().request(value);
        LOG4CXX_INFO(logger, "< art1 change: " << value);                        
    }

    if (oArtisticServer1.getMovementTurn(value))
    {
        pArtisticBus1->getCO_ARTISTIC_TURN().request(value);
        LOG4CXX_INFO(logger, "< art1 turn: " << value);                        
    }

    if (oArtisticServer1.getHalt())
    {
        pArtisticBus1->getCO_ARTISTIC_HALT().request();
        LOG4CXX_INFO(logger, "< art1 halt");                        
    }
}

void BodyServer::checkArtisticSection2()
{
    std::string value;
    
    if (oArtisticServer2.getFigure(value))
    {
        pArtisticBus2->getCO_ARTISTIC_FIGURE().request(value);
        LOG4CXX_INFO(logger, "< art2 figure: " << value);                        
    }

    if (oArtisticServer2.getMovementChange(value))
    {
        pArtisticBus2->getCO_ARTISTIC_SET().request(value);
        LOG4CXX_INFO(logger, "< art2 change: " << value);                        
    }

    if (oArtisticServer2.getMovementTurn(value))
    {
        pArtisticBus2->getCO_ARTISTIC_TURN().request(value);
        LOG4CXX_INFO(logger, "< art2 turn: " << value);                        
    }

    if (oArtisticServer2.getHalt())
    {
        pArtisticBus2->getCO_ARTISTIC_HALT().request();
        LOG4CXX_INFO(logger, "< art2 halt");                        
    }
}

void BodyServer::checkExtraSection()
{
    if (oExtraServer.getStop())
    {
        LOG4CXX_INFO(logger, "< stop");                        
    }

    if (oExtraServer.getEnd())
    {
        bEndRequested = true;
        LOG4CXX_INFO(logger, "< end roly");  
    }
}

}