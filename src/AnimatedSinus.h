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

class AnimatedSinus : public AnimatedStuff{
    
public:
    AnimatedSinus();
    ~AnimatedSinus();
    
    void setup(string name);
    void update();
    
private:
    float freq;
    int nbPoint;
    float speed;
    float height;
    float posY;
    
};