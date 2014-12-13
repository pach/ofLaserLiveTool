//
//  AnimatedMultiline.h
//  LaserAnimTool
//
//  Created by pach on 14/09/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"

class AnimatedMultiline : public AnimatedStuff{
    
public:
    AnimatedMultiline();
    ~AnimatedMultiline();
    void setup(string name);
    void update();
    void draw();
    
    void guiEvent(ofxUIEventArgs &e);
    
    void load();
    void save();
    
    void addPoint(ofPoint pos);
    void updatePoint(unsigned int i, ofPoint pos);
    int getClosestPointId (ofPoint pos);
    void removePoint (int idPoint);
    
    void mousePressed(ofMouseEventArgs& e);
    void mouseDragged(ofMouseEventArgs& e);
    void mouseReleased(ofMouseEventArgs& e);
    
    void setActivePoint (int idPoint);
    
private:
    float pickingDistance;
    int timeKeyPickDistance;
    
    bool pointIsPicked;
    int pointPickedId;
    
    ofPolyline points;
};