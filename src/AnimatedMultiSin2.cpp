//
//  AnimatedMultiSin2.cpp
//  LaserLiveTool
//
//  Created by pach on 23/01/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//


#include "AnimatedMultiSin2.h"

AnimatedMultiSin2::AnimatedMultiSin2(){
    
}

AnimatedMultiSin2::~AnimatedMultiSin2(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedMultiSin2::setup(string name) {
    AnimatedStuff::setup(name);
    
    type = "AnimatedMultiSinus2";
    
    nbPoint = 100;
    posY = 0.5;
    sin11.freq = 0.;
    sin11.speed = 0.;
    sin11.height = 0.;
    sin12.freq = 0.;
    sin12.speed = 0.;
    sin12.height = 0.;
    sin13.freq = 0.;
    sin13.speed = 0.;
    sin13.height = 0.;
    sin21.freq = 0.;
    sin21.speed = 0.;
    sin21.height = 0.;
    sin22.freq = 0.;
    sin22.speed = 0.;
    sin22.height = 0.;
    sin23.freq = 0.;
    sin23.speed = 0.;
    sin23.height = 0.;
    
    gui->addSpacer();
    gui->addIntSlider("/nbPoint", 10, 1000, &nbPoint);
    gui->addSlider("/posY", -1., 1., &posY);
    gui->addSpacer();
    gui->addSlider("/1/1/freq", 0., 100., &sin11.freq);
    gui->addSlider("/1/1/speed", -10., 10., &sin11.speed);
    gui->addSlider("/1/1/height", 0., 1., &sin11.height);
    gui->addSlider("/1/2/freq", 0., 100., &sin12.freq);
    gui->addSlider("/1/2/speed", -10., 10., &sin12.speed);
    gui->addSlider("/1/2/height", 0., 1., &sin12.height);
    gui->addSlider("/1/3/freq", 0., 100., &sin13.freq);
    gui->addSlider("/1/3/speed", -10., 10., &sin13.speed);
    gui->addSlider("/1/3/height", 0., 1., &sin13.height);
    gui->addSpacer();
    gui->addSlider("/2/1/freq", 0., 100., &sin21.freq);
    gui->addSlider("/2/1/speed", -10., 10., &sin21.speed);
    gui->addSlider("/2/1/height", 0., 1., &sin21.height);
    gui->addSlider("/2/2/freq", 0., 100., &sin22.freq);
    gui->addSlider("/2/2/speed", -10., 10., &sin22.speed);
    gui->addSlider("/2/2/height", 0., 1., &sin22.height);
    gui->addSlider("/2/3/freq", 0., 100., &sin23.freq);
    gui->addSlider("/2/3/speed", -10., 10., &sin23.speed);
    gui->addSlider("/2/3/height", 0., 1., &sin23.height);

    ofPolyline p;
    p.addVertex(0.5, 0.5);
    p.addVertex(0.5, 0.5);
    polylines.push_back(p);
    polylines.push_back(p);
    nFrame = 0;
    
    load();
}

void AnimatedMultiSin2::update() {
    polylines[0].clear();
    polylines[1].clear();
    
//    float y;
//    if (nFrame == 0){
//        for (int i=0 ; i<nbPoint ; i++){
//            y = sin((float)i/sin1.freq+ofGetElapsedTimef()*sin1.speed)*sin1.height;
//            polylines[0].addVertex((float)i/(float)nbPoint, y-posY);
//        }
//        nFrame = 1;
//    }
//    else{
//        for (int i=0 ; i<nbPoint ; i++){
//            y = sin((float)i/sin2.freq+ofGetElapsedTimef()*sin2.speed)*sin2.height;
//            polylines[0].addVertex((float)i/(float)nbPoint, y-posY);
//        }
//        nFrame = 0;
//    }
    float y1, y2, y3;
    for (int i=0 ; i<nbPoint ; i++){
        y1 = sin((float)i*sin11.freq/nbPoint+time*sin11.speed)*sin11.height;
        y2 = sin((float)i*sin12.freq/nbPoint+time*sin12.speed)*sin12.height;
        y3 = sin((float)i*sin13.freq/nbPoint+time*sin13.speed)*sin13.height;
        polylines[0].addVertex((float)i/(float)nbPoint, (y1+y2+y3)-posY);
        y1 = sin((float)i*sin21.freq/nbPoint+time*sin21.speed)*sin21.height;
        y2 = sin((float)i*sin22.freq/nbPoint+time*sin22.speed)*sin22.height;
        y3 = sin((float)i*sin23.freq/nbPoint+time*sin23.speed)*sin23.height;
        polylines[1].addVertex((float)i/(float)nbPoint, (y1+y2+y3)-posY);
    }
    
}
