//
//  AnimatedRect.cpp
//  LaserAnimTool
//
//  Created by pach on 14/09/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "AnimatedRect.h"

AnimatedRect::AnimatedRect(){
    
}

AnimatedRect::~AnimatedRect(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedRect::setup(string name) {
    AnimatedStuff::setup(name);
    center = ofVec2f (0.5f, 0.5f);
    rot = 0.0f;
    size = 0.0f;
    
    type = "AnimatedRect";
    gui->add2DPad("/center", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &center);
    gui->addSlider("/rot", 0., 360., &rot);
    gui->addSlider("/size", 0., 1., &size);

//    timeline.addCurves(name+".x");
//    timeline.addCurves(name+".y");
//    timeline.addCurves(name+".rot");
//    timeline.addCurves(name+".size");
//    
    ofPolyline p ;
    p.addVertex(center+ofVec2f(-size/2., -size/2.));
    p.addVertex(center+ofVec2f(size/2., -size/2.));
    polylines.push_back(p);
    p.clear();
    p.addVertex(center+ofVec2f(size/2., -size/2.));
    p.addVertex(center+ofVec2f(size/2., size/2.));
    polylines.push_back(p);
    p.clear();
    p.addVertex(center+ofVec2f(size/2., size/2.));
    p.addVertex(center+ofVec2f(-size/2., size/2.));
    polylines.push_back(p);
    p.clear();
    p.addVertex(center+ofVec2f(-size/2., size/2.));
    p.addVertex(center+ofVec2f(-size/2., -size/2.));
    polylines.push_back(p);
    
//    load();
}

void AnimatedRect::update() {
    AnimatedStuff::update();
    
//    center.x = timeline.getValue(name+".x");
//    center.y = timeline.getValue(name+".y");
//    rot = timeline.getValue(name+".rot");
//    rot = rot * 360.0;
//    size = timeline.getValue(name+".size");
    
    ofPolyline p ;
    polylines.clear();
    p.addVertex(center+ofVec2f(-size/2., -size/2.).rotate(rot));
    p.addVertex(center+ofVec2f(size/2., -size/2.).rotate(rot));
    polylines.push_back(p);
    p.clear();
    p.addVertex(center+ofVec2f(size/2., -size/2.).rotate(rot));
    p.addVertex(center+ofVec2f(size/2., size/2.).rotate(rot));
    polylines.push_back(p);
    p.clear();
    p.addVertex(center+ofVec2f(size/2., size/2.).rotate(rot));
    p.addVertex(center+ofVec2f(-size/2., size/2.).rotate(rot));
    polylines.push_back(p);
    p.clear();
    p.addVertex(center+ofVec2f(-size/2., size/2.).rotate(rot));
    p.addVertex(center+ofVec2f(-size/2., -size/2.).rotate(rot));
    polylines.push_back(p);
    
}

void AnimatedRect::parseOSC(ofxOscMessage &m){
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
    if (cmd == "rect"){
        osc = getOSCcmd(msg);
        string cmd = osc[0];
        string msg = osc[1];
        
        if (cmd == "center"){
            center = ofPoint(m.getArgAsFloat(0), m.getArgAsFloat(1));
        }
        else if (cmd == "rot"){
            rot = ofMap(m.getArgAsFloat(0), 0, 1, 0, 360);
        }
        else if (cmd == "size"){
            size = m.getArgAsFloat(0);
        }
    }
}
