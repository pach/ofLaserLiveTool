//
//  AnimatedSinusRibbon.h
//  LaserLiveTool
//
//  Created by pach on 20/01/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"
#include "AnimatedMultiSinus.h"

//struct sinWave {
//    float freq;
//    float speed;
//    float height;
//};

class AnimatedSinusRibbon : public AnimatedStuff{
    
public:
    AnimatedSinusRibbon();
    ~AnimatedSinusRibbon();
    
    void setup(string name);
    void update();
    
    void parseOSC(ofxOscMessage &m);
    
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
    
    ofVec2f lastPoint;
    
    ofPolyline spleenLine;
    
    sinWave sin1;
    sinWave sin2;
    sinWave sin3;
    
//    sinWave tan1;
};