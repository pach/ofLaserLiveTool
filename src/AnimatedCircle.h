//
//  AnimatedCircle.h
//  LaserLiveTool
//
//  Created by pach on 30/12/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"

class AnimatedCircle : public AnimatedStuff{
    
public:
    AnimatedCircle();
    ~AnimatedCircle();
    
    void setup(string name);
    void update();
    
private:
//    vector<ofPoint> pos;
//    vector<float> size;
    
    ofPoint onePos;
    float oneSize;
    
    bool useNoise;
    
    int nbCircle;
    
    int nbPointPerCircle;
    
    float noiseSpeedCoeff;
    float noiseSpeed;
    
    float noiseTime;
};