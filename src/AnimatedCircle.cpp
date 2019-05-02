//
//  AnimatedCircle.cpp
//  LaserLiveTool
//
//  Created by pach on 30/12/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "AnimatedCircle.h"

AnimatedCircle::AnimatedCircle(){
    
}

AnimatedCircle::~AnimatedCircle(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedCircle::setup(string name) {
    AnimatedStuff::setup(name);
    
    type = "AnimatedCircle";
    
    nbCircle = 1;
    useNoise = false;
    onePos = ofPoint(0.5, 0.5);
    oneSize = 0.5;
    
    nbPointPerCircle = 20;
    
    noiseTime = 0.;
    rotSpeed = 0.;
    
    gui->addIntSlider("/nbCircle", 1, 10, &nbCircle);
    gui->addIntSlider("/nbPointCircle", 3, 50, &nbPointPerCircle);
    gui->addSlider("/size", 0., 1., &oneSize);
    gui->add2DPad("/pos", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &onePos);
    gui->addToggle("/noise/sw", &useNoise);
    gui->addSlider("noise speed coeff", 0., 0.5, &noiseSpeedCoeff);
    gui->addSlider("/noise/speed", 0., 1., &noiseSpeed);
    gui->addSlider("/rotSpeed", 0., 100., &rotSpeed);
    
//    load();

}

void AnimatedCircle::update() {
    AnimatedStuff::update();
    
    polylines.clear();
    ofPolyline p;
    
    float quadra = (2*PI) / nbPointPerCircle;
    float currentRot = ofGetElapsedTimef()*rotSpeed;
    
    if (!useNoise){
        
        for (int n = 0; n<nbPointPerCircle; n++) {
            p.addVertex(onePos.x+sin(quadra*n+currentRot)*oneSize, onePos.y+cos(quadra*n+currentRot)*oneSize);
        }
        p.addVertex(onePos.x+sin(currentRot)*oneSize, onePos.y+cos(currentRot)*oneSize);
        polylines.push_back(p);
    }
    else{
        noiseTime += noiseSpeedCoeff*noiseSpeed;
        for (int i = 0; i<nbCircle; i++) {
            p.clear();
            
            ofPoint pos = ofPoint (ofNoise(i, 0, noiseTime), ofNoise(i, 1, noiseTime));
            float size = ofNoise(i, 2, noiseTime)*oneSize;
            
            for (int n = 0; n<nbPointPerCircle; n++) {
                p.addVertex(pos.x+sin(quadra*n+currentRot)*size, pos.y+cos(quadra*n+currentRot)*size);
            }
            p.addVertex(pos.x+sin(currentRot)*size, pos.y+cos(currentRot)*size);
            polylines.push_back(p);
        }
    }
}

void AnimatedCircle::parseOSC(ofxOscMessage &m){
    
    vector<string> osc = getOSCcmd(m.getAddress());
    string cmd = osc[0];
    string msg = osc[1];
    
    if (cmd == "circle"){
        osc = getOSCcmd(msg);
        string cmd = osc[0];
        string msg = osc[1];
        
        if (cmd == "nbCircle"){
            nbCircle = m.getArgAsInt32(0);
        }
        else if (cmd == "nbPointCircle"){
            nbPointPerCircle = m.getArgAsInt32(0);
        }
        else if (cmd == "size"){
            oneSize = m.getArgAsFloat(0);
        }
        else if (cmd == "pos"){
            onePos = ofVec2f(m.getArgAsFloat(0.), m.getArgAsFloat(1));
        }
        else if (cmd == "rotSpeed"){
            rotSpeed = m.getArgAsFloat(0);
        }
        else if (cmd == "noise"){
            m.setAddress(msg);
            osc = getOSCcmd(m.getAddress());
            cmd = osc[0];
            msg = osc[1];
            
            if (cmd == "sw"){
                useNoise = m.getArgAsInt32(0);
            }
            else if (cmd == "speed"){
                noiseSpeed = m.getArgAsFloat(0);
            }
        }
    }
}
