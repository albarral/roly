/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "roly/bodycoms/modules/BodyServer2.h"
#include "roly/bodycore/ArtisticBus.h"
#include "roly/interface2/BodyNode.h"

using namespace log4cxx;

namespace roly
{
LoggerPtr BodyServer2::logger(Logger::getLogger("roly.coms"));

// Constructor 
BodyServer2::BodyServer2()
{    
    modName = "BodyServer2";
    benabled = false;
    pBodyBus = 0;
    bEndRequested = false;
    // tune cycler servers
//    oCyclerServer1.tune2Cycler(AmyConfig::CYCLER1);
//    oCyclerServer2.tune2Cycler(AmyConfig::CYCLER2);
    // tune extra server
    BodyNode2 oBodyNode;
    oExtraServer.init(oBodyNode, BodyNode2::eSECTION_EXTRA);
 }

void BodyServer2::init(BodyBus& oBodyBus)
{
    pBodyBus = &oBodyBus;
    
    // prepare communication servers
    //oExtraChannelServer.connect2Bus(oBodyBus);    
    
    // if servers enabled
//    if (oCyclerServer1.isTuned() && oCyclerServer2.isTuned())
    {
        benabled = true;
        LOG4CXX_INFO(logger, modName + " initialized");                                
    }
//    else
//        LOG4CXX_ERROR(logger, modName + ": failed initialization, some servers not tuned!");                        
}

void BodyServer2::first()
{    
    log4cxx::NDC::push(modName);   	
}

void BodyServer2::loop()
{
    // check joints section
    checkArtisticSection();
    // check axes section
    //checkAxesSection();
    // check cycler1 channel
    //checkCyclerSection(1);
    // check cycler2 channel
    //checkCyclerSection(2);
    // check extra channel
    checkExtraSection();
}


void BodyServer2::checkArtisticSection()
{
    std::string value;
        
    // TEMP: TO DO selection of art1 & art2
    ArtisticBus& oArtisticBus = pBodyBus->getArtisticBus1();
    
    if (oArtisticServer.getFigure(value))
    {
        oArtisticBus.getCO_ARTISTIC_FIGURE().request(value);
        LOG4CXX_INFO(logger, "< art1 figure: " << value);                        
    }

    if (oArtisticServer.getMovementChange(value))
    {
        oArtisticBus.getCO_ARTISTIC_SET().request(value);
        LOG4CXX_INFO(logger, "< art1 change: " << value);                        
    }

    if (oArtisticServer.getMovementTurn(value))
    {
        oArtisticBus.getCO_ARTISTIC_TURN().request(value);
        LOG4CXX_INFO(logger, "< art1 turn: " << value);                        
    }

    if (oArtisticServer.getHalt())
    {
        oArtisticBus.getCO_ARTISTIC_HALT().request();
        LOG4CXX_INFO(logger, "< art1 halt");                        
    }
}


void BodyServer2::checkExtraSection()
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