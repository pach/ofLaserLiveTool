//
//  AnimatedWalls.h
//  LaserLiveTool
//
//  Created by pach on 11/02/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"
#include "ofxOsc.h"


class AnimatedWalls : public AnimatedStuff{
    
public:
    AnimatedWalls();
    ~AnimatedWalls();
    
    void setup(string name);
    void update();
    
    void parseOSC(ofxOscMessage &m);
    
private:
    bool isOrigin;
    float posX1;
    float posX2;
    ofVec2f posY1;
    ofVec2f posY2;
    
};