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
    
    
    timeline.addCurves("noise speed");
    timeline.addCurves("line mode");
    timeline.addCurves("nb points");
    timeline.addCurves("scaleX");
    timeline.addCurves("scaleY");
    timeline.addCurves("offsetX");
    timeline.addCurves("offsetY");
    
    gui->addSlider("noise speed coeff", 0., 0.5, &noiseSpeedCoeff);
    gui->addIntSlider("nb points coeff", 1, 20, &nbPointsCoeff);
//    gui->addToggle("line mode", &lineMode);
    noiseTime = 0.;
    
    load();
    
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
    nbPoints = (int)(timeline.getValue("nb points")*nbPointsCoeff);
    if (nbPoints == 0) nbPoints = 1;
    
    lineMode = (timeline.getValue("line mode")>0.5) ? true : false;
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
    
    noiseSpeed = timeline.getValue("noise speed");
    
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
    
    float scaleX = timeline.getValue("scaleX");
    float scaleY = timeline.getValue("scaleY");
    float offsetX = ofMap(timeline.getValue("offsetX"), 0., 1., -0.5, 0.5);
    float offsetY = ofMap(timeline.getValue("offsetY"), 0., 1., -0.5, 0.5);
    
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

//void AnimatedPerlinLines::draw() {
//    if (setFirstShape){
//
//    }else{
//
//    }
//}

