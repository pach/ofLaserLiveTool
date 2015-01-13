//
//  AnimatedMultiSinus.h
//  LaserLiveTool
//
//  Created by pach on 31/12/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"

struct sinWave {
    float freq;
    float speed;
    float height;
};

class AnimatedMultiSinus: public AnimatedStuff{
    
public:
    AnimatedMultiSinus();
    ~AnimatedMultiSinus();
    
    void setup(string name);
    void update();
    
    void parseOSC(ofxOscMessage &m);
    
private:
    sinWave sin1;
    sinWave sin2;
    sinWave sin3;
    
    int nbPoint;
    float posY;
    
};