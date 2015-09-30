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
    innerSize = 0.1;
    resetSpeed = false;
    
    gui->addSlider("/nbPoint", 10, 500, &nbPoint);
    gui->addSlider("/maxSize", 0., 1., &maxSize);
    gui->addSlider("/spiralCoeff", 0., 2., &spiralCoeff);
    gui->addSlider("/innerSize", 0., 1., &innerSize);
    gui->addSlider("/rotSpeed", -50., 50., &rotSpeed);
    gui->addToggle("resetSpeed", &resetSpeed);
    gui->add2DPad("/center", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &center);
    
    gui->addSpacer();
    gui->addToggle("/log/sw", &isLogSpiral);
    gui->addSlider("/log/coeff", 0.95, 1.5, &logCoeff);
    
    load();
    
}

void AnimatedSpiral::update() {
    if (resetSpeed) {
        rotSpeed = 0;
        resetSpeed = false;
    }
    
    polylines.clear();
    ofPolyline p;
    
    float quadra = (2*PI) / (nbPoint*spiralCoeff);
    currentRot += (ofGetElapsedTimef()-lastTime)*rotSpeed;
    lastTime = ofGetElapsedTimef();
    float size;
    ofPoint pt;
    
    for (int n = 0; n<nbPoint; n++) {
        if(!isLogSpiral){
            size = ofMap(n, 0, nbPoint, innerSize/2., maxSize/2.);
            p.addVertex(center.x+sin(quadra*n+currentRot)*size, center.y+cos(quadra*n+currentRot)*size);
        }
        else{
            size = ofMap(n, 0, nbPoint, 0, maxSize/(2.*pow(logCoeff, quadra*nbPoint)));
            pt = ofPoint(center.x+sin(quadra*n+currentRot)*size*pow(logCoeff, quadra*n), center.y+cos(quadra*n+currentRot)*size*pow(logCoeff, quadra*n));
            if (center.distance(pt)>innerSize) {
                p.addVertex(pt);
            }
        }
    }
    
    polylines.push_back(p);
}

void AnimatedSpiral::parseOSC(ofxOscMessage &m){
    
    vector<string> osc = getOSCcmd(m.getAddress());
    string cmd = osc[0];
    string msg = osc[1];
    
    if (cmd == "nbPoint"){
        nbPoint = m.getArgAsInt32(0);
    }
    else if (cmd == "maxSize"){
        maxSize = m.getArgAsFloat(0);
    }
    else if (cmd == "spiralCoeff"){
        spiralCoeff = m.getArgAsFloat(0);
    }
    else if (cmd == "center"){
        center = ofVec2f(m.getArgAsFloat(0.), m.getArgAsFloat(1));
    }
    else if (cmd == "innerSize"){
        innerSize = m.getArgAsFloat(0);
    }
    else if (cmd == "rotSpeed"){
        rotSpeed = m.getArgAsFloat(0);
    }
    else if (cmd == "log"){
        m.setAddress(msg);
        osc = getOSCcmd(m.getAddress());
        cmd = osc[0];
        msg = osc[1];
        
        if (cmd == "sw"){
            isLogSpiral = m.getArgAsInt32(0);
        }
        else if (cmd == "coeff"){
            logCoeff = m.getArgAsFloat(0);
        }
    }
}

