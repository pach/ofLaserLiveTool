//
//  AnimatedLosange.h
//  LaserLiveTool
//
//  Created by pach on 22/09/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"

#include "ofxTween.h"

#define NB_POINTS 700


class AnimatedSolid : public AnimatedStuff{
    
public:
    
    void setup(string name);
    void update();
    void parseOSC(ofxOscMessage &m);
    
private:
    
    ofxEasingQuad easing;
    float clamp;
    ofxTween::ofxEasingType easingType;
    
    ofPoint center;
    int nbPoint;
    float size1;
    float size2;
    float rot1;
    float rot2;
    float perlinCoeff;
    float perlinSpeed;
    
    double time;
    double lastTime;
    
    ofPolyline targetPoint;
};
