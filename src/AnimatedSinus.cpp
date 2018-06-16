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
   AnimatedStuff::~AnimatedStuff();
}


void AnimatedSinus::setup(string name) {
    AnimatedStuff::setup(name);
    
    type = "AnimatedSinus";
    
    freq = 10;
    nbPoint = 100;
    speed = 5;
    height = 0.5;
    posY = 0.;
    c = ofFloatColor(1.);
    
    gui->addSpacer();
    gui->addSlider("/freq", 0., 50., &freq);
    gui->addIntSlider("/nbPoint", 10, 1000, &nbPoint);
    gui->addSlider("/speed", 0., 50., &speed);
    gui->addSlider("/height", 0., 1., &height);
    gui->addSlider("/posY", -1., 1., &posY);
    gui->addSpacer();
    gui->addSlider("/red", 0., 1., &c.r);
    gui->addSlider("/green", 0., 1., &c.g);
    gui->addSlider("/blue", 0., 1., &c.b);
    
    ofPolyline p;
    polylines.push_back(p);
    colors.push_back(c);
    
    load();
 
}


void AnimatedSinus::update() {
    AnimatedStuff::update();
    polylines[0].clear();
    
    for (int i=0 ; i<nbPoint ; i++){
        polylines[0].addVertex((float)i/(float)nbPoint, sin((float)i*freq/nbPoint+time)*height-posY);
    }
    
    colors.clear();
    colors.push_back(c);
}

void AnimatedSinus::parseOSC(ofxOscMessage &m){
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
    if (cmd == "sin"){
        osc = getOSCcmd(msg);
        cmd = osc[0];
        msg = osc[1];
        
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
}
