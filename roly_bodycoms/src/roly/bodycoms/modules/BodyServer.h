#ifndef __ROLY_BODYCOMS_BODYSERVER2_H
#define __ROLY_BODYCOMS_BODYSERVER2_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/bodycore/BodyBus.h"
#include "roly/bodycore/ArtisticBus.h"
#include "roly/interface2/control/ArtisticServer.h"
#include "tron/control/module3.h"
#include "tron/interface/ExtraServer.h"

namespace roly
{
// This module serves external control requests for body control. 
// It uses an ignition based server for each body node's section.
class BodyServer : public tron::Module3
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // bus connections
    ArtisticBus* pArtisticBus1;
    ArtisticBus* pArtisticBus2;
    // section servers
    ArtisticServer oArtisticServer1;
    ArtisticServer oArtisticServer2;
    tron::ExtraServer oExtraServer;      
    bool bEndRequested;         // end of roly process requested

public:
    BodyServer();
    //~BodyServer2();

    void init(BodyBus& oBodyBus);       
    bool isEnabled() {return benabled;};
        
    bool getBodyEndRequested() {return bEndRequested;};        

private:
    virtual void first();
    // executes the behaviour
    virtual void loop();
    
    void checkArtisticSection1();        
    void checkArtisticSection2();        
    void checkExtraSection();
};
}		
#endif
