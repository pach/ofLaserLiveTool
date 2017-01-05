//
//  AnimatedImacStraw.cpp
//  LaserLiveTool
//
//  Created by pach on 14/01/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//


#include "AnimatedImacStraw.h"
#include "ofxXmlSettings.h"

AnimatedImacStraw::AnimatedImacStraw(){
    
}

AnimatedImacStraw::~AnimatedImacStraw(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedImacStraw::setup(string name) {
    AnimatedStuff::setup(name);
    type = "AnimatedImacStraw";
    
    idUpdateStraw = 0;
    nbStraw = 11;
    for (int i=0 ; i<nbStraw ; i++){
        size.push_back(0.2);
        active.push_back(true);
        strawPos.push_back(ofVec2f(ofNoise(ofGetElapsedTimef()*i), ofNoise(ofGetElapsedTimef()*2+i)));
        rot = 90.;
    }
    
    idOn = 0;
    animationSpeed = 1.;
    animationMode = 1;
    
    horizontalDisplace = 0.1;
    
    gui->addSlider("rotation", 0., 360., &rot);
    
    gui->addIntSlider("idUpdate", 0, nbStraw, &idUpdateStraw);
    gui->add2DPad("update pos", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &updatePos);
    gui->addSlider("update size", 0., 1., &updateSize);
    gui->addIntSlider("anim mode", 0, 4, &animationMode);
    gui->addSlider("anim speed", 0., 2., &animationSpeed);
    gui->addSlider("displaceSize", 0., 0.2, &horizontalDisplace);
    
    load();
}


void AnimatedImacStraw::save(string layerName){
    AnimatedStuff::save(layerName);
    
    ofxXmlSettings xml;
    
    for (int i=0; i<nbStraw; i++) {
        xml.addTag("PT");
        xml.pushTag("PT", i);
        xml.addValue("X", strawPos[i].x);
        xml.addValue("Y", strawPos[i].y);
        xml.addValue("SIZE", size[i]);
        xml.popTag();
    }
    
    xml.addTag("ALL");
    xml.pushTag("ALL");
    xml.addValue("NB_STRAW", nbStraw);
    xml.addValue("ROT", rot);
    xml.popTag();
    
    xml.save(layerName+"/"+"imacStraws_pts.xml");
}

void AnimatedImacStraw::load(string layerName){
    AnimatedStuff::load(layerName);
    
    ofxXmlSettings xml;
    if(!xml.load("imacStraws_pts.xml")){
        cout<<"error loading "<<name<<"_pts.xml files"<<endl;
        return;
    }
    
    xml.pushTag("ALL");
    nbStraw = xml.getValue("NB_STRAW", 11);
    rot = xml.getValue("ROT", 0);
    xml.popTag();
    
    strawPos.clear();
    size.clear();
    active.clear();
    for (int i = 0; i<nbStraw; i++) {
        xml.pushTag("PT", i);
        ofPoint p = ofVec2f(xml.getValue("X", 0.5), xml.getValue("Y", 0.5));
        cout<<"pt "<<i<<" "<<p<<endl;
        strawPos.push_back(p);
        size.push_back(xml.getValue("SIZE", 0.1));
        active.push_back(true);
        xml.popTag();
    }
}

void AnimatedImacStraw::update() {
    polylines.clear();
    
    
    // animation calculation
    displacePos = 0;
    // no animation
    if (animationMode == 0){
        for (int i=0; i<nbStraw; i++) {
            active[i] = true;
        }
    }
    // forward no displace
    else if (animationMode == 1){
        if(ofGetElapsedTimef()-lastStepTime > animationSpeed){
            lastStepTime = ofGetElapsedTimef();
            idOn ++;
            if (idOn > nbStraw/2+1){
                idOn = 0;
            }
        }
        
        for (int i=0; i<nbStraw; i++) {
            active[i] = false;
        }
        for (int i=0; i<nbStraw/2+1; i++) {
            if (i==idOn) {
                if (i==0) {
                    active[0]=true;
                }else{
                    active[i*2-1]=true;
                    active[i*2]=true;
                }
            }
        }
    }
    // backward no displace
    else if (animationMode == 2){
        if(ofGetElapsedTimef()-lastStepTime > animationSpeed){
            lastStepTime = ofGetElapsedTimef();
            idOn --;
            if (idOn < 0){
                idOn = nbStraw/2+1;
            }
        }
        
        for (int i=0; i<nbStraw; i++) {
            active[i] = false;
        }
        for (int i=0; i<nbStraw/2+1; i++) {
            if (i==idOn) {
                if (i==0) {
                    active[0]=true;
                }else{
                    active[i*2-1]=true;
                    active[i*2]=true;
                }
            }
        }
    }
    // forward + displace
    else if (animationMode == 3){
        float displaceTime = ofGetElapsedTimef()-lastStepTime;
        
        displacePos = ofMap(displaceTime, 0., animationSpeed, -horizontalDisplace, horizontalDisplace);
        
        if(displaceTime > animationSpeed){
            lastStepTime = ofGetElapsedTimef();
            idOn ++;
            if (idOn > nbStraw/2+1){
                idOn = 0;
            }
        }
        
        for (int i=0; i<nbStraw; i++) {
            active[i] = false;
        }
        for (int i=0; i<nbStraw/2+1; i++) {
            if (i==idOn) {
                if (i==0) {
                    active[0]=true;
                }else{
                    active[i*2-1]=true;
                    active[i*2]=true;
                }
            }
        }
    }
    // backward + displace
    else if (animationMode == 4){
        float displaceTime = ofGetElapsedTimef()-lastStepTime;
        
        displacePos = ofMap(displaceTime, 0., animationSpeed, -horizontalDisplace, horizontalDisplace);
        
        
        if(displaceTime > animationSpeed){
            lastStepTime = ofGetElapsedTimef();
            idOn --;
            if (idOn < 0){
                idOn = nbStraw/2+1;
            }
        }
        
        for (int i=0; i<nbStraw; i++) {
            active[i] = false;
        }
        for (int i=0; i<nbStraw/2+1; i++) {
            if (i==idOn) {
                if (i==0) {
                    active[0]=true;
                }else{
                    active[i*2-1]=true;
                    active[i*2]=true;
                }
            }
        }
    }
    
    
    //update polylines
    ofPolyline p;
    for (int i=0; i<nbStraw; i++) {
        if (i == idUpdateStraw-1) {
            strawPos[i] = updatePos;
            size[i] = updateSize;
        }
        if (active[i]) {
            p.clear();
            
            p.addVertex(strawPos[i]+ofVec2f(displacePos, -size[i]).rotate(rot));
            p.addVertex(strawPos[i]+ofVec2f(displacePos, size[i]).rotate(rot));
            
            polylines.push_back(p);
        }
    }
}
