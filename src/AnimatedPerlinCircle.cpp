//
//  AnimatedPerlinCircle.cpp
//  LaserLiveTool
//
//  Created by Thomas Pachoud on 03/07/2016.
//
//

#include "AnimatedPerlinCircle.h"
//
//  AnimatedCircle.cpp
//  LaserLiveTool
//
//  Created by pach on 30/12/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


AnimatedPerlinCircle::AnimatedPerlinCircle(){
    
}

AnimatedPerlinCircle::~AnimatedPerlinCircle(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedPerlinCircle::setup(string name) {
    AnimatedStuff::setup(name);
    
    type = "AnimatedPerlinCircle";
    
    center = ofVec2f (0.5, 0.5);
    size = 0.5;
    nbPoints = 700;
    noiseSpeed = 0.;
    noiseCoeff = 0.;
    
    rotSpeed = 0.;
    smooth = 0.;
    
    noiseDisplace = 0.1;
    
    gui->addIntSlider("/nbPoints", 10, 1000, &nbPoints);
    gui->addSlider("/size", 0., 1., &size);
    gui->add2DPad("/center", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &center);
    gui->addSlider("/noise/speed", 0., 1., &noiseSpeed);
    gui->addSlider("/noise/coeff", 0., 1., &noiseCoeff);
    gui->addSlider("/noiseDisplace", 0., 1., &noiseDisplace);
    gui->addSlider("/rot/speed", 0., 1., &rotSpeed);
    gui->addSlider("/smooth", 0., 10., &smooth);
    
    
    timeNoise = 0.;
    timeRot = 0.;
    lastTime = ofGetElapsedTimef();
    
    load();
    
}

void AnimatedPerlinCircle::update() {
    AnimatedStuff::update();
    polylines.clear();
    ofPolyline p;
    
    float quadra = (2*PI) / nbPoints;

    timeNoise += (ofGetElapsedTimef()-lastTime)*noiseSpeed;
    timeRot += (ofGetElapsedTimef()-lastTime)*rotSpeed;
    lastTime = ofGetElapsedTimef();
    
    ofPoint disp;
    
    for (int n = 0; n<nbPoints; n++) {
        disp.x = ofSignedNoise(n*noiseDisplace, timeNoise);
        disp.y = ofSignedNoise(timeNoise, n*noiseDisplace);
        
        disp *= noiseCoeff;
        
        p.addVertex(center.x+sin(quadra*n+timeRot)*size+disp.x, center.y+cos(quadra*n+timeRot)*size+disp.y);
    }
    p.addVertex(p[0]);
    p = p.getSmoothed(smooth);
    
    polylines.push_back(p);
}

void AnimatedPerlinCircle::parseOSC(ofxOscMessage &m){
    
    vector<string> osc = getOSCcmd(m.getAddress());
    string cmd = osc[0];
    string msg = osc[1];
    
    if (cmd == "perlinCircle"){
        osc = getOSCcmd(msg);
        string cmd = osc[0];
        string msg = osc[1];
        
        if (cmd == "nbPoints"){
            nbPoints = m.getArgAsInt32(0);
        }
        else if (cmd == "size"){
            size = m.getArgAsFloat(0);
        }
        else if (cmd == "rot"){
            osc = getOSCcmd(msg);
            cmd = osc[0];
            msg = osc[1];
            if (cmd == "speed"){
                rotSpeed = m.getArgAsFloat(0);
            }
        }
        else if (cmd == "center" ){
            center = ofVec2f(m.getArgAsFloat(0.), m.getArgAsFloat(1));
        }
        else if (cmd == "smooth"){
            smooth = m.getArgAsFloat(0);
        }
        else if (cmd == "noise"){
            m.setAddress(msg);
            osc = getOSCcmd(m.getAddress());
            cmd = osc[0];
            msg = osc[1];
            
            if (cmd == "coeff"){
                noiseCoeff = m.getArgAsFloat(0);
            }
            else if (cmd == "speed"){
                noiseSpeed = m.getArgAsFloat(0);
            }
            else if (cmd == "displace"){
                noiseDisplace = m.getArgAsFloat(0);
            }
        }
    }
}
