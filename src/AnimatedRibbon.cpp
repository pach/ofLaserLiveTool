//
//  AnimatedRibbon.cpp
//  LaserAnimTool
//
//  Created by pach on 20/09/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "AnimatedRibbon.h"

AnimatedRibbon::AnimatedRibbon(){
    
}

AnimatedRibbon::~AnimatedRibbon(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedRibbon::setup(string name) {
    AnimatedStuff::setup(name);
    
    nbMaxVertex = 500;
    noiseCoeff = 0.0;
    smoothCoeff = 1.9;
    noiseSpeed = 0.2;
    moveSpeed = 0.5;
    windCoeff = 0.01;
    useNoise = false;
    isRecording = false;
    
    windX = 0.;
    windY = 0.;
    
    timeKeyPickDistance = 2;
    
    lastPoint = ofVec2f (0.5, 0.5);
    
    gui->addIntSlider("max vertex", 1, 1000, &nbMaxVertex);
    gui->addSlider("noise coeff", 0., 0.02, &noiseCoeff);
    gui->addSlider("smooth coeff", 1.99, 10., &smoothCoeff);
    gui->addSlider("noise Speed", 0., 1., &noiseSpeed);
    gui->addSlider("move Speed", 0., 1., &moveSpeed);
    gui->addSlider("wind coeff", 0., 0.05, &windCoeff);
    gui->addSlider("wind noise start pos", 0., 1., &windNoiseDisplace);
    gui->addToggle("use noise", &useNoise);
    gui->addToggle("record", &isRecording);
    
    timeline.addCurves(name+".x");
    timeline.addCurves(name+".y");
    
    timeline.addCurves(name+".wind.x");
    timeline.addCurves(name+".wind.y");
    
    timeline.addCurves("smooth");
    timeline.addCurves("nb vertex");
    
    type = "AnimatedRibbon";
    
    load();
    
    ofPolyline p;
    for (int i=0; i<nbMaxVertex; i++) {
        p.addVertex(ofVec2f(0.5, 0.5));
    }
    polylines.push_back(p);
}

void AnimatedRibbon::update() {
    
    windX = ofMap(timeline.getValue(name+".wind.x"), 0., 1., -windCoeff, windCoeff);
    windY = ofMap(timeline.getValue(name+".wind.y"), 0., 1., -windCoeff, windCoeff);
    
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
    }else{
        if (!isRecording){
            lastPoint.x = timeline.getValue(name+".x");
            lastPoint.y = timeline.getValue(name+".y");
        }
        else{
            lastPoint.x = (float)ofGetMouseX()/(float)ofGetWidth();
            lastPoint.y = (float)ofGetMouseY()/(float)ofGetHeight();
            addPointAtCurrentTime(lastPoint.x, lastPoint.y);
        }
    }
    

    polylines[0].addVertex(lastPoint.x, lastPoint.y);
    vector<ofPoint> p = polylines[0].getVertices();
    polylines[0].clear();
    
    
    while (p.size() > (int)(nbMaxVertex*timeline.getValue("nb vertex"))){
        p.erase(p.begin());
    }
    
    vector<ofPoint>::iterator pIt = p.begin();
    vector<ofPoint>::iterator pItEnd = p.end();
    int idPt=0;
    while (pIt != pItEnd && idPt < (int)(nbMaxVertex*timeline.getValue("nb vertex") - 2)){
        
//        float noiseX = ofSignedNoise(pIt->x, idPt/nbMaxVertex*noiseSpeed);
//        float noiseY = ofSignedNoise(pIt->y, idPt/nbMaxVertex*noiseSpeed);
        float noiseX = ofSignedNoise(pIt->x, idPt/nbMaxVertex*noiseSpeed, ofGetElapsedTimef());
        float noiseY = ofSignedNoise(pIt->y, idPt/nbMaxVertex*noiseSpeed, ofGetElapsedTimef());
        
        noiseX *= noiseCoeff;
        noiseY *= noiseCoeff;
        
//        cout<<"noise : "<<noiseX<<" "<<noiseY<<endl;
        pIt->x += noiseX;
        pIt->y += noiseY;
        
        pIt->x += windX;
        pIt->y += windY;
        
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
    
    polylines[0].addVertices(p);
    polylines[0] = polylines[0].getSmoothed(smoothCoeff*timeline.getValue("smooth"));
}

void AnimatedRibbon::addPointAtCurrentTime(float x, float y){
    
    bool found = false;
    int idKey = -1;
    
    ofxTLCurves * keysX = (ofxTLCurves *)(timeline.getTrack(name+".x"));
    if(keysX != NULL){
        vector<ofxTLKeyframe *> & keyframesX = keysX->getKeyframes();
        for (int i=0; i<keyframesX.size() && !found; i++) {
            if (keyframesX[i]->previousTime >= timeline.getCurrentTimeMillis()-timeKeyPickDistance
                && keyframesX[i]->previousTime <= timeline.getCurrentTimeMillis()+timeKeyPickDistance) {
                found = true;
                idKey = i;
            }
        }
        
        if (found){
            keysX->updateKey(idKey, x);
            ofLog(OF_LOG_VERBOSE, "updating x key "+ofToString(idKey)+" to pos "+ofToString(x));
        }
        else {
            keysX->addKeyframe(x);
            ofLog(OF_LOG_VERBOSE, "adding a new x key ");
        }
    }
    else{
        ofLog(OF_LOG_NOTICE, "no timeline found to add key");
    }
    
    
    // update y point
    ofxTLCurves * keysY = (ofxTLCurves *)(timeline.getTrack(name+".y"));
    if(keysY != NULL){
        vector<ofxTLKeyframe *> & keyframesY = keysY->getKeyframes();
        
        found = false;
        for (int i=0; i<keyframesY.size() && !found; i++) {
            if (keyframesY[i]->previousTime >= timeline.getCurrentTimeMillis()-timeKeyPickDistance
                && keyframesY[i]->previousTime <= timeline.getCurrentTimeMillis()+timeKeyPickDistance) {
                found = true;
                idKey = i;
            }
        }
        
        if (found){
            keysY->updateKey(idKey, y);
            ofLog(OF_LOG_VERBOSE, "updating y key "+ofToString(idKey)+" to pos "+ofToString(y));
        }
        else {
            keysY->addKeyframe(y);
            ofLog(OF_LOG_VERBOSE, "adding a new y key ");
        }
    }
    else{
        ofLog(OF_LOG_NOTICE, "no timeline found to add key");
    }
}
