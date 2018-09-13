#ifndef __ROLY_BODYCOMS_BODYSERVER2_H
#define __ROLY_BODYCOMS_BODYSERVER2_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/bodycore/BodyBus.h"
#include "roly/interface2/control/ArtisticServer.h"
//#include "amy/interface2/control/AxesServer.h"
//#include "amy/interface2/control/CyclerServer.h"
#include "tron/control/module3.h"
#include "tron/interface/ExtraServer.h"

namespace roly
{
// This module serves external control requests for arm control. 
// It uses an ignition based server for each arm node's section.
class BodyServer2 : public tron::Module3
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
    BodyBus* pBodyBus;      // access to body bus    
    ArtisticServer oArtisticServer;
//    AxesServer oAxesServer;    
//    CyclerServer oCyclerServer1;
//    CyclerServer oCyclerServer2;
    tron::ExtraServer oExtraServer;      
    bool bEndRequested;         // end of roly process requested

public:
    BodyServer2();
    //~BodyServer2();

    void init(BodyBus& oBodyBus);       
    bool isEnabled() {return benabled;};
        
    bool getBodyEndRequested() {return bEndRequested;};        

private:
    virtual void first();
    // executes the behaviour
    virtual void loop();
    
    void checkArtisticSection();        
    //void checkAxesSection();
//    void checkCyclerSection(int i);
    void checkExtraSection();
};
}		
#endif
