//
//  AnimatedRing.cpp
//  LaserLiveTool
//
//  Created by pach on 02/02/16.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//


#include "AnimatedRing.h"

AnimatedRing::AnimatedRing(){
    
}

AnimatedRing::~AnimatedRing(){
    AnimatedStuff::~AnimatedStuff();
}

void AnimatedRing::setup(string name) {
    AnimatedStuff::setup(name);
    
    type="AnimatedRing";
    
    center = ofVec2f(0.5, 0.5);
    size = 0.;
    rot = 0;
    easeRot = 0.;
    rotDir = 1;
    maxWidth = 1.;
    nbPoint = 25;
    rotSpeed = 0.;
    currentRot = 0.;
    
    time = ofGetElapsedTimef();
    lastTime = ofGetElapsedTimef();
    
    gui->addSlider("/size", 0., 1., &size);
    gui->addSlider("/maxWidth", 0., 1., &maxWidth);
    gui->addIntSlider("/nbPoint", 1, 50, &nbPoint);
    gui->addSlider("/rotSpeed", 0., 10., &rotSpeed);
    gui->addSlider("/spinSpeed", 0., 10., &spinningSpeed);
    gui->add2DPad("/center", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &center);
    
    float quadra = (2*PI) / nbPoint;
    
    ofPolyline p;
    for (int i=0; i<=nbPoint; i++) {
        p.addVertex(center.x+sin(quadra*i+currentRot)*size*rot*maxWidth, center.y+cos(quadra*i+currentRot)*size);
    }
    polylines.push_back(p);
    
    easingType = ofxTween::easeInOut;
    clamp = true;
    
    load();
    
}

void AnimatedRing::update() {
    AnimatedStuff::update();
    
    time = ofGetElapsedTimef()-lastTime;
    lastTime = ofGetElapsedTimef();
    
    currentRot += time*rotSpeed;
    
    rot += time*spinningSpeed*rotDir;
    
    cout<<"time "<<time<<" rot "<<rot<<" dir "<<rotDir<<endl;
    
    if (rot>=1.) {
        rot = 1.;
        rotDir = -1;
    }else if (rot<=-1){
        rot = -1.;
        rotDir = 1;
    }
    
    easeRot = ofxTween::map(rot, -1., 1., -1., 1., clamp, easing, easingType);
    
    polylines.clear();
    float quadra = (2*PI) / nbPoint;
    ofPolyline p;
    for (int i=0; i<=nbPoint; i++) {
        p.addVertex(center.x+sin(quadra*i+currentRot)*size*easeRot*maxWidth, center.y+cos(quadra*i+currentRot)*size);
    }
    polylines.push_back(p);
}

void AnimatedRing::parseOSC(ofxOscMessage &m){
    
    vector<string> osc = getOSCcmd(m.getAddress());
    string cmd = osc[0];
    string msg = osc[1];
    
    if (cmd == "size"){
        size = m.getArgAsFloat(0);
    }
    else if (cmd == "maxWidth"){
        maxWidth = m.getArgAsFloat(0);
    }
    else if (cmd == "nbPoint"){
        nbPoint = m.getArgAsInt32(0);
    }
    else if (cmd == "rotSpeed"){
        rotSpeed = m.getArgAsFloat(0);
    }
    else if (cmd == "spinSpeed"){
        spinningSpeed = m.getArgAsFloat(0);
    }
    else if (cmd == "center"){
        center = ofPoint (m.getArgAsFloat(0), m.getArgAsFloat(1));
    }
}
