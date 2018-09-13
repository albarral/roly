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
    oExtraServer.tune4Node(oBodyNode, BodyNode2::eSECTION_EXTRA);
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
    std::string svalue;
    float value;
        
    // TEMP: TO DO selection of art1 & art2
    ArtisticBus& oArtisticBus = pBodyBus->getArtisticBus1();
    
    if (oArtisticServer.getFigure(svalue))
    {
        oArtisticBus.getCO_ARTISTIC_FIGURE().request(svalue);
        LOG4CXX_INFO(logger, "> set artistic figure " << svalue);                        
    }

    if (oArtisticServer.getFrequency(value))
    {
        oArtisticBus.getCO_ARTISTIC_FREQ().request(value);
        LOG4CXX_INFO(logger, "> set artistic freq " << value);                        
    }

    if (oArtisticServer.getSize(value))
    {
        oArtisticBus.getCO_ARTISTIC_SIZE().request(value);
        LOG4CXX_INFO(logger, "> set artistic size " << value);                        
    }

    if (oArtisticServer.getOrientation(value))
    {
        oArtisticBus.getCO_ARTISTIC_ORIENTATION().request(value);
        LOG4CXX_INFO(logger, "> set artistic orientation " << value);                        
    }

    if (oArtisticServer.getRelativeFactor(value))
    {
        oArtisticBus.getCO_ARTISTIC_RELFACTOR().request(value);
        LOG4CXX_INFO(logger, "> set artistic relative factor " << value);                        
    }

    if (oArtisticServer.getHalt())
    {
        oArtisticBus.getCO_ARTISTIC_HALT().request();
        LOG4CXX_INFO(logger, "> halt artistic");                        
    }
}

//void BodyServer2::checkAxesSection()
//{
//    float value;
//    bool bvalue;
//    if (oAxesServer.getPan(value))
//    {
//        pBodyBus->getPanBus().getCO_AXIS_POS().request(value);
//        LOG4CXX_INFO(logger, "> set pan " << value);                        
//    }
//    
//    if (oAxesServer.getTilt(value))
//    {
//        pBodyBus->getTiltBus().getCO_AXIS_POS().request(value);
//        LOG4CXX_INFO(logger, "> set tilt " << value);                        
//    }
//
//    if (oAxesServer.getRadial(value))
//    {
//        pBodyBus->getRadialBus().getCO_AXIS_POS().request(value);
//        LOG4CXX_INFO(logger, "> set radius " << value);                        
//    }
//
//    if (oAxesServer.getPanSpeed(value))
//    {
//        pBodyBus->getPanBus().getCO_AXIS_SPEED1().request(value);
//        LOG4CXX_INFO(logger, "> pan speed " << value);                        
//    }
//
//    if (oAxesServer.getTiltSpeed(value))
//    {
//       pBodyBus->getTiltBus().getCO_AXIS_SPEED1().request(value);
//       LOG4CXX_INFO(logger, "> tilt speed " << value);                        
//    }
//
//    if (oAxesServer.getRadialSpeed(value))
//    {
//        pBodyBus->getRadialBus().getCO_AXIS_SPEED1().request(value);
//        LOG4CXX_INFO(logger, "> rad speed " << value);                                
//    }
//
//    if (oAxesServer.getKeepTilt(bvalue))
//    {
//        pBodyBus->getCO_KEEP_TILT().request((int)bvalue);
//        LOG4CXX_INFO(logger, "> keep tilt " << value);                        
//    }    
//}
//
//void BodyServer2::checkCyclerSection(int i)
//{
//    // security check
//    if (i<1 && i>2) 
//        return; 
//        
//    // select cycler server to use
//    CyclerServer& oCyclerServer = (i==1) ? oCyclerServer1 : oCyclerServer2;        
//    CyclerBus& oCyclerBus = (i==1) ? pBodyBus->getCyclerBus1() : pBodyBus->getCyclerBus2(); 
//    std::string identity = (i==1) ? "> cycler1 " : "> cycler2 ";
//       
//    float value;
//    int ivalue;
//    if (oCyclerServer.getMainFreq(value))
//    {
//        oCyclerBus.getCO_CYCLER_FREQ1().request(value);
//        LOG4CXX_INFO(logger, identity << "main freq " << value);                        
//    }
//    
//    if (oCyclerServer.getMainAmplitude(value))
//    {
//        oCyclerBus.getCO_CYCLER_AMP1().request(value);
//        LOG4CXX_INFO(logger, identity << "main amplitude " << value);                        
//    }
//
//    if (oCyclerServer.getMainAngle(value))
//    {
//        oCyclerBus.getCO_CYCLER_ANGLE1().request(value);
//        LOG4CXX_INFO(logger, identity << "main angle " << value);                        
//    }
//
//    if (oCyclerServer.getMainPhase(value))
//    {
//        oCyclerBus.getCO_CYCLER_PHASE1().request((int)value);
//        LOG4CXX_INFO(logger, identity << "main phase " << value);                        
//    }
//
//    if (oCyclerServer.getSecondaryFreq(value))
//    {
//        oCyclerBus.getCO_CYCLER_FREQ2().request(value);
//        LOG4CXX_INFO(logger, identity << "secondary freq " << value);                        
//    }
//    
//    if (oCyclerServer.getSecondaryAmplitude(value))
//    {
//        oCyclerBus.getCO_CYCLER_AMP2().request(value);
//        LOG4CXX_INFO(logger, identity << "secondary amplitude " << value);                        
//    }
//
//    if (oCyclerServer.getSecondaryAngle(value))
//    {
//        oCyclerBus.getCO_CYCLER_ANGLE2().request(value);
//        LOG4CXX_INFO(logger, identity << "secondary angle " << value);                        
//    }
//
//    if (oCyclerServer.getSecondaryPhase(value))
//    {
//        oCyclerBus.getCO_CYCLER_PHASE2().request((int)value);
//        LOG4CXX_INFO(logger, identity << "secondary phase " << value);                        
//    }
//
//    if (oCyclerServer.getAction(ivalue))
//    {
//        bool bgo = (ivalue != 0); 
//        oCyclerBus.getCO_CYCLER_ACTION().request(bgo);
//        LOG4CXX_INFO(logger, identity << " action " << bgo);                        
//    }
//}

void BodyServer2::checkExtraSection()
{
    if (oExtraServer.getStop())
    {
        LOG4CXX_INFO(logger, "> stop");                        
    }

    if (oExtraServer.getEnd())
    {
        bEndRequested = true;
        LOG4CXX_INFO(logger, "> end roly");  
    }
}

}