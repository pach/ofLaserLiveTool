//
//  AnimatedPerlinLines.h
//  LaserAnimTool
//
//  Created by pach on 20/09/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"
#include "ofxTween.h"

#define NB_POINTS_SPACING 200

class AnimatedPerlinLines : public AnimatedStuff{
    
public:
    AnimatedPerlinLines();
    ~AnimatedPerlinLines();
    
    void setup(string name);
    void update();
//    void draw();
    
    void parseOSC(ofxOscMessage &m);
    
private:
    float noiseSpeed;
    float noiseSpeedCoeff;
    int nbPoints;
    int nbPointsCoeff;
    float nbVertex;
    int oldNbPoints;
    float noiseTime;
    
    bool lineMode;
    bool oldMode;
    
    bool setFirstShape;
    
    ofPoint scale;
    ofPoint offset;
   
    ofPolyline targetPoint;
    
    ofxEasingQuad easing;
    float clamp;
    ofxTween::ofxEasingType easingType;
};
