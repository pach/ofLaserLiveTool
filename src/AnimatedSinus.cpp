//
//  AnimatedSinus.cpp
//  LaserAnimTool
//
//  Created by pach on 07/08/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "AnimatedSinus.h"

AnimatedSinus::AnimatedSinus(){
    
}

AnimatedSinus::~AnimatedSinus(){
    
}


void AnimatedSinus::setup(string name) {
    AnimatedStuff::setup(name);
    
    type = "AnimatedSinus";
    
    freq = 10;
    nbPoint = 100;
    speed = 5;
    height = 0.5;
    posY = 0.;
    
    gui->addSpacer();
    gui->addSlider("freq", 0., 500., &freq);
    gui->addIntSlider("nbPoint", 10, 1000, &nbPoint);
    gui->addSlider("speed", 0., 50., &speed);
    gui->addSlider("height", 0., 1., &height);
    gui->addSlider("posY", -1., 1., &posY);
    
    ofPolyline p;
    polylines.push_back(p);
    
    load();
 
}


void AnimatedSinus::update() {
    polylines[0].clear();
    
    for (int i=0 ; i<nbPoint ; i++){
        polylines[0].addVertex((float)i/(float)nbPoint, sin((float)i/freq+ofGetElapsedTimef()*speed)*height-posY);
    }
}
