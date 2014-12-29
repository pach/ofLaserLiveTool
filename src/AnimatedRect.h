//
//  AnimatedRect.h
//  LaserAnimTool
//
//  Created by pach on 14/09/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"

class AnimatedRect : public AnimatedStuff{
    
public:
    AnimatedRect();
    ~AnimatedRect();
    
    void setup(string name);
    void update();
    
private:
    
    ofPoint center;
    float rot;
    float size;
    
    
    
};