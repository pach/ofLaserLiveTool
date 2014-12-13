//
//  MovingPoint.h
//  LaserAnimTool
//
//  Created by pach on 30/05/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"


class MovingPoint{
    
public:
    MovingPoint();
    ~MovingPoint();
    
    void setup();
    void update();
    void draw();
    
    
    
private:
    ofxTLCurves xMove;
    ofxTLCurves yMove;
    
};