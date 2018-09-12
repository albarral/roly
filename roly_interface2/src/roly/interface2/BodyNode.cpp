/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/interface2/BodyNode.h"
#include "tron/topics/NodeSection.h"
#include "tron/topics/RobotNodes.h"
#include "tron/topics/channels/ExtraSection.h"

namespace roly
{    

BodyNode2::BodyNode2() : tron::Node(tron::RobotNodes::eNODE_ARM)
{
    oSectionsMap.addCode(eSECTION_EXPRESSIVE, SECTION_EXPRESSIVE);
    oSectionsMap.addCode(eSECTION_ARTISTIC1, SECTION_ARTISTIC1);
    oSectionsMap.addCode(eSECTION_ARTISTIC2, SECTION_ARTISTIC2);
    oSectionsMap.addCode(eSECTION_EXTRA, tron::ExtraSection::EXTRA_SECTION);
    
    setExpressiveSection();
    setArtisticSection(eSECTION_ARTISTIC1);
    setArtisticSection(eSECTION_ARTISTIC2);

    tron::ExtraSection oExtraSection(eSECTION_EXTRA);
    listNodeSections.push_back(oExtraSection);    
}

void BodyNode2::setExpressiveSection()
{
    tron::NodeSection oExpressiveSection(eSECTION_EXPRESSIVE);
    
    oExpressiveSection.addChannel(eEXPRESS_FEELING, EXPRESS_FEELING);
    oExpressiveSection.addChannel(eEXPRESS_HALT, EXPRESS_HALT);                         
    
    listNodeSections.push_back(oExpressiveSection);    
}

void BodyNode2::setArtisticSection(int section)
{
    tron::NodeSection oArtisticSection(section);
    
    oArtisticSection.addChannel(eARTISTIC_FIGURE, ARTISTIC_FIGURE);
    oArtisticSection.addChannel(eARTISTIC_FREQ, ARTISTIC_FREQ);                         
    oArtisticSection.addChannel(eARTISTIC_SIZE, ARTISTIC_SIZE);                      
    oArtisticSection.addChannel(eARTISTIC_ORIENTATION, ARTISTIC_ORIENTATION);                   
    oArtisticSection.addChannel(eARTISTIC_RELFACTOR, ARTISTIC_RELFACTOR);
    oArtisticSection.addChannel(eARTISTIC_HALT, ARTISTIC_HALT);                         
    
    listNodeSections.push_back(oArtisticSection);            
}

std::string BodyNode2::toString()
{
    return "ArmNode\n" + tron::Node::toString();
}
}