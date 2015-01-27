//
//  AnimManager.cpp
//  LaserAnimTool
//
//  Created by pach on 29/05/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#include "AnimManager.h"
#include "ofxUI.h"

//#include "ofxTimeline.h"
//#include "ofxTLAudioTrack.h"

#include "ofxXmlSettings.h"

#include "Utils.h"

//#include "AnimatedPolyline.h"
#include "AnimatedSinus.h"
#include "AnimatedMultiSinus.h"
#include "AnimatedMultiSin2.h"
#include "AnimatedRect.h"
//#include "AnimatedMultiline.h"
#include "AnimatedPerlinLines.h"
#include "AnimatedRibbon.h"
#include "AnimatedSvg.h"
#include "AnimatedLines.h"
#include "AnimatedCircle.h"
#include "AnimatedOSCLines.h"
#include "AnimatedOSCPolylines.h"

#include "AnimatedSvg.h"
#include "AnimatedImacStraw.h"
#include "AnimatedSinusRibbon.h"
#include "AnimatedSpiral.h"

AnimManager::AnimManager(){
    curSelected = NULL;
}

AnimManager::~AnimManager(){
    delete gui;
}

void AnimManager::setup() {
    
    gui = new ofxUISuperCanvas("Anim Manager");
    
    curSelected = NULL;
    lastSelected = NULL;
    
    animName.push_back("none");
    
    fadeTime = 2.;
    isFading = false;
    
    setupGui();
    
    load ();
    
    animUIselectEvent = false;
    
    
}

void AnimManager::load(){
    setupAnimatedList();
    gui->loadSettings("manager.xml");
}

void AnimManager::save(){
    vector<AnimatedStuff*>::iterator it = allAnims.begin();
    vector<AnimatedStuff*>::iterator itEnd = allAnims.end();
    
    ofxXmlSettings xml;
    xml.addTag("ANIMATIONS");
    xml.pushTag("ANIMATIONS");
    int idTag = 0;
    while (it != itEnd) {
        xml.addTag("animList");
        xml.pushTag("animList", idTag);
            xml.addValue("name", (*it)->getName());
            xml.addValue("type", (*it)->getType());
        xml.popTag();
        idTag ++;
        
        (*it)->save();
        it++;
    }
    
    xml.popTag();
    
    xml.save("anim.xml");
    gui->saveSettings("manager.xml");
}

void AnimManager::setupAnimatedList(){
    
    ofxXmlSettings xml;
    xml.load("anim.xml");
    
    xml.pushTag("ANIMATIONS");
    
    int numTag = xml.getNumTags("animList");
    
    for (int i=0; i<numTag; i++) {
        xml.pushTag("animList", i);
        string name = xml.getValue("name", "noName"+ofToString(i));
        string type = xml.getValue("type", "noType"+ofToString(i));
        
        cout<< "load animation "<<name<< " of type "<<type<<endl;
        
        createNewAnimation(type, name);
        
        xml.popTag();
    }
    
}

void AnimManager::setupGui(){
    // setup gui list
    gui->addSpacer();
    gui->addSlider("fade time", 0., 20., &fadeTime);
    gui->addSpacer();
    newAnimBool = false;
    gui->addButton("add SVG", newAnimBool);
//    gui->addButton("add Polyline", newAnimBool);
//    gui->addButton("add Multiline", newAnimBool);
    gui->addButton("add Sinus", newAnimBool);
    gui->addButton("add MultiSinus", newAnimBool);
    gui->addButton("add MultiSinus2", newAnimBool);
    gui->addButton("add Rect", newAnimBool);
    gui->addButton("add Perlin", newAnimBool);
    gui->addButton("add Ribbon", newAnimBool);
    gui->addButton("add Sinus Ribbon", newAnimBool);
    gui->addButton("add lines", newAnimBool);
    gui->addButton("add circle", newAnimBool);
    gui->addButton("add osc lines", newAnimBool);
    gui->addButton("add osc multilines", newAnimBool);
    gui->addButton("add imac straws", newAnimBool);
    gui->addButton("add spiral", newAnimBool);
    gui->addSpacer();
    
//    gui->addRadio("anim list", animName, OFX_UI_ORIENTATION_VERTICAL);
    ofxUIDropDownList *ddl = gui->addDropDownList("anim list", animName);
    ddl->setAllowMultiple(false);
    
    gui->setHeight(ofGetWindowHeight());
    
    ofAddListener(gui->newGUIEvent, this, &AnimManager::guiEvent);

}

void AnimManager::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    if (!newAnimBool){
//        if (name == "add Polyline"){
//            createNewAnimationWithTextbox("AnimatedPolyline");
//        }
        if (name == "add Sinus"){
            createNewAnimationWithTextbox("AnimatedSinus");
        }
        else if (name == "add MultiSinus"){
            createNewAnimationWithTextbox("AnimatedMultiSinus");
        }
        else if (name == "add MultiSinus2"){
            createNewAnimationWithTextbox("AnimatedMultiSinus2");
        }
        else if (name == "add Rect"){
            createNewAnimationWithTextbox("AnimatedRect");
        }
//        else if (name == "add Multiline"){
//            createNewAnimationWithTextbox("AnimatedMultiline");
//        }
        else if (name == "add Perlin"){
            createNewAnimationWithTextbox("AnimatedPerlin");
        }
        else if (name == "add Ribbon"){
            createNewAnimationWithTextbox("AnimatedRibbon");
        }
        else if (name == "add Sinus Ribbon"){
            createNewAnimationWithTextbox("AnimatedSinusRibbon");
        }
        else if (name == "add SVG"){
            createNewAnimationWithTextbox("AnimatedSvg");
        }
        else if (name == "add lines"){
            createNewAnimationWithTextbox("AnimatedLines");
        }
        else if (name == "add circle"){
            createNewAnimationWithTextbox("AnimatedCircle");
        }
        else if (name == "add osc lines"){
            createNewAnimationWithTextbox("AnimatedOSCLines");
        }
        else if (name == "add osc multilines"){
            createNewAnimationWithTextbox("AnimatedOSCPolylines");
        }
        else if (name == "add imac straws"){
            createNewAnimationWithTextbox("AnimatedImacStraw");
        }
        else if (name == "add spiral"){
            createNewAnimationWithTextbox("AnimatedSpiral");
        }
        else if (name == "anim list"){
            animUIselectEvent = true;
            cout<<"select a new animation"<<endl;
        }
        newAnimBool = false;
    }
    if (animUIselectEvent && name != "anim list") {
        setCurrentSelected(name);
//        addActiveAnim(1, name);
        
        cout<<" run animation "<<name<<endl;
        
        animUIselectEvent = false;
    }
    
}

void AnimManager::createNewAnimationWithTextbox(string type){
    string name = ofSystemTextBoxDialog(type+" name?");
    createNewAnimation(type, name);
}

void AnimManager::createNewAnimation(string type, string name){
    
    if (name != ""){
        AnimatedStuff *a;
//        if (type == "AnimatedPolyline") {
//            a = new AnimatedPolyline();
//            a->setup(name);
//        }
        if (type == "AnimatedSinus") {
            a = new AnimatedSinus();
            a->setup(name);
        }
        else if (type == "AnimatedMultiSinus") {
            a = new AnimatedMultiSinus();
            a->setup(name);
        }
        else if (type == "AnimatedMultiSinus2") {
            a = new AnimatedMultiSin2();
            a->setup(name);
        }
        else if (type == "AnimatedRect") {
            a = new AnimatedRect();
            a->setup(name);
        }
//        else if (type == "AnimatedMultiline") {
//            a = new AnimatedMultiline();
//            a->setup(name);
//        }
        else if (type == "AnimatedPerlin") {
            a = new AnimatedPerlinLines();
            a->setup(name);
        }
        else if (type == "AnimatedRibbon") {
            a = new AnimatedRibbon();
            a->setup(name);
        }
        else if (type == "AnimatedSinusRibbon") {
            a = new AnimatedSinusRibbon();
            a->setup(name);
        }
        else if (type == "AnimatedSvg") {
            a = new AnimatedSvg();
            a->setup(name);
        }
        else if (type == "AnimatedLines") {
            a = new AnimatedLines();
            a->setup(name);
        }
        else if (type == "AnimatedCircle") {
            a = new AnimatedCircle();
            a->setup(name);
        }
        else if (type == "AnimatedOSCLines") {
            a = new AnimatedOSCLines();
            a->setup(name);
        }
        else if (type == "AnimatedOSCPolylines") {
            a = new AnimatedOSCPolylines();
            a->setup(name);
        }
        else if (type == "AnimatedImacStraw") {
            a = new AnimatedImacStraw();
            a->setup(name);
        }
        else if (type == "AnimatedSpiral") {
            a = new AnimatedSpiral();
            a->setup(name);
        }

        a->setDrawWidth(drawW);
        a->setDrawHeight(drawH);
        a->setDrawOffset(drawOffset);
//        a->setTlOffset(guiOffset+ofVec2f(gui->getRect()->getWidth(),0));
        allAnims.push_back(a);
        animName.push_back(name);
        
        // update animName gui menu
        ofxUIDropDownList *w = (ofxUIDropDownList *)gui->getWidget("anim list");
        w->addToggle(name);
        
        /* to update radio group, doesn't work*/
//        ofxUIRadio *r = (ofxUIRadio *)gui->getWidget("anim list");
//        ofxUIToggle *toggle = new ofxUIToggle(name, false, r->getRect()->getWidth(), r->getRect()->getHeight());
//        r->addEmbeddedWidget(toggle);
//        r->addToggle(toggle);
//        r->setVisible(true);
//        r->getRect()->setHeight(500);
//        r->calculatePaddingRect();
//        r->stateChange();
////        gui->autoSizeToFitWidgets();
//        gui->stateChange();
        
        cout<<"create new anim "<<name<<" of type "<<type<<endl;
//        vector<ofxUIToggle *> tg =r->getToggles();
//        for (int i=0 ; i<tg.size() ; i++){
//                    cout<<"radio : "<<tg[i]->getName()<<endl;
//        }

    }
}

void AnimManager::hasClicked(ofMouseEventArgs &e){

}

void AnimManager::setCurrentSelected(string name){
    if (curSelected != NULL){
        curSelected->toggleSelected();
        lastSelected = curSelected;
        curSelected = NULL;
    }
    
    
    vector<AnimatedStuff*>::iterator it = allAnims.begin();
    vector<AnimatedStuff*>::iterator itEnd = allAnims.end();
    bool found = false;
    
    while (!found && it!=itEnd) {
        if ((*it)->getName() == name) {
            found = true;
            curSelected = *it;
            curSelected->toggleSelected();
        }
        it++;
    }
    
    // start fading
    isFading = true;
    fadeStartTime = ofGetElapsedTimef();
    polysMerger.clear();
    ofxPolylineMerger p;
    p.setup();
    ofPolyline popo ;
    popo.addVertex(ofPoint(0.5, 0.5));
    popo.addVertex(ofPoint(0.5, 0.5));
    
    if(curSelected!=NULL){
        curSelected->update();
        p.setPoly1(curSelected->getPolylines()[0]);
    }else{
        p.setPoly1(popo);
    }
    if (lastSelected != NULL) {
        p.setPoly2(lastSelected->getPolylines()[0]);
    }else{
        p.setPoly2(popo);
    }

    polysMerger.push_back(p);
}

void AnimManager::update() {
    if (curSelected != NULL)
        curSelected->update();
    
    if (lastSelected != NULL){
        lastSelected -> update();
    }
    
    polys.clear() ;
    
    if (!isFading) {
        if (curSelected != NULL) {
            polys = curSelected->getPolylines();
        }

    }
    else{
        fadeCurrentTime = ofGetElapsedTimef()-fadeStartTime;
        if (fadeCurrentTime>fadeTime) {
            isFading = false;
            lastSelected = NULL;
            if (curSelected != NULL){
                polys = curSelected->getPolylines();
            }
        }
        else{
            
            if(curSelected!=NULL){
                polysMerger[0].setPoly2(curSelected->getPolylines()[0]);
            }
            if (lastSelected != NULL) {
                polysMerger[0].setPoly1(lastSelected->getPolylines()[0]);
            }
            
            polysMerger[0].mergePolyline(fadeCurrentTime/fadeTime);
            polys.push_back(polysMerger[0].getPolyline());
            
//            for (int i=0; i<polysMerger.size(); i++) {
//                if (curSelected != NULL && curSelected->getPolylines().size()>i) {
//                    polysMerger[i].setPoly1(curSelected->getPolylines()[i]);
//                }
//                if (lastSelected != NULL && lastSelected->getPolylines().size()>i) {
//                    polysMerger[i].setPoly2(lastSelected->getPolylines()[i]);
//                }
//                
//                polysMerger[i].mergePolyline(fadeCurrentTime/fadeTime);
//                
//                polys.push_back(polysMerger[i].getPolyline());
//            }
        }
    }
    
}

void AnimManager::draw() {
    gui->draw();
    
    ofSetColor(0);
    ofRect(drawOffset, drawW, drawH);
    
    if(isFading){
        
        ofPushMatrix();
        ofSetColor(255);
        
        ofTranslate(drawOffset);
        ofScale(drawW, drawH);
        
        ofSetColor(255, 0, 0);
        if (curSelected != NULL){
            curSelected->getPolylines()[0].draw();
        }
        ofSetColor(0, 255, 0);
        if (lastSelected != NULL){
            lastSelected->getPolylines()[0].draw();
        }
        ofSetColor(255, 255, 0);
        polysMerger[0].getPolyline().draw();
        
        ofPopMatrix();
        
    }
    else {
        if (curSelected != NULL){
            curSelected->draw();
        }
    }
}

void AnimManager::setDrawWidth(int w){
    drawW = w;
    for (int i=0; i<allAnims.size(); i++) {
        allAnims[i]->setDrawWidth(w);
    }
}

void AnimManager::setDrawHeight(int h){
    drawH = h;
    for (int i=0; i<allAnims.size(); i++) {
        allAnims[i]->setDrawHeight(h);
    }
    
}

void AnimManager::setDrawOffset(ofVec2f offset){
    drawOffset = offset;
    // update offset pour chaque sous anim
    for (int i=0; i<allAnims.size(); i++) {
        allAnims[i]->setDrawOffset(offset);//+ofVec2f(0., gui->getRect()->getHeight()));
    }
}

void AnimManager::setGuiOffset(ofVec2f offset){
    guiOffset = offset;
    gui->setPosition(offset.x, offset.y);
    
    // update offset pour chaque sous anim
    for (int i=0; i<allAnims.size(); i++) {
        allAnims[i]->setGuiOffset(offset+ofVec2f(gui->getRect()->x + 10., 0.));
    }
    
    cout<<"gui offset "<<guiOffset.x<<", "<<guiOffset.y<<endl;
}

vector<ofPolyline> AnimManager::getPolylines(){
    return polys;
}

void AnimManager::parseOSC(ofxOscMessage &m){
    vector<string> osc = getOSCcmd(m.getAddress());
    string cmd = osc[0];
    string msg = osc[1];
    
    if (cmd == "layer1"){
        m.setAddress(msg);
        if (curSelected != NULL){
            curSelected->parseOSC(m);
        }
    }
    
    
}