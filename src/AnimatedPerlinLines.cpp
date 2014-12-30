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

    
    if(lineMode){
        for (int i=0 ; i<=nbPoints ; i++) {
            ofPolyline p;
            p.addVertex(0.5, 0.5);
            p.addVertex(0.5, 0.5);
            polylines.push_back(p);
        }
    }
    else{
        ofPolyline p;
        for (int i=0 ; i<=nbPoints ; i++) {
            p.addVertex(0.5, 0.5);
        }
        polylines.push_back(p);
    }
    
    type = "AnimatedPerlin";
}

void AnimatedPerlinLines::update() {
//    nbPoints = (int)(timeline.getValue("nb points")*nbPointsCoeff);
    nbPoints = nbVertex*nbPointsCoeff;
    if (nbPoints == 0) nbPoints = 1;
    
//    lineMode = (timeline.getValue("line mode")>0.5) ? true : false;
    if (nbPoints != oldNbPoints){
        if (lineMode){
            if (nbPoints > oldNbPoints){
                for (int i= oldNbPoints; i<=nbPoints; i++) {
                    ofPolyline p;
                    p.addVertex(0.5, 0.5);
                    p.addVertex(0.5, 0.5);
                    polylines.push_back(p);
                }
            }
            else{
                polylines.resize(nbPoints+1);
            }
        }
        else{
            if (nbPoints > oldNbPoints){
                for (int i=oldNbPoints; i<=nbPoints; i++) {
                    polylines[0].addVertex(0.5, 0.5);
                }
            }
            else{
                polylines[0].resize(nbPoints+1);
            }
        }
        oldNbPoints = nbPoints;
    }
    
//    noiseSpeed = timeline.getValue("noise speed");
    
    noiseTime += noiseSpeedCoeff*noiseSpeed;
    
    
    // if line mode did change
    if (oldMode != lineMode) {
        if(lineMode){
            ofPolyline oldPoly = polylines[0];
            polylines.clear();
            for (int i=0 ; i<nbPoints ; i++) {
                ofPolyline p ;
                p.addVertex(oldPoly[i]);
                p.addVertex(oldPoly[i+1]);
                polylines.push_back(p);
            }
            ofPolyline p ;
            p.addVertex(oldPoly[nbPoints]);
            p.addVertex(oldPoly[0]);
            polylines.push_back(p);
        }
        else{
            ofPolyline p;
            for (int i=0 ; i<=nbPoints ; i++) {
                p.addVertex(polylines[i][0]);
            }
            polylines.clear();
            polylines.push_back(p);
        }
        oldMode = lineMode;
    }
    
//    float scaleX = timeline.getValue("scaleX");
//    float scaleY = timeline.getValue("scaleY");
//    float offsetX = ofMap(timeline.getValue("offsetX"), 0., 1., -0.5, 0.5);
//    float offsetY = ofMap(timeline.getValue("offsetY"), 0., 1., -0.5, 0.5);
    float scaleX = scale.x;
    float scaleY = scale.y;
    float offsetX = offset.x;
    float offsetY = offset.y;
    
    // set perlin points
    if (lineMode) {
        polylines[0][0].set(ofMap(ofNoise(0, 0, noiseTime), 0., 1., 0.5-scaleX, 0.5+scaleX)+offsetX, ofMap(ofNoise(0, 1, noiseTime), 0., 1., 0.5-scaleY, 0.5+scaleY)+offsetY);
        polylines[0][1].set(ofMap(ofNoise(0, 0, noiseTime), 0., 1., 0.5-scaleX, 0.5+scaleX)+offsetX, ofMap(ofNoise(0, 1, noiseTime), 0., 1., 0.5-scaleY, 0.5+scaleY)+offsetY);
        for (int i = 1; i<nbPoints; i++) {
            polylines[i][0].set(polylines[i-1][1]);
            polylines[i][1].set(ofMap(ofNoise(i, 0, noiseTime), 0., 1., 0.5-scaleX, 0.5+scaleX), ofMap(ofNoise(i, 1, noiseTime), 0., 1., 0.5-scaleY, 0.5+scaleY)+offsetY);
        }
        polylines[nbPoints][0].set(polylines[nbPoints-1][1]);
        polylines[nbPoints][1].set(polylines[0][0]);
    }
    else{
        for (int i = 0; i<nbPoints; i++) {
            polylines[0][i].set(ofMap(ofNoise(i, 0, noiseTime), 0., 1., 0.5-scaleX, 0.5+scaleX)+offsetX, ofMap(ofNoise(i, 1, noiseTime), 0., 1., 0.5-scaleY, 0.5+scaleY)+offsetY);
        }
        polylines[0][nbPoints]= polylines[0][0];
    }
}

void AnimatedPerlinLines::parseOSC(ofxOscMessage &m){
    string msg = m.getAddress();
    string cmd ;
    
    int ces = msg.find_first_of("/");
    
    if (ces != -1) {
        if (ces == 0){
            msg = msg.substr(ces+1);
            ces = msg.find_first_of("/");
        }
        if (ces == -1){
            cmd = msg;
        }
        else{
            cmd = msg.substr(0, ces);
            msg = msg.substr(ces);
        }
    }
    
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

