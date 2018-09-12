#ifndef __ROLY_INTERFACE2_BODYNODE_H
#define __ROLY_INTERFACE2_BODYNODE_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron/topics/Node.h"

namespace roly
{
// Definition of body node sections and channels
 class BodyNode2 : public tron::Node
{
public:
    /*! body sections */
    enum eBodySections
    {
        eSECTION_EXPRESSIVE,       /*! expressive section */
        eSECTION_ARTISTIC1,          /*! artistic 1 section  */
        eSECTION_ARTISTIC2,          /*! artistic 2 section  */
        eSECTION_EXTRA,             /*! extra section  */
        eSECTION_DIM
    };     

    /*! expressive section channels */
    enum eJointsChannels
    {
        eEXPRESS_FEELING,                   /*! express given feeling */
        eEXPRESS_HALT,                        /*! halt expressive action */
        eEXPRESS_DIM
    };
    
    /*! artistic section channels  */
    enum eCyclerChannels
    {
        eARTISTIC_FIGURE,        // id of artistic figure to implement
        eARTISTIC_FREQ,       // frequency of cyclic figure (Hz) 
        eARTISTIC_SIZE,        // size of cyclic figure (degrees)
        eARTISTIC_ORIENTATION,  // orientation of cyclic figure (degrees)
        eARTISTIC_RELFACTOR,    // relative xy factor of cyclic figure 
        eARTISTIC_HALT,                // halt ongoing artistic movement
        eARTISTIC_DIM
    };
    
 private:
    /*! names of arm sections */
    const std::string SECTION_EXPRESSIVE = "express";
    const std::string SECTION_ARTISTIC1 = "art1";
    const std::string SECTION_ARTISTIC2 = "art2";
    
    /*! names of expressive section channels */
    const std::string EXPRESS_FEELING = "feel";      /*! set feeling to express (integer) */
    const std::string EXPRESS_HALT = "halt";          /*! halt expression */
    
    /*! names of artistic section channels */
    const std::string ARTISTIC_FIGURE = "figure";             /*! id of artistic figure to implement (integer) */
    const std::string ARTISTIC_FREQ = "freq";                  /*! frequency of cyclic figure (Hz) */
    const std::string ARTISTIC_SIZE = "size";                   /*! size of cyclic figure (degrees) */
    const std::string ARTISTIC_ORIENTATION = "angle";     /*! orientation of cyclic figure (degrees) */
    const std::string ARTISTIC_RELFACTOR = "factor";       /*! relative xy factor of cyclic figure */
    const std::string ARTISTIC_HALT = "halt";                   /*! halt ongoing artistic movement */
     
    void setExpressiveSection();
    void setArtisticSection(int section);
    
 public:     
   BodyNode2();
    
    // return node description
    virtual std::string toString() override;             
};
}
#endif
