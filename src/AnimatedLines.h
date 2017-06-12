//
//  Lines.h
//  LaserLiveTool
//
//  Created by pach on 29/12/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"

class AnimatedLines : public AnimatedStuff{
    
public:
    AnimatedLines();
    ~AnimatedLines();
    
    void setup(string name);
    void update();
    
    void parseOSC(ofxOscMessage &m);
    
private:
    
    float nbLines;
    float pos;
    int dir;
    
    float rot;
    
    float speed;
    
    long lastTime;
    int updateTime;
    
    bool reinitSpeed;
    
    bool useNoise;
    float noiseCoeff;
    float noiseSpeed;
    float noiseScale;
    
    float noisePos;
    float noiseNbPoint;
};
