//
//  AnimatedRibbon.h
//  LaserAnimTool
//
//  Created by pach on 20/09/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"

class AnimatedRibbon : public AnimatedStuff{
    
public:
    AnimatedRibbon();
    ~AnimatedRibbon();
    
    void setup(string name);
    void update();
    
    void addPointAtCurrentTime(float x, float y);
    
private:
    
    int nbMaxVertex;
    float noiseCoeff;
    float smoothCoeff;
    float noiseSpeed;
    float moveSpeed;
    bool useNoise;
    float windCoeff;
    float windNoiseDisplace;
    
    float windX;
    float windY;
    
    bool isRecording;
    
    float timeKeyPickDistance;
    
    ofVec2f lastPoint;
};