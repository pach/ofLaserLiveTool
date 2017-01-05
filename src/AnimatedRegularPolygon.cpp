//
//  AnimatedRegularPolygon.cpp
//  LaserLiveTool
//
//  Created by pach on 22/09/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//


#include "AnimatedRegularPolygon.h"

void AnimatedRegularPolygon::setup(string name) {
    AnimatedStuff::setup(name);
    center = ofVec2f(0., 0.);
    size = 0.;
    nbPoint = 6;
    rot = 0;
    
    gui->addSlider("/size", 0., 1., &size);
    gui->addIntSlider("/nbPoint", 3, 10, &nbPoint);
    gui->addSlider("/rot", 0., 2*PI, &rot);
    gui->add2DPad("/center", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &center);
    
    type="AnimatedRegularPolygon";
    
    float quadra = (2*PI) / nbPoint;
   
    
    for (int i=0; i<nbPoint; i++) {
        ofPolyline p;
        p.addVertex(center.x+sin(quadra*i+rot)*size, center.y+cos(quadra*i+rot)*size);
        p.addVertex(center.x+sin(quadra*(i+1)+rot)*size, center.y+cos(quadra*(i+1)+rot)*size);
        polylines.push_back(p);
    }
    
    load();
    
}

void AnimatedRegularPolygon::update() {
    polylines.clear();
    float quadra = (2*PI) / nbPoint; 
    for (int i=0; i<nbPoint; i++) {
        ofPolyline p;
        p.addVertex(center.x+sin(quadra*i+rot)*size, center.y+cos(quadra*i+rot)*size);
        p.addVertex(center.x+sin(quadra*(i+1)+rot)*size, center.y+cos(quadra*(i+1)+rot)*size);
        polylines.push_back(p);
        
        cout<<"add "<<p[0]<<" "<<p[1]<< endl;
    }
}

void AnimatedRegularPolygon::parseOSC(ofxOscMessage &m){
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
    if (cmd == "polygon"){
        osc = getOSCcmd(msg);
        string cmd = osc[0];
        string msg = osc[1];
        
        if (cmd == "center"){
            center = ofPoint(m.getArgAsFloat(0), m.getArgAsFloat(1));
        }
        if (cmd == "nbPoint"){
            nbPoint = m.getArgAsInt32(0);
        }
        else if (cmd == "rot"){
            rot = ofMap(m.getArgAsFloat(0), 0, 1, 0, 360);
        }
        else if (cmd == "size"){
            size = m.getArgAsFloat(0);
        }
    }
}

