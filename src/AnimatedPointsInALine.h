//
//  AnimatedSinus.h
//  LaserAnimTool
//
//  Created by pach on 07/08/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"

class AnimatedPointsInALine : public AnimatedStuff{
    
public:
    AnimatedPointsInALine();
    ~AnimatedPointsInALine();
    
    void setup(string name);
    void update();
    
    void parseOSC(ofxOscMessage &m);
    
private:
    int numSimultaneousPoints;
    float freq;
    float duration;
    
    float lastChangeFreqTime;
    float lastChangeDurationTime;
    
    
};