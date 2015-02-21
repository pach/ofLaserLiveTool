//
//  Lines.cpp
//  LaserLiveTool
//
//  Created by pach on 29/12/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "AnimatedLines.h"

AnimatedLines::AnimatedLines(){
    
}

AnimatedLines::~AnimatedLines(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedLines::setup(string name) {
    AnimatedStuff::setup(name);
    
    type = "AnimatedLines";
    
    nbLines = 1;
    pos = 0.5;
    dir = 0;
    speed = 0.;
    reinitSpeed = false;
    
    noiseCoeff = 0;
    noiseScale = 100;
    noiseSpeed = 0.5;
    useNoise = false;
    noisePos = 0.;
    noiseNbPoint = 100.;
    
    updateTime = 50;
    
    gui->addSlider("/nbLines", 1, 10, &nbLines);
    gui->addSlider("/pos", 0., 1., &pos);
    gui->addIntSlider("/dir", 0, 2, &dir);
    
    gui->addSlider("/speed", -0.05, 0.05, &speed);
    gui->addToggle("reinit speed", &reinitSpeed);
    
    gui->addToggle("/noise/sw", &useNoise);
    gui->addSlider("/noise/coeff", 0., 0.5, &noiseCoeff);
    gui->addSlider("/noise/speed", 0., 0.5, &noiseSpeed);
    gui->addSlider("/noise/scale", 0., 0.5, &noiseScale);
}

void AnimatedLines::update() {
    if (reinitSpeed == false) {
        speed = 0;
        reinitSpeed = true;
    }
    
    if (ofGetElapsedTimeMillis()-lastTime>updateTime){
        pos += speed;
        noisePos += noiseSpeed;
        
        if (pos > 1.){
            pos = pos - 1.;
        }else if (pos < 1.){
            pos = pos + 1.;
        }
    }
    
    polylines.clear();
    
    ofPolyline p;
    float step = 1./nbLines;
    for (int i=0; i<nbLines; i++) {
        p.clear();
        float lp = pos+i*step;
        while (lp>1.) {
            lp = lp-1.;
        }
        if (!useNoise) {
            if (dir == 0){
                p.addVertex(ofVec2f(0., lp));
                p.addVertex(ofVec2f(1., lp));
            }
            else if (dir == 1){
                p.addVertex(ofVec2f(lp, 0.));
                p.addVertex(ofVec2f(lp, 1.));
            }
            else{
                if (i%2 == 0) {
                    p.addVertex(ofVec2f(0., lp));
                    p.addVertex(ofVec2f(1., lp));
                }else{
                    p.addVertex(ofVec2f(lp, 0.));
                    p.addVertex(ofVec2f(lp, 1.));
                }
            }
        }
        else{
            for (int j=0; j<=noiseNbPoint; j++) {
                if (dir == 0){
                    p.addVertex(ofVec2f(j/noiseNbPoint, lp+(ofNoise(noisePos, j*noiseScale, lp)-0.5)*noiseCoeff));
                }
                else if (dir == 1){
                    p.addVertex(ofVec2f(lp+(ofNoise(noisePos, j*noiseScale, lp)-0.5)*noiseCoeff, j/noiseNbPoint));
                }
                else{
                    if (i%2 == 0) {
                        p.addVertex(ofVec2f(j/noiseNbPoint, lp+(ofNoise(noisePos, j*noiseScale, lp)-0.5)*noiseCoeff));
                    }else{
                        p.addVertex(ofVec2f(lp+(ofNoise(noisePos, j*noiseScale, lp)-0.5)*noiseCoeff, j/noiseNbPoint));
                    }
                }
            }
        }
        polylines.push_back(p);
    }
}

void AnimatedLines::parseOSC(ofxOscMessage &m){
//    string msg = m.getAddress();
//    string cmd ;
//    
//    int ces = msg.find_first_of("/");
//    
//    if (ces != -1) {
//        if (ces == 0){
//            msg = msg.substr(ces+1);
//            cmd = msg;
//            ces = msg.find_first_of("/");
//            if (ces != -1) {
//                cmd = msg.substr(0, ces);
//                msg = msg.substr(ces);
//            }
//        }
//        else{
//            cmd = msg.substr(0, ces);
//            msg = msg.substr(ces);
//        }
//    }

    vector<string> osc = getOSCcmd(m.getAddress());
    string cmd = osc[0];
    string msg = osc[1];
    
    if (cmd == "nbLines"){
        nbLines = m.getArgAsFloat(0);
    }
    else if (cmd == "pos"){
        pos = m.getArgAsFloat(0);
    }
    else if (cmd == "dir"){
        dir = m.getArgAsInt32(0);
    }
    else if (cmd == "speed"){
        speed = ofMap(m.getArgAsFloat(0), 0., 1., -0.05, 0.05);
    }
    else if (cmd == "noise"){
        m.setAddress(msg);
        osc = getOSCcmd(m.getAddress());
        cmd = osc[0];
        msg = osc[1];
        
        if (cmd == "sw"){
            useNoise = m.getArgAsInt32(0);
        }
        else if (cmd == "coeff"){
            noiseCoeff = m.getArgAsFloat(0);
        }
        else if (cmd == "speed"){
            noiseSpeed = m.getArgAsFloat(0);
        }
        else if (cmd == "scale"){
            noiseScale = m.getArgAsFloat(0);
        }
    }
}
