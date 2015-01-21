//
//  AnimatedSpiral.h
//  LaserLiveTool
//
//  Created by pach on 21/01/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"

class AnimatedSpiral : public AnimatedStuff{
    
public:
    AnimatedSpiral();
    ~AnimatedSpiral();
    
    void setup(string name);
    void update();
    
private:
    ofPoint center;
    float nbPoint;
    float maxSize;
    float spiralCoeff;
    
    float lastTime;
    
    float rotSpeed;
    float currentRot;
};