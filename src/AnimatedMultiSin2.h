//
//  AnimatedMultiSin2.h
//  LaserLiveTool
//
//  Created by pach on 23/01/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"
#include "AnimatedMultiSinus.h"

class AnimatedMultiSin2 : public AnimatedStuff {
    
public:
    AnimatedMultiSin2();
    ~AnimatedMultiSin2();
    
    void setup(string name);
    void update();
    
private:
    sinWave sin11;
    sinWave sin12;
    sinWave sin13;
    sinWave sin21;
    sinWave sin22;
    sinWave sin23;
    
    int nbPoint;
    float posY;
    
    int nFrame;
    
    float derivativeTime;
    float lastTime;
};