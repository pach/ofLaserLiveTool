



//
//  AnimatedStuff.cpp
//  LaserAnimTool
//
//  Created by pach on 29/05/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "AnimatedStuff.h"

AnimatedStuff::AnimatedStuff(){
    
}

AnimatedStuff::~AnimatedStuff(){
    delete gui;
}

void AnimatedStuff::setTimelineActive(bool enable){
    if (enable){
        timeline.enableEvents();
        ofLog(OF_LOG_NOTICE, "enabling events");
    }else{
        timeline.disableEvents();
        ofLog(OF_LOG_NOTICE, "disabling events");
    }
}

void AnimatedStuff::setLoopMode(ofLoopType mode){
    loopMode = mode;
    timeline.setLoopType(mode);
}


void AnimatedStuff::setup(string name) {
    timeline.setup();
    timeline.setSpacebarTogglePlay(false);
    timeline.setMinimalHeaders(true);
    timeline.setShowInoutControl(false);
    timeline.disableEvents();
    
    gui = new ofxUISuperCanvas("");
    gui->disable();
    
    setName(name);
    
    isSelected = false;
    drawW = ofGetWidth();
    drawH = ofGetHeight();
    drawOffset = ofVec2f (0., 0.);
    setLoopMode(OF_LOOP_NORMAL);
}

void AnimatedStuff::draw(){
    ofSetColor(0);
    ofRect(drawOffset, drawW, drawH);
    
    ofPushMatrix();
    ofSetColor(255);
    
    ofTranslate(drawOffset);
    ofScale(drawW, drawH);
    
    for (int i =0 ; i<polylines.size(); i++) {
        polylines[i].draw();
    }
    
    ofPopMatrix();
}

void AnimatedStuff::drawTimeline(){
    if (isSelected){
        timeline.draw();
        gui->draw();
    }
}

void AnimatedStuff::setName(string newName){
    name = newName;
    timeline.setName(name);
    timeline.setPageName(name);
    gui->setName(name);
}

void AnimatedStuff::load(){
    cout<<"loading animated stuff "<<name<<endl;
    
    gui->loadSettings(name+"_gui.xml");
    timeline.loadTracksFromFolder(ofToDataPath(""));
}

void AnimatedStuff::save(){
    cout<<"saving animated stuff "<<name<<endl;
    timeline.save();
    gui->saveSettings(name+"_gui.xml");
}

void AnimatedStuff::play(){
    timeline.play();
}

void AnimatedStuff::togglePlay(){
    timeline.togglePlay();
}

void AnimatedStuff::stop(){
    timeline.stop();
}

void AnimatedStuff::clear(){
    timeline.clear();
}

void AnimatedStuff::setLoop(ofLoopType loop){
    timeline.setLoopType(loop);
}

void AnimatedStuff::setDrawWidth(int w){
    drawW = w;
}

void AnimatedStuff::setDrawHeight(int h){
    drawH = h;
}

void AnimatedStuff::setDrawOffset(ofVec2f offset){
    drawOffset = offset;
}


void AnimatedStuff::setTlWidth(int w){
    timeline.setWidth(w);
}

void AnimatedStuff::setTlHeight(int h){
    timeline.setHeight(h);
}

void AnimatedStuff::setTlOffset(ofVec2f offset){
    timeline.setOffset(offset);
}

void AnimatedStuff::setSelected(bool selected){
    isSelected = selected;
    if (isSelected) {
        gui->enable();
        timeline.enableEvents();
        ofRegisterMouseEvents(this);
    }else{
        gui->disable();
        timeline.disableEvents();
        ofUnregisterMouseEvents(this);
    }
}

void AnimatedStuff::setGuiOffset(ofVec2f offset){
    gui->setPosition(offset.x, offset.y);
    gui->setHeight(ofGetHeight()-offset.y-150);
    cout<<"anim gui offset "<<offset.x<<", "<<offset.y<<endl;
}

void AnimatedStuff::setCurrentTime(unsigned long long time){
    timeline.setCurrentTimeMillis(time);
}

void AnimatedStuff::setTimeLength(long time){
    timeline.setDurationInMillis(time);
}
