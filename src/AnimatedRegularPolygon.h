//
//  AnimatedLosange.h
//  LaserLiveTool
//
//  Created by pach on 22/09/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"


class AnimatedRegularPolygon : public AnimatedStuff{
    
public:
    
    void setup(string name);
    void update();
    void parseOSC(ofxOscMessage &m);

private:
    
    ofPoint center;
    int nbPoint;
    float size;
    float rot;
};