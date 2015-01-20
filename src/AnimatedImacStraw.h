//
//  AnimatedImacStraw.h
//  LaserLiveTool
//
//  Created by pach on 14/01/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"

class AnimatedImacStraw : public AnimatedStuff{
    
public:
    AnimatedImacStraw();
    ~AnimatedImacStraw();
    
    void setup(string name);
    void update();
    
    void save();
    void load();
    
private:
    int nbStraw;
    vector<ofPoint> strawPos;
    vector<float> size;
    vector<bool> active;
    float rot;

    int idUpdateStraw;
    ofPoint updatePos;
    float updateSize;
    
    int animationMode;
    float animationSpeed;
    float lastStepTime;
    
    int idOn;
    
    float horizontalDisplace;
    float displacePos;
};