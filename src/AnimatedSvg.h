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
#include "ofxSvg.h"

class AnimatedSvg : public AnimatedStuff{
    
public:
    AnimatedSvg();
    ~AnimatedSvg();
    
    void loadSvg(string filename);
    
    void setup (string name);
    void update ();
    
private:
    
    ofxSVG svg;
    ofPath svgPath;
    
    ofVec2f pos;
    float rot;
    float size;
    
};