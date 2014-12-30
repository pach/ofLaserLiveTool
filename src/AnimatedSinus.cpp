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

void AnimatedSinus::parseOSC(ofxOscMessage &m){
    string msg = m.getAddress();
    string cmd ;
    
    int ces = msg.find_first_of("/");
    
    if (ces != -1) {
        if (ces == 0){
            msg = msg.substr(ces+1);
            ces = msg.find_first_of("/");
        }
        if (ces == -1){
            cmd = msg;
        }
        else{
            cmd = msg.substr(0, ces);
            msg = msg.substr(ces);
        }
    }
    
    if (cmd == "freq"){
        freq = ofMap(m.getArgAsFloat(0), 0., 1., 0., 500.);
    }
    else if (cmd == "nbPoint"){
        nbPoint = m.getArgAsInt32(0);
    }
    else if (cmd == "speed"){
        speed = ofMap(m.getArgAsFloat(0), 0., 1., 0., 50.);
    }
    else if (cmd == "height"){
        height = m.getArgAsFloat(0);
    }
    else if (cmd == "posY"){
        posY = ofMap(m.getArgAsFloat(0), 0., 1., -1., 1.);
    }
}