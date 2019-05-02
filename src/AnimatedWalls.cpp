//
//  AnimatedWalls.cpp
//  LaserLiveTool
//
//  Created by pach on 11/02/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//


#include "AnimatedWalls.h"

AnimatedWalls::AnimatedWalls(){
    
}

AnimatedWalls::~AnimatedWalls(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedWalls::setup(string name) {
    AnimatedStuff::setup(name);
    type = "AnimatedWalls";
    
    isOrigin = false;
    
    posX1 = 0.1;
    posX2 = 0.9;
    posY1 = ofVec2f(0.1, 0.9);
    posY2 = ofVec2f(0.1, 0.9);
    
    ofPolyline p;
    p.addVertex(ofVec2f(posX1, posY1[1]));
    p.addVertex(ofVec2f(posX1, posY1[0]));
    p.addVertex(ofVec2f(posX2, posY2[0]));
    p.addVertex(ofVec2f(posX2, posY2[1]));
    
    polylines.push_back(p);
    
    gui->addToggle("is origin", &isOrigin);
    gui->addSlider("posX1", 0., 1., &posX1);
    gui->addSlider("posX2", 0., 1., &posX2);
    gui->addSlider("posY11", 0., 1., &posY1[0]);
    gui->addSlider("posY12", 0., 1., &posY1[1]);
    gui->addSlider("posY21", 0., 1., &posY2[0]);
    gui->addSlider("posY22", 0., 1., &posY2[1]);
    
//    load();
    
}

void AnimatedWalls::update() {
    AnimatedStuff::update();
    
    polylines.clear();
    ofPolyline p;
    if (isOrigin) {
        p.addVertex(ofVec2f(posX1, posY1[1]));
        p.addVertex(ofVec2f(posX1, posY1[0]));
        p.addVertex(ofVec2f(posX2, posY2[0]));
        p.addVertex(ofVec2f(posX2, posY2[1]));
        polylines.push_back(p);
    }else{
        p.addVertex(ofVec2f(posX1, posY1[1]));
        p.addVertex(ofVec2f(posX1, posY1[0]));
        polylines.push_back(p);
        p.clear();
        p.addVertex(ofVec2f(posX2, posY2[1]));
        p.addVertex(ofVec2f(posX2, posY2[0]));
        polylines.push_back(p);
    }
}

void AnimatedWalls::parseOSC(ofxOscMessage &m){
    vector<string> osc = getOSCcmd(m.getAddress());
    string cmd = osc[0];
    string msg = osc[1];
    
    cout<<"wall osc msg : "<<cmd<<" "<<msg<<endl;
    if (cmd == "wall"){
        if (msg == "/1/x") {
            posX1 = m.getArgAsFloat(0);
        }
        else if (msg == "/2/x") {
            posX2 = m.getArgAsFloat(0);
        }
        else if (msg == "/1/y/1") {
            posY1[0] = m.getArgAsFloat(0);
        }
        else if (msg == "/1/y/2") {
            posY1[1] = m.getArgAsFloat(0);
        }
        else if (msg == "/2/y/1") {
            posY2[0] = m.getArgAsFloat(0);
        }
        else if (msg == "/2/y/2") {
            posY2[1] = m.getArgAsFloat(0);
        }
    }
}
