//
//  Lines.h
//  LaserLiveTool
//
//  Created by pach on 29/12/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"

class AnimatedLines : public AnimatedStuff{
    
public:
    AnimatedLines();
    ~AnimatedLines();
    
    void setup(string name);
    void update();
    void draw();
    
private:
    
    float nbLines;
    float pos;
    int dir;
    
    float speed;
    
    long lastTime;
    int updateTime;
    
    bool reinitSpeed;
};