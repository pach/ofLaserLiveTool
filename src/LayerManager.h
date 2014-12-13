//
//  LayerManager.h
//  LaserLiveTool
//
//  Created by pach on 13/12/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "AnimatedStuff.h"

class LayerManager{
    
public:
    LayerManager();
    ~LayerManager();
    
    void setup();
    void update();
    void draw();
    
    void setAnimationList(vector<string> animList);
    
    
    
private:
    AnimatedStuff * currentAnimation;
    
    
};