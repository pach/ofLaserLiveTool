//
//  AnimatedSpiral.cpp
//  LaserLiveTool
//
//  Created by pach on 21/01/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//


#include "AnimatedSpiral.h"

AnimatedSpiral::AnimatedSpiral(){
 
}

AnimatedSpiral::~AnimatedSpiral(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedSpiral::setup(string name) {
    AnimatedStuff::setup(name);
    
    type = "AnimatedSpiral";
    
    nbPoint = 200;
    center = ofVec2f(0.5, 0.5);
    maxSize = 1.;
    spiralCoeff = 2.;
    rotSpeed = 0.;
    lastTime = 0.;
    currentRot = 0.;
    
    gui->addSlider("nbPoint", 10, 500, &nbPoint);
    gui->addSlider("maxSize", 0., 1., &maxSize);
    gui->addSlider("spiralCoeff", 0., 2., &spiralCoeff);
    gui->addSlider("rotSpeed", -10., 10., &rotSpeed);
    gui->add2DPad("center", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &center);
}

void AnimatedSpiral::update() {
    polylines.clear();
    ofPolyline p;
    
    float quadra = (2*PI) / (nbPoint*spiralCoeff);
    currentRot += (ofGetElapsedTimef()-lastTime)*rotSpeed;
    lastTime = ofGetElapsedTimef();
    
    for (int n = 0; n<nbPoint; n++) {
        p.addVertex(center.x+sin(quadra*n+currentRot)*(maxSize/2.)*((float)n/(float)nbPoint), center.y+cos(quadra*n+currentRot)*(maxSize/2.)*((float)n/(float)nbPoint));
    }
    
    polylines.push_back(p);
}
