//
//  AnimatedRing.h
//  LaserAnimTool
//
//  Created by pach on 02/02/16.
//  Copyright (c) 2015 __IKARI__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"
#include "ofxTween.h"

class AnimatedRing : public AnimatedStuff{
    
public:
    AnimatedRing();
    ~AnimatedRing();
    
    void setup(string name);
    void update();
    
    void parseOSC(ofxOscMessage &m);
    
private:
    ofPoint center;
    float size;
    float maxWidth;
    float rot;
    float easeRot;
    int rotDir;
    int nbPoint;
    float rotSpeed;
    float currentRot;
    float spinningSpeed;
    
    float lastTime;
    float time;
    
    ofxEasingQuad easing;
    float clamp;
    ofxTween::ofxEasingType easingType;
};