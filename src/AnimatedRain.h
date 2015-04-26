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

class AnimatedRain : public AnimatedStuff{
    
public:
    AnimatedRain();
    ~AnimatedRain();
    
    void setup(string name);
    void update();

    void guiEvent(ofxUIEventArgs &e);

    void parseOSC(ofxOscMessage &m);
    
private:
    
    void changeNumDrops(int n);
    void changeRainSpeed(float n);
    void changeRainSpeedVariation(float n);
    void changeRainLength(float n);
    void changeRainLengthVariation(float n);
    
    
    vector<ofVec2f>     vecADrops;
    vector<ofVec2f>     vecZDrops;
    vector<float>       vecDropsSpeed;
    vector<float>       vecDropsLength;
    
    int                 numDrops;
    float               rainSpeed;
    float               rainSpeedVariation;
    float               rainLength;
    float               rainLengthVariation;
    
    int numSimultaneousPoints;
    float freq;
    float duration;
    
    float lastChangeFreqTime;
    float lastChangeDurationTime;
    
    
};