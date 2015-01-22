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
    gui->addToggle("/useNoise", &useNoise);
    gui->addSlider("noise speed coeff", 0., 0.5, &noiseSpeedCoeff);
    gui->addSlider("/noiseSpeed", 0., 1., &noiseSpeed);
    gui->addSlider("/rotSpeed", 0., 100., &rotSpeed);
    
    load();

}

void AnimatedCircle::update() {
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
