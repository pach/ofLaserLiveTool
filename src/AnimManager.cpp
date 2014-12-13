//
//  AnimManager.cpp
//  LaserAnimTool
//
//  Created by pach on 29/05/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#include "AnimManager.h"
#include "ofxUI.h"

#include "ofxTimeline.h"
#include "ofxTLAudioTrack.h"

#include "ofxXmlSettings.h"

#include "AnimatedPolyline.h"
#include "AnimatedSinus.h"
#include "AnimatedRect.h"
#include "AnimatedMultiline.h"
#include "AnimatedPerlinLines.h"
#include "AnimatedRibbon.h"

AnimManager::AnimManager(){
    curSelected = NULL;
}

AnimManager::~AnimManager(){
    delete gui;
}

void AnimManager::setup() {
    
    gui = new ofxUISuperCanvas("Anim Manager");
    timeline.setup();
    timeline.setDurationInSeconds(600);
    timeline.setLoopType(OF_LOOP_NORMAL);
    
    nbLayer = 2;
    
    
//    timeline.addAudioTrack("Audio","audio/hyperlight.wav");
    
    for (int i=0; i<nbLayer; i++) {
        timeline.addSwitches("layer"+ofToString(i+1));
    }
    
    
    ofAddListener(timeline.events().switched, this, &AnimManager::animFired);
    ofAddListener(timeline.events().trackGainedFocus, this, &AnimManager::trackGainFocused);
    ofAddListener(timeline.events().trackLostFocus, this, &AnimManager::trackLostFocused);
    
    ofAddListener(ofEvents().mouseReleased, this, &AnimManager::hasClicked);
    
    setupGui();
    
    load ();
    
    curTrackSelected = NULL;
    
//    timeline.play();
}

void AnimManager::load(){
    setupAnimatedList();
    gui->loadSettings("manager.xml");
//    timeline.load();
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
    timeline.save();
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
    
//    AnimatedStuff * anim = new AnimatedPolyline ();
//    anim->setup("poly1");
//    allAnims.push_back(anim);
//    animName.push_back(anim->getName());
//    
//    anim = new AnimatedMultiline();
//    anim->setup("poly2");
//    allAnims.push_back(anim);
//    animName.push_back(anim->getName());
//    
//    anim = new AnimatedSinus();
//    anim->setup("sinus1");
//    allAnims.push_back(anim);
//    animName.push_back(anim->getName());
//    
//    anim = new AnimatedSinus();
//    anim->setup("sinus2");
//    allAnims.push_back(anim);
//    animName.push_back(anim->getName());
//    
//    anim = new AnimatedRect();
//    anim->setup("rect1");
//    allAnims.push_back(anim);
//    animName.push_back(anim->getName());
    
}

void AnimManager::setupGui(){
    // setup gui list
    gui->addSpacer();
    newAnimBool = false;
    gui->addButton("add Polyline", newAnimBool);
    gui->addButton("add Multiline", newAnimBool);
    gui->addButton("add Sinus", newAnimBool);
    gui->addButton("add Rect", newAnimBool);
    gui->addButton("add Perlin", newAnimBool);
    gui->addButton("add Ribbon", newAnimBool);
    
    gui->addSpacer();
    ofxUIDropDownList *ddl = gui->addDropDownList("animation list", animName);
    ddl->setAllowMultiple(false);
    
    
    ofAddListener(gui->newGUIEvent, this, &AnimManager::guiEvent);

}

void AnimManager::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    if (!newAnimBool){
        if (name == "add Polyline"){
            createNewAnimationWithTextbox("AnimatedPolyline");
        }
        else if (name == "add Sinus"){
            createNewAnimationWithTextbox("AnimatedSinus");
        }
        else if (name == "add Rect"){
            createNewAnimationWithTextbox("AnimatedRect");
        }
        else if (name == "add Multiline"){
            createNewAnimationWithTextbox("AnimatedMultiline");
        }
        else if (name == "add Perlin"){
            createNewAnimationWithTextbox("AnimatedPerlin");
        }
        else if (name == "add Ribbon"){
            createNewAnimationWithTextbox("AnimatedRibbon");
        }
    }
    newAnimBool = false;
//   if(name == "animation list")
//    {
//        ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
//        vector<ofxUIWidget *> &selected = ddlist->getSelected();
//        
//        activeAnims.clear();
//        if (curSelected != NULL){
//            curSelected->setSelected(false);
//            curSelected->setTimelineActive(false);
//        }
//        curSelected = NULL;
//        
//        for(int i = 0; i < selected.size(); i++)
//        {
//            vector<AnimatedStuff* >::iterator it = allAnims.begin();
//            vector<AnimatedStuff* >::iterator itEnd = allAnims.end();
//            bool found = false;
//            
//            while (!found && it!= itEnd) {
//                if ((*it)->getName() == selected[i]->getName()){
//                    found = true;
//                    activeAnims.push_back(*it);
//                    curSelected = *it;
//                    curSelected->setSelected(true);
//                    curSelected->setTimelineActive(true);
//                }
//                it++;
//            }
//        }
//    }
}

void AnimManager::createNewAnimationWithTextbox(string type){
    string name = ofSystemTextBoxDialog(type+" name?");
    createNewAnimation(type, name);
}

void AnimManager::createNewAnimation(string type, string name){
    
    if (name != ""){
        AnimatedStuff *a;
        if (type == "AnimatedPolyline") {
            a = new AnimatedPolyline();
            a->setup(name);
        }
        else if (type == "AnimatedSinus") {
            a = new AnimatedSinus();
            a->setup(name);
        }
        else if (type == "AnimatedRect") {
            a = new AnimatedRect();
            a->setup(name);
        }
        else if (type == "AnimatedMultiline") {
            a = new AnimatedMultiline();
            a->setup(name);
        }
        else if (type == "AnimatedPerlin") {
            a = new AnimatedPerlinLines();
            a->setup(name);
        }
        else if (type == "AnimatedRibbon") {
            a = new AnimatedRibbon();
            a->setup(name);
        }
        a->setDrawWidth(drawW);
        a->setDrawHeight(drawH);
        a->setDrawOffset(drawOffset);
        a->setTlWidth(timeline.getWidth());
        a->setTlHeight(timeline.getHeight());
        a->setTlOffset(guiOffset+ofVec2f(gui->getRect()->getWidth(),timeline.getHeight()));
        allAnims.push_back(a);
        animName.push_back(name);
        
        // update animName gui menu
        ofxUIDropDownList *w = (ofxUIDropDownList *)gui->getWidget("animation list");
        w->addToggle(name);
        
        cout<<"create new anim "<<name<<" of type "<<type<<endl;
    }
}

void AnimManager::animFired(ofxTLSwitchEventArgs& args){
    string animName = args.switchName;
    bool state = args.on;
    ofxTLTrack * t = args.track;
    
    if (t->getName() == "layer1"){
        if (state){
            addActiveAnim(1, animName);
        }
        else{
            removeActiveAnim(1);
        }
    } else if (t->getName() == "layer2"){
        if (state){
            addActiveAnim(2, animName);
        }
        else{
            removeActiveAnim(2);
        }
    }
    cout<<animName<<" is "<<ofToString(state)<<" from layer "<<t->getName()<<endl;
}

void AnimManager::trackGainFocused(ofxTLTrackEventArgs &args){
    string trackName = args.name;
    curTrackSelected = dynamic_cast<ofxTLSwitches*>(args.track);
    cout<<"track "<<trackName<<" just gain focus "<<endl;
}

void AnimManager::trackLostFocused(ofxTLTrackEventArgs &args){
    string trackName = args.name;
    if (curTrackSelected != NULL && curTrackSelected->getName() == args.name) {
        curTrackSelected = NULL;
    }
    
    cout<<"track "<<trackName<<" just lost focus "<<endl;

}

void AnimManager::hasClicked(ofMouseEventArgs &e){
    updateSelected = true;
}

void AnimManager::addAnimatedPoly(){
    
}

void AnimManager::setCurrentSelected(string name){
    if (curSelected != NULL){
        curSelected->toggleSelected();
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
}

void AnimManager::addActiveAnim(int trackId, string name){
    removeActiveAnim(trackId);
    
    vector<AnimatedStuff*>::iterator it = allAnims.begin();
    vector<AnimatedStuff*>::iterator itEnd = allAnims.end();
    bool found = false;
    
    while (!found && it!=itEnd) {
        if ((*it)->getName() == name) {
            found = true;
            activeAnims.insert(pair<int, AnimatedStuff*>(trackId, *it));
            (*it)->start();
        }
        it++;
    }
}

void AnimManager::removeActiveAnim(int trackId){
    map<int, AnimatedStuff*>::iterator itActive = activeAnims.find(trackId);
    if (itActive != activeAnims.end()){
        activeAnims.erase(itActive);
    }
}

void AnimManager::update() {
    if (updateSelected && curTrackSelected != NULL){
        // check if a new item has been selected
        ofxTLSwitch * selectedItem = curTrackSelected->getActiveSwitchAtMillis(curTrackSelected->getLatestSelectedTime());
        if (selectedItem != NULL){
            cout<<"item "<<selectedItem->textField.text<<" from track "<<curTrackSelected->getName()<<" is selected"<<endl;
            setCurrentSelected(selectedItem->textField.text);
        }
        
        // check time of all items and update according to switches time
        vector <ofxTLKeyframe*> kf = curTrackSelected->getKeyframes();
        vector <ofxTLKeyframe*>::iterator it = kf.begin();
        vector <ofxTLKeyframe*>::iterator itEnd = kf.end();
        ofxTLSwitch * sw = NULL;
        vector<AnimatedStuff*>::iterator itAnim = allAnims.begin();
        vector<AnimatedStuff*>::iterator itAnimEnd = allAnims.end();
        
        while (it != itEnd){
            sw = static_cast<ofxTLSwitch *>(*it);
            if (sw != NULL) {
                long timeLength = sw->timeRange.max - sw->timeRange.min;
                string name = sw->textField.text;
                cout<<name <<" time is "<<sw->timeRange<<" length "<<timeLength<<endl;
                
                itAnim = allAnims.begin();
                bool found = false;
                while (itAnim != itAnimEnd) {
                    if ((*itAnim)->getName() == name){
                        found = true;
                        (*itAnim)->setTimeLength(timeLength);
                    }
                    itAnim ++;
                }
            }
            
            it++;
        }
        
        updateSelected = false;
    }
    
    itActive = activeAnims.begin();
    itActiveEnd = activeAnims.end();
    
    while (itActive != itActiveEnd) {
        itActive->second->update();
        itActive ++;
    }
    
    // set time for each active anim
    unsigned long long curTime = timeline.getCurrentTimeMillis();
    ofxTLSwitches* t ;
    ofxTLSwitch* s;
    for (int i=0 ; i<nbLayer; i++){
        t = dynamic_cast<ofxTLSwitches*>(timeline.getTrack("layer"+ofToString(i+1)));
        if (t != NULL){
            s = dynamic_cast<ofxTLSwitch*>(t->getActiveSwitchAtMillis(curTime));
            if (s!=NULL){
                unsigned long long startTime = s->time;
                string name = s->textField.text;
                
                map<int, AnimatedStuff*>::iterator animIt = activeAnims.find(i+1);
                if (animIt != activeAnims.end()) {
                    animIt->second->setCurrentTime(curTime-startTime);
                }
                
            }
        }
    }
    
//    if (curSelected != NULL){
//        curSelected->update();
//    }
}

void AnimManager::draw() {
    gui->draw();
    timeline.draw();
    
    if (curSelected != NULL){
        curSelected->draw();
        curSelected->drawTimeline();
    }
}

void AnimManager::play(){
    timeline.play();
}

void AnimManager::togglePlay(){
   
    if (!isTimelineActive){
        timeline.play();
    }else{
        timeline.stop();
    }
    isTimelineActive = !isTimelineActive;
    
//    timeline.togglePlay();
    
//    for (int i=0; i<allAnims.size(); i++) {
//        allAnims[i]->togglePlay();
//    }
}

void AnimManager::stop(){
    timeline.stop();
    for (int i=0; i<allAnims.size(); i++) {
        allAnims[i]->stop();
    }
}

void AnimManager::clear(){
    timeline.clear();
}

void AnimManager::setLoop(ofLoopType loop){
    timeline.setLoopType(loop);
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

void AnimManager::setTlWidth(int w){
    timeline.setWidth(w);
    for (int i=0; i<allAnims.size(); i++) {
        allAnims[i]->setTlWidth(w);
    }
}

void AnimManager::setTlHeight(int h){
    timeline.setHeight(h);
}

void AnimManager::setTlOffset(ofVec2f offset){
    timeline.setOffset(guiOffset+ofVec2f(gui->getRect()->getWidth(), 0.));
    // update offset pour chaque sous anim
    for (int i=0; i<allAnims.size(); i++) {
        allAnims[i]->setTlOffset(guiOffset+ofVec2f(gui->getRect()->getWidth(),timeline.getHeight()));
    }
}

void AnimManager::setGuiOffset(ofVec2f offset){
    guiOffset = offset;
    gui->setPosition(offset.x, offset.y);
    
    // update offset pour chaque sous anim
    for (int i=0; i<allAnims.size(); i++) {
        allAnims[i]->setGuiOffset(offset+ofVec2f(0., gui->getRect()->getHeight()));
    }
    
    cout<<"gui offset "<<guiOffset.x<<", "<<guiOffset.y<<endl;
}

vector<ofPolyline> AnimManager::getPolylines(){
    vector<ofPolyline> polys;
    itActive = activeAnims.begin();
    itActiveEnd = activeAnims.end();
    
    vector<ofPolyline>::iterator itT ;
    vector<ofPolyline>::iterator itEndT ;
    vector<ofPolyline> polytemp;
    
    while (itActive != itActiveEnd) {
        polytemp = itActive->second->getPolylines();
        itT = polytemp.begin();
        itEndT = polytemp.end();
        while (itT != itEndT) {
            polys.push_back((*itT));
            itT ++;
        }
        itActive ++;
    }
    
    return polys;
}