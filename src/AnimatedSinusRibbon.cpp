//
//  AnimatedSinusRibbon.cpp
//  LaserLiveTool
//
//  Created by pach on 20/01/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//


#include "AnimatedSinusRibbon.h"

AnimatedSinusRibbon::AnimatedSinusRibbon(){
    
}

AnimatedSinusRibbon::~AnimatedSinusRibbon(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedSinusRibbon::setup(string name) {
    AnimatedStuff::setup(name);
    
    nbMaxVertex = 500;
    noiseCoeff = 0.0;
    smoothCoeff = 1.9;
    noiseSpeed = 0.2;
    moveSpeed = 0.5;
    windCoeff = 0.01;
    useNoise = true;
    
    windX = 0.;
    windY = 0.;

    lastPoint = ofVec2f (0.5, 0.5);
    
    sin1.freq = 0.1;
    sin1.speed = 0.;
    sin1.height = 0.;
    sin2.freq = 0.1;
    sin2.speed = 0.;
    sin2.height = 0.;
    sin3.freq = 0.1;
    sin3.speed = 0.;
    sin3.height = 0.;
//    tan1.freq = 0.;
//    tan1.speed = 0.;
//    tan1.height = 0.;

    gui->addIntSlider("max Vertex coeff", 1, 1000, &nbMaxVertex);
    gui->addSlider("smooth coeff", 1.99, 10., &smoothCoeff);
//    gui->addSlider("noise coeff", 0., 0.02, &noiseCoeff);
    gui->addSlider("wind coeff", 0., 0.05, &windCoeff);
    gui->addSlider("wind noise start pos", 0., 1., &windNoiseDisplace);
    gui->addToggle("use noise", &useNoise);
    
//    gui->addSlider("/noise", 0., 1., &noiseSpeed);
    gui->addSlider("/moveSpeed", 0., 1., &moveSpeed);
    gui->addSlider("/nbVertex", 0., 1., &nbVertex);
    gui->addSlider("/smooth", 0., 1., &smooth);
    gui->add2DPad("/wind", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &wind);
//    gui->add2DPad("/pos", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &curPos);
    
//    gui->addSpacer();
//    gui->addToggle("sin mode", &sinMode);
    gui->addSpacer();
    gui->addSlider("/1/freq", 0., 50., &sin1.freq);
    gui->addSlider("/1/speed", -0.01, 0.01, &sin1.speed);
    gui->addSlider("/1/height", 0., 0.5, &sin1.height);
    gui->addSpacer();
    gui->addSlider("/2/freq", 0., 50., &sin2.freq);
    gui->addSlider("/2/speed", -0.01, 0.01, &sin2.speed);
    gui->addSlider("/2/height", 0., 0.5, &sin2.height);
    gui->addSpacer();
    gui->addSlider("/3/freq", 0., 50., &sin3.freq);
    gui->addSlider("/3/speed", -0.01, 0.01, &sin3.speed);
    gui->addSlider("/3/height", 0., 0.5, &sin3.height);
//    gui->addSpacer();
//    gui->addSlider("/tan/freq", 0.1, 50., &tan1.freq);
//    gui->addSlider("/tan/speed", -0.1, 0.1, &tan1.speed);
//    gui->addSlider("/tan/height", 0., 0.5, &tan1.height);
    
    gui->setHeight(ofGetHeight());
    
    type = "AnimatedSinusRibbon";
     
    load();
    
    polylines.clear();
    
//    ofPolyline p;
    for (int i=0; i<nbMaxVertex; i++) {
        spleenLine.addVertex(ofVec2f(0.5, 0.5));
    }
    polylines.push_back(spleenLine);
    
    lastTime = ofGetElapsedTimef();
    derivativeTime = 0;


}

void AnimatedSinusRibbon::update() {
    
    derivativeTime += (ofGetElapsedTimef()-lastTime);
    
    windX = ofMap(wind.x, 0., 1., -windCoeff, windCoeff);
    windY = ofMap(wind.y, 0., 1., -windCoeff, windCoeff);
    
    // ajoute nouveau point.
    if (useNoise) {
        lastPoint = ofVec2f(ofNoise(ofGetElapsedTimef()*moveSpeed, 0), ofNoise(ofGetElapsedTimef()*moveSpeed, 1));
        
        if (windX<0.){
            lastPoint.x = ofMap(lastPoint.x, 0., 1., ofMap(windX, 0., -windCoeff, 0., windNoiseDisplace), 1.);
        }else{
            lastPoint.x = ofMap(lastPoint.x, 0., 1., 0., ofMap(windX, 0., windCoeff, 1., 1.-windNoiseDisplace));
        }
        
        if (windY<0.){
            lastPoint.y = ofMap(lastPoint.y, 0., 1., ofMap(windY, 0., -windCoeff, 0., windNoiseDisplace), 1.);
        }else{
            lastPoint.y = ofMap(lastPoint.y, 0., 1., 0., ofMap(windY, 0., windCoeff, 1., 1.-windNoiseDisplace));
        }
    }
    else{
        lastPoint = curPos;
    }
    
//    polylines[0].addVertex(lastPoint.x, lastPoint.y);
//    vector<ofPoint> p = polylines[0].getVertices();
    spleenLine.addVertex(lastPoint.x, lastPoint.y);
    vector<ofPoint> p = spleenLine.getVertices();
    
    // si trop grand, enleve dernier point (premier du polyline
    while (p.size() > (int)(nbMaxVertex*nbVertex)){
        p.erase(p.begin());
    }
    
    // add noise + wind + ... to all points
    vector<ofPoint>::iterator pIt = p.begin();
    vector<ofPoint>::iterator pItEnd = p.end();
    int idPt=0;
    float noiseX, noiseY, disp1, disp2, disp3, dispT1;
    ofVec2f norm, tangent;
    
    while (pIt != pItEnd && idPt < (int)(nbMaxVertex*nbVertex - 2)){
        
        //        float noiseX = ofSignedNoise(pIt->x, idPt/nbMaxVertex*noiseSpeed);
        //        float noiseY = ofSignedNoise(pIt->y, idPt/nbMaxVertex*noiseSpeed);
        noiseX = ofSignedNoise(pIt->x, idPt/nbMaxVertex*noiseSpeed, ofGetElapsedTimef());
        noiseY = ofSignedNoise(pIt->y, idPt/nbMaxVertex*noiseSpeed, ofGetElapsedTimef());
        
        noiseX *= noiseCoeff;
        noiseY *= noiseCoeff;
        
        //        cout<<"noise : "<<noiseX<<" "<<noiseY<<endl;
        pIt->x += noiseX;
        pIt->y += noiseY;
        
        pIt->x += windX;
        pIt->y += windY;
        
//        disp1 = sin((float)idPt/sin1.freq+ofGetElapsedTimef()*sin1.speed)*sin1.height;
//        disp2 = sin((float)idPt/sin2.freq+ofGetElapsedTimef()*sin2.speed)*sin2.height;
//        disp3 = sin((float)idPt/sin3.freq+ofGetElapsedTimef()*sin3.speed)*sin3.height;
//        
//        ofVec2f norm = polylines[0].getNormalAtIndex(idPt);
//        norm *= (disp1+disp2+disp3);
//        *pIt += norm;
//        pIt->x += norm.x;
//        pIt->y += norm.y;
        
        //        if (pIt->x < 0.) {
        //            pIt->x = 0.;
        //        }else if (pIt->x > 1.){
        //            pIt->x = 1.;
        //        }
        //
        //        if (pIt->y < 0.) {
        //            pIt->y = 0.;
        //        }else if (pIt->y > 1.){
        //            pIt->y = 1.;
        //        }
        //
        //        pIt ++ ;
        
        if (pIt->x < 0. || pIt->x > 1. || pIt->y < 0. || pIt->y > 1.){
            vector<ofPoint>::iterator pTemp = pIt;
            pIt ++;
            p.erase(pTemp);
        }else{
            pIt ++;
        }
        
        idPt++;
    }
    
    polylines[0].clear();
    spleenLine.clear();
//    polylines[0].addVertices(p);
//    polylines[0].getResampledBySpacing(0.5);
    spleenLine.addVertices(p);
    spleenLine.getResampledBySpacing(0.5);
    spleenLine = spleenLine.getSmoothed(smoothCoeff*smooth);
    
    polylines[0] = spleenLine;
    
    for (int i=0; i<polylines[0].size(); i++) {
        disp1 = sin((float)i*sin1.freq/polylines[0].size()+derivativeTime*sin1.speed)*sin1.height;
        disp2 = sin((float)i*sin2.freq/polylines[0].size()+derivativeTime*sin2.speed)*sin2.height;
        disp3 = sin((float)i*sin3.freq/polylines[0].size()+derivativeTime*sin3.speed)*sin3.height;
//        dispT1 = sin((float)i*tan1.freq/polylines[0].size()+derivativeTime*tan1.speed)*tan1.height;
        norm = spleenLine.getNormalAtIndex(i);
        norm.normalize();
        norm *= (disp1+disp2+disp3);
//        tangent = polylines[0].getTangentAtIndex(i);
//        tangent.normalize();
//        tangent *= dispT1;
        
        polylines[0][i] += norm;//+tangent;
    }
   
//    polylines[0] = polylines[0].getSmoothed(smoothCoeff*smooth);
    
}

void AnimatedSinusRibbon::parseOSC(ofxOscMessage &m){

    vector<string> osc = getOSCcmd(m.getAddress());
    string cmd = osc[0];
    string msg = osc[1];
    
    if (cmd == "nbVertex"){
        nbVertex = m.getArgAsFloat(0);
    }
    else if (cmd == "noise"){
        noiseSpeed = m.getArgAsFloat(0);
    }
    else if (cmd == "moveSpeed"){
        moveSpeed = m.getArgAsFloat(0);
    }
    else if (cmd == "smooth"){
        smooth = m.getArgAsFloat(0);
    }
    else if (cmd == "wind"){
        wind = ofPoint(m.getArgAsFloat(0), m.getArgAsFloat(1));
    }
    else if (cmd == "pos"){
        curPos = ofPoint(m.getArgAsFloat(0), m.getArgAsFloat(1));
    }
}
