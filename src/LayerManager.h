//
//  LayerManager.h
//  LaserLiveTool
//
//  Created by pach on 26/12/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimManager.h"
#include "ofxUI.h"

class LayerManager{
    
public:
    LayerManager();
    ~LayerManager();
    
    void setup(vector<string> anims);
    void update();
    void draw();
    
private:
    
    AnimatedStuff *curAnim;
    
    vector<string> animList;
    
    ofxUISuperCanvas *gui;
    
    int idLayer;
};