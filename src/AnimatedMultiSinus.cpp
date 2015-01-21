//
//  AnimatedMultiSinus.cpp
//  LaserAnimTool
//
//  Created by pach on 07/08/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "AnimatedMultiSinus.h"

AnimatedMultiSinus::AnimatedMultiSinus(){
    
}

AnimatedMultiSinus::~AnimatedMultiSinus(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedMultiSinus::setup(string name) {
    AnimatedStuff::setup(name);
    
    type = "AnimatedMultiSinus";
    
    gui->addSpacer();
    gui->addIntSlider("/nbPoint", 10, 1000, &nbPoint);
    gui->addSlider("/posY", -1., 1., &posY);
    gui->addSpacer();
    gui->addSlider("/1/freq", 0., 500., &sin1.freq);
    gui->addSlider("/1/speed", -10., 10., &sin1.speed);
    gui->addSlider("/1/height", 0., 1., &sin1.height);
    gui->addSpacer();
    gui->addSlider("/2/freq", 0., 500., &sin2.freq);
    gui->addSlider("/2/speed", -10., 10., &sin2.speed);
    gui->addSlider("/2/height", 0., 1., &sin2.height);
    gui->addSpacer();
    gui->addSlider("/3/freq", 0., 500., &sin3.freq);
    gui->addSlider("/3/speed", -10., 10., &sin3.speed);
    gui->addSlider("/3/height", 0., 1., &sin3.height);
    ofPolyline p;
    polylines.push_back(p);
    
    load();
    
}


void AnimatedMultiSinus::update() {
    polylines[0].clear();
    
    for (int i=0 ; i<nbPoint ; i++){
        float y1 = sin((float)i/sin1.freq+ofGetElapsedTimef()*sin1.speed)*sin1.height;
        float y2 = sin((float)i/sin2.freq+ofGetElapsedTimef()*sin2.speed)*sin2.height;
        float y3 = sin((float)i/sin3.freq+ofGetElapsedTimef()*sin3.speed)*sin3.height;
        polylines[0].addVertex((float)i/(float)nbPoint, y1+y2+y3-posY);
    }
}

void AnimatedMultiSinus::parseOSC(ofxOscMessage &m){
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
    
    if (cmd == "nbPoint"){
        nbPoint = m.getArgAsInt32(0);
    }
    else if (cmd == "posY"){
        posY = ofMap(m.getArgAsFloat(0), 0., 1., -1., 1.);
    }
    else if (cmd == "1"){
//        ces = msg.find_first_of("/");
//        
//        if (ces != -1) {
//            if (ces == 0){
//                msg = msg.substr(ces+1);
//                cmd = msg;
//                ces = msg.find_first_of("/");
//                if (ces != -1) {
//                    cmd = msg.substr(0, ces);
//                    msg = msg.substr(ces);
//                }
//            }
//            else{
//                cmd = msg.substr(0, ces);
//                msg = msg.substr(ces);
//            }
//        }
        osc = getOSCcmd(msg);
        cmd = osc[0];
        msg = osc[1];
        
        if (cmd == "freq"){
            sin1.freq = ofMap(m.getArgAsFloat(0), 0., 1., 0., 500.);
        }
        else if (cmd == "speed"){
            sin1.speed = ofMap(m.getArgAsFloat(0), 0., 1., 0., 50.);
        }
        else if (cmd == "height"){
            sin1.height = m.getArgAsFloat(0);
        }
    }
    else if (cmd == "2"){
//        ces = msg.find_first_of("/");
//        
//        if (ces != -1) {
//            if (ces == 0){
//                msg = msg.substr(ces+1);
//                cmd = msg;
//                ces = msg.find_first_of("/");
//                if (ces != -1) {
//                    cmd = msg.substr(0, ces);
//                    msg = msg.substr(ces);
//                }
//            }
//            else{
//                cmd = msg.substr(0, ces);
//                msg = msg.substr(ces);
//            }
//        }
        osc = getOSCcmd(msg);
        cmd = osc[0];
        msg = osc[1];
        
        if (cmd == "freq"){
            sin2.freq = ofMap(m.getArgAsFloat(0), 0., 1., 0., 500.);
        }
        else if (cmd == "speed"){
            sin2.speed = ofMap(m.getArgAsFloat(0), 0., 1., 0., 50.);
        }
        else if (cmd == "height"){
            sin2.height = m.getArgAsFloat(0);
        }
    }
    else if (cmd == "3"){
//        ces = msg.find_first_of("/");
//        
//        if (ces != -1) {
//            if (ces == 0){
//                msg = msg.substr(ces+1);
//                cmd = msg;
//                ces = msg.find_first_of("/");
//                if (ces != -1) {
//                    cmd = msg.substr(0, ces);
//                    msg = msg.substr(ces);
//                }
//            }
//            else{
//                cmd = msg.substr(0, ces);
//                msg = msg.substr(ces);
//            }
//        }

        osc = getOSCcmd(msg);
        cmd = osc[0];
        msg = osc[1];
        
        if (cmd == "freq"){
            sin3.freq = ofMap(m.getArgAsFloat(0), 0., 1., 0., 500.);
        }
        else if (cmd == "speed"){
            sin3.speed = ofMap(m.getArgAsFloat(0), 0., 1., 0., 50.);
        }
        else if (cmd == "height"){
            sin3.height = m.getArgAsFloat(0);
        }
    }
//    else if (cmd == "1/freq"){
//        sin1.freq = ofMap(m.getArgAsFloat(0), 0., 1., 0., 500.);
//    }
//    else if (cmd == "1/speed"){
//        sin1.speed = ofMap(m.getArgAsFloat(0), 0., 1., 0., 50.);
//    }
//    else if (cmd == "1/height"){
//        sin1.height = m.getArgAsFloat(0);
//    }
//    else if (cmd == "2/freq"){
//        sin2.freq = ofMap(m.getArgAsFloat(0), 0., 1., 0., 500.);
//    }
//    else if (cmd == "2/speed"){
//        sin2.speed = ofMap(m.getArgAsFloat(0), 0., 1., 0., 50.);
//    }
//    else if (cmd == "2/height"){
//        sin2.height = m.getArgAsFloat(0);
//    }
//    else if (cmd == "3/freq"){
//        sin3.freq = ofMap(m.getArgAsFloat(0), 0., 1., 0., 500.);
//    }
//    else if (cmd == "3/speed"){
//        sin3.speed = ofMap(m.getArgAsFloat(0), 0., 1., 0., 50.);
//    }
//    else if (cmd == "3/height"){
//        sin3.height = m.getArgAsFloat(0);
//    }
}