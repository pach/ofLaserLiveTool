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
    
    sin1.freq = 1.;
    sin1.speed = 0.;
    sin1.height = 1.;
    sin2.freq = 1.;
    sin2.speed = 0.;
    sin2.height = 1.;
    sin3.freq = 1.;
    sin3.speed = 0.;
    sin3.height = 1.;
    sinI1.freq = 1.;
    sinI1.speed = 0.;
    sinI1.height = 1.;
    sinI2.freq = 1.;
    sinI2.speed = 0.;
    sinI2.height = 1.;
    sinI3.freq = 1.;
    sinI3.speed = 0.;
    sinI3.height = 1.;
    
    vertical = false;
    
    gui->addSpacer();
    gui->addIntSlider("/nbPoint", 10, 1000, &nbPoint);
    gui->addSlider("/posY", -1., 1., &posY);
    gui->addToggle("/vertical", &vertical);
    gui->addSpacer();
    gui->addSlider("/1/freq", 0., 200., &sin1.freq);
    gui->addSlider("/1/speed", -10., 10., &sin1.speed);
    gui->addSlider("/1/height", 0., 1., &sin1.height);
    gui->addSpacer();
    gui->addSlider("/2/freq", 0., 200., &sin2.freq);
    gui->addSlider("/2/speed", -10., 10., &sin2.speed);
    gui->addSlider("/2/height", 0., 1., &sin2.height);
    gui->addSpacer();
    gui->addSlider("/3/freq", 0., 200., &sin3.freq);
    gui->addSlider("/3/speed", -10., 10., &sin3.speed);
    gui->addSlider("/3/height", 0., 1., &sin3.height);
    gui->addSpacer();
    gui->addSlider("/tan/1/freq", 0., 50., &sinI1.freq);
    gui->addSlider("/tan/1/speed", -10., 10., &sinI1.speed);
    gui->addSlider("/tan/1/height", 0., 1., &sinI1.height);
    gui->addSpacer();
    gui->addSlider("/tan/2/freq", 0., 50., &sinI2.freq);
    gui->addSlider("/tan/2/speed", -10., 10., &sinI2.speed);
    gui->addSlider("/tan/2/height", 0., 1., &sinI2.height);
    gui->addSpacer();
    gui->addSlider("/tan/3/freq", 0., 50., &sinI3.freq);
    gui->addSlider("/tan/3/speed", -10., 10., &sinI3.speed);
    gui->addSlider("/tan/3/height", 0., 1., &sinI3.height);
    
    ofPolyline p;
    polylines.push_back(p);
    
//    load();
}


void AnimatedMultiSinus::update() {
    AnimatedStuff::update();
    polylines[0].clear();
    float x1, x2, x3, y1, y2, y3;
    for (int i=0 ; i<nbPoint ; i++){
        y1 = sin((float)i*sin1.freq/nbPoint+time*sin1.speed)*sin1.height;
        y2 = sin((float)i*sin2.freq/nbPoint+time*sin2.speed)*sin2.height;
        y3 = sin((float)i*sin3.freq/nbPoint+time*sin3.speed)*sin3.height;
        x1 = sin((float)i*sinI1.freq/nbPoint+time*sinI1.speed)*sinI1.height;
        x2 = sin((float)i*sinI2.freq/nbPoint+time*sinI2.speed)*sinI2.height;
        x3 = sin((float)i*sinI3.freq/nbPoint+time*sinI3.speed)*sinI3.height;
        if (! vertical) {
            polylines[0].addVertex((float)i/(float)nbPoint+x1+x2+x3, y1+y2+y3-posY);
        }else{
            polylines[0].addVertex(y1+y2+y3-posY, (float)i/(float)nbPoint+x1+x2+x3);
        }

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
    
    if (cmd == "multisin1"){
        osc = getOSCcmd(msg);
        string cmd = osc[0];
        string msg = osc[1];
    
        if (cmd == "nbPoint"){
            nbPoint = m.getArgAsInt32(0);
        }
        else if (cmd == "posY"){
            posY = ofMap(m.getArgAsFloat(0), 0., 1., -1., 1.);
        }
        else if (cmd == "1"){
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
        else if (cmd == "tan"){
            osc = getOSCcmd(msg);
            cmd = osc[0];
            msg = osc[1];
            if (cmd == "1"){
                osc = getOSCcmd(msg);
                cmd = osc[0];
                msg = osc[1];
                
                if (cmd == "freq"){
                    sinI1.freq = ofMap(m.getArgAsFloat(0), 0., 1., 0., 500.);
                }
                else if (cmd == "speed"){
                    sinI1.speed = ofMap(m.getArgAsFloat(0), 0., 1., 0., 50.);
                }
                else if (cmd == "height"){
                    sinI1.height = m.getArgAsFloat(0);
                }
            }
            else if (cmd == "2"){
                osc = getOSCcmd(msg);
                cmd = osc[0];
                msg = osc[1];
                
                if (cmd == "freq"){
                    sinI2.freq = ofMap(m.getArgAsFloat(0), 0., 1., 0., 500.);
                }
                else if (cmd == "speed"){
                    sinI2.speed = ofMap(m.getArgAsFloat(0), 0., 1., 0., 50.);
                }
                else if (cmd == "height"){
                    sinI2.height = m.getArgAsFloat(0);
                }
            }
            else if (cmd == "3"){
                
                osc = getOSCcmd(msg);
                cmd = osc[0];
                msg = osc[1];
                
                if (cmd == "freq"){
                    sinI3.freq = ofMap(m.getArgAsFloat(0), 0., 1., 0., 500.);
                }
                else if (cmd == "speed"){
                    sinI3.speed = ofMap(m.getArgAsFloat(0), 0., 1., 0., 50.);
                }
                else if (cmd == "height"){
                    sinI3.height = m.getArgAsFloat(0);
                }
            }
        }
    }
}
