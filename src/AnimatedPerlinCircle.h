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

class AnimatedPerlinCircle : public AnimatedStuff{
    
public:
    AnimatedPerlinCircle();
    ~AnimatedPerlinCircle();
    
    void setup(string name);
    void update();
    
    void parseOSC(ofxOscMessage &m);
    
private:
    
    ofPoint center;
    float size;
    int nbPoints;
    float noiseSpeed;
    float noiseCoeff;
    float noiseDisplace;
    float smooth;
    float rotSpeed;
    
    float timeNoise, timeRot, lastTime;
};