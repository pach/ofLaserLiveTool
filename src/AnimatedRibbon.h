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
    
    void parseOSC(ofxOscMessage &m);
    
//    void addPointAtCurrentTime(float x, float y);
    
private:
    
    int nbMaxVertex;
    float nbVertex;
    float noiseCoeff;
    float smoothCoeff;
    float smooth;
    float noiseSpeed;
    float moveSpeed;
    bool useNoise;
    float windCoeff;
    float windNoiseDisplace;
    
    float windX;
    float windY;

    ofPoint wind;
    ofPoint curPos;
    
    bool isRecording;
    
    float timeKeyPickDistance;
    
    ofVec2f lastPoint;
};