#ifndef __ROLY_INTERFACE_BODYCLIENT_H
#define __ROLY_INTERFACE_BODYCLIENT_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "tron2/coms/ChannelClient.h"
#include "tron2/coms/ifaces/TronAnyClient.h"

namespace roly
{
// Body client class to control the body roles node.
class BodyClient : public tron2::TronAnyClient
{    
private:
    static log4cxx::LoggerPtr logger;
    tron2::ChannelClient oExpressiveChannelClient;
    tron2::ChannelClient oArtisticChannelClient1;
    tron2::ChannelClient oArtisticChannelClient2;
    tron2::ChannelClient oExtraChannelClient;
        
public:
    BodyClient();
    ~BodyClient();

    // expressive topic ...
    // express given feeling (feeling id)
    bool expressFeeling(int value);
    // stop expressing feeling
    bool stopExpression();

    // artistic topic ...
    // make given artistic figure (figure id)
    bool makeFigure(int value);
    // set frequency of artistic movement (Hz)
    bool setFigureFreq(float value);
    // set amplitude of artistic movement (degrees)
    bool setFigureAmplitude(float value);
    // set orientation of artistic movement (degrees)
    bool setFigureAngle(float value);
    // set shape factor of artistic movement 
    bool setFigureFactor(float value);
    // stop artistic movement
    bool stopFigure();

    // extra topic ...    
    // full stop of control actions 
    virtual bool fullStop();
    // end control process
    virtual bool endNode();        
};

}
#endif
