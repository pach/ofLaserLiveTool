//
//  AnimatedOSCLines.cpp
//  LaserLiveTool
//
//  Created by pach on 02/01/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//


#include "AnimatedOSCLines.h"

AnimatedOSCLines::AnimatedOSCLines(){
    
}

AnimatedOSCLines::~AnimatedOSCLines(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedOSCLines::setup(string name) {
    AnimatedStuff::setup(name);
    type = "AnimatedOSCLines";
    
    ofPolyline p;
    p.addVertex(ofVec2f(0.5, 0.5));
    polylines.push_back(p);
}

void AnimatedOSCLines::update() {
    AnimatedStuff::update();
}

void AnimatedOSCLines::parseOSC(ofxOscMessage &m){
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
    
//    cout<<"osc points "<<cmd<<endl;
    
    if (cmd == "oscPoints"){
        ofPolyline p;
        polylines.clear();
        int nbPoints = m.getArgAsInt32(0);
        for (int i=0; i<nbPoints-1; i++) {
            p.addVertex(m.getArgAsFloat(1+i*2), m.getArgAsFloat(1+i*2+1));
        }
//        p.addVertex(m.getArgAsFloat(1), m.getArgAsFloat(2));
        polylines.push_back(p);
    }
}
