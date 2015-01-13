//
//  AnimatedSvg.h
//  LaserAnimTool
//
//  Created by pach on 14/09/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"
#include "SvgLoader.h"

class AnimatedSvg : public AnimatedStuff{
    
public:
    AnimatedSvg();
    ~AnimatedSvg();
    
    void setup (string name);
    void update ();
    
    void textInputEvent(ofxUIEventArgs &e);
    
private:

    ofPoint pos;
    float rot;
    float size;
    
    string filename;
    bool hasLoaded;
    
    SvgLoader svg;
    
};