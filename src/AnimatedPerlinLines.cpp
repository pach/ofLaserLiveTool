//
//  AnimatedPerlinLines.cpp
//  LaserAnimTool
//
//  Created by pach on 20/09/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "AnimatedPerlinLines.h"

AnimatedPerlinLines::AnimatedPerlinLines(){
    
}

AnimatedPerlinLines::~AnimatedPerlinLines(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedPerlinLines::setup(string name) {
    AnimatedStuff::setup(name);
    
    noiseSpeedCoeff = 0.05;
    nbPoints = 8;
    noiseSpeed = 0.;
    lineMode = false;
    
    
//    timeline.addCurves("noise speed");
//    timeline.addCurves("line mode");
//    timeline.addCurves("nb points");
//    timeline.addCurves("scaleX");
//    timeline.addCurves("scaleY");
//    timeline.addCurves("offsetX");
//    timeline.addCurves("offsetY");
    
    gui->addSlider("noise speed coeff", 0., 0.5, &noiseSpeedCoeff);
    gui->addIntSlider("nb points coeff", 1, 20, &nbPointsCoeff);
    gui->addSlider("/noiseSpeed", 0., 1., &noiseSpeed);
    gui->addSlider("/nbPoint", 0., 1., &nbVertex);
    gui->add2DPad("/offset", ofxUIVec2f(-0.5, 0.5), ofxUIVec2f(-0.5, 0.5), &offset);
    gui->add2DPad("/scale", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &scale);
    gui->addToggle("/lineMode", &lineMode);
    noiseTime = 0.;
    
    load();
    nbPoints = nbVertex*nbPointsCoeff;
    
    oldNbPoints = nbPoints;
    oldMode = lineMode;

    easingType = ofxTween::easeInOut;
    clamp = true;
    
    for (int i=0 ; i<=nbPoints ; i++) {
        targetPoint.addVertex(0.5, 0.5);
    }
    
//    if(lineMode){
//        for (int i=0 ; i<=nbPoints ; i++) {
//            ofPolyline p;
//            p.addVertex(0.5, 0.5);
//            p.addVertex(0.5, 0.5);
//            targetPoint.push_back(p);
//        }
//    }
//    else{
//        ofPolyline p;
//        for (int i=0 ; i<=nbPoints ; i++) {
//            p.addVertex(0.5, 0.5);
//        }
//        targetPoint.push_back(p);
//    }
    
    type = "AnimatedPerlin";
}

void AnimatedPerlinLines::update() {
    AnimatedStuff::update();

    nbPoints = nbVertex*nbPointsCoeff;
    if (nbPoints == 0) nbPoints = 1;
    
    if (nbPoints != oldNbPoints){
        if (nbPoints > oldNbPoints){
            for (int i=oldNbPoints; i<=nbPoints; i++) {
                targetPoint.addVertex(0.5, 0.5);
            }
        }
        else{
            targetPoint.resize(nbPoints+1);
        }
        oldNbPoints = nbPoints;
    }
    
    noiseTime += noiseSpeedCoeff*noiseSpeed;
    
    
    float scaleX = scale.x;
    float scaleY = scale.y;
    float offsetX = offset.x;
    float offsetY = offset.y;
    
    // set perlin points
    for (int i = 0; i<targetPoint.size(); i++) {
        targetPoint[i].set(ofMap(ofNoise(i, 0, noiseTime), 0., 1., 0.5-scaleX, 0.5+scaleX)+offsetX, ofMap(ofNoise(i, 1, noiseTime), 0., 1., 0.5-scaleY, 0.5+scaleY)+offsetY);
    }
    
    // doSpacing

    polylines.clear();
    if (!lineMode){
        polylines.push_back(targetPoint.getResampledByCount(NB_POINTS_SPACING));
    }
    else{
        ofPolyline p;
        ofPoint pt;
        int pointPerLine = NB_POINTS_SPACING/targetPoint.size();
        for (int i=0; i<targetPoint.size()-1; i++) {
            for (int j=0; j<pointPerLine; j++) {
                pt = ofVec2f(ofxTween::map(j, 0, pointPerLine, targetPoint[i].x, targetPoint[i+1].x, clamp, easing, easingType), ofxTween::map(j, 0, pointPerLine, targetPoint[i].y, targetPoint[i+1].y, clamp, easing, easingType));
                p.addVertex(pt);
            }
            p.addVertex(p[0]);
        }
        polylines.push_back(p);
    }
//    }
}

void AnimatedPerlinLines::parseOSC(ofxOscMessage &m){
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
    
    if (cmd == "perlin"){
        osc = getOSCcmd(msg);
        string cmd = osc[0];
        string msg = osc[1];
    
        if (cmd == "noiseSpeed"){
            noiseSpeed = m.getArgAsFloat(0);
        }
        else if (cmd == "nbPoint"){
            nbVertex = m.getArgAsFloat(0);
        }
        else if (cmd == "offset"){
            offset = ofPoint(ofMap(m.getArgAsFloat(0), 0, 1, -0.5, 0.5), ofMap(m.getArgAsFloat(1), 0, 1, -0.5, 0.5));
        }
        else if (cmd == "scale"){
            scale = ofPoint(m.getArgAsFloat(0), m.getArgAsFloat(1));
        }
        else if (cmd == "lineMode"){
            lineMode = m.getArgAsInt32(0);
        }
    }
}

