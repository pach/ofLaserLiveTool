//
//  FixedShot.h
//  LaserLiveTool
//
//  Created by pach on 08/05/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxIldaFrame.h"

class FixedShot : public ofxIlda::Frame{
    
public:
    FixedShot();
    
    void setup();
    void update();
    void draw(float x=0, float y=0, float w=0, float h=0);
private:
    
};