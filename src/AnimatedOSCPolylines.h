//
//  AnimatedOSCPolylines.h
//  LaserLiveTool
//
//  Created by pach on 27/01/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "AnimatedStuff.h"

class AnimatedOSCPolylines : public AnimatedStuff {
    
public:
    AnimatedOSCPolylines();
    ~AnimatedOSCPolylines();
    
    void setup(string name);
    void update();
    
    void parseOSC(ofxOscMessage &m);
    
private:
    
};