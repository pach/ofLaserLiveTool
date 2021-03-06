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
#include "AnimatedMultiSvg.h"
#include "AnimatedLines.h"
#include "AnimatedCircle.h"
#include "AnimatedWalls.h"
#include "AnimatedOSCLines.h"
#include "AnimatedOSCPolylines.h"
#include "AnimatedPointsInALine.h"
#include "AnimatedRain.h"
#include "AnimatedSoundWave.h"
#include "AnimatedRegularPolygon.h"

#include "AnimatedSvg.h"
#include "AnimatedImacStraw.h"
#include "AnimatedSinusRibbon.h"
#include "AnimatedSpiral.h"
#include "AnimatedRing.h"
#include "AnimatedSolid.h"
#include "AnimatedPerlinCircle.h"

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
    
    color = ofFloatColor(1.);
    
    animName.push_back("none");
    
    fadeTime = 2.;
    isFading = false;
    
    setupGui();
    
//    load ();
    
    animUIselectEvent = false;
    
    name = "layer.0";
    
    polys.clear();
    polyColors.clear();
    
//    rotate = 0;
    
}

void AnimManager::setName(string newName){
    name = newName;
    gui->setName(name);
    gui->addLabel(name);
}

void AnimManager::load(){
    setupAnimatedList();
    gui->loadSettings(name+".xml");
}

void AnimManager::save(){
    vector<AnimatedStuff*>::iterator it = allAnims.begin();
    vector<AnimatedStuff*>::iterator itEnd = allAnims.end();
    
    // check si folder existe, le crée sinon
    ofDirectory curDir;
    if (!curDir.doesDirectoryExist(name)){
        curDir.createDirectory(name);
        
    }
    
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
        
        (*it)->save(name);
        it++;
    }
    
    xml.popTag();
    
    xml.save("anim.xml");
    gui->saveSettings(name+".xml");
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
    gui->add2DPad("pos", ofxUIVec2f(0., 1), ofxUIVec2f(0., 1), &offset);
    gui->add2DPad("scale", ofxUIVec2f(0., 1), ofxUIVec2f(0., 1), &scale);
    
//    gui->addSlider("rotate", 0., 1., &rotate);
    gui->addSpacer();
    gui->addSlider("red", 0, 1, &color.r);
    gui->addSlider("green", 0, 1, &color.g);
    gui->addSlider("blue", 0, 1, &color.b);
//    gui->addSlider("alpha", 0, 1, &color.a);
    
    newAnimBool = false;
//    gui->addButton("add SVG", newAnimBool);
////    gui->addButton("add Polyline", newAnimBool);
////    gui->addButton("add Multiline", newAnimBool);
//    gui->addButton("add Sinus", newAnimBool);
//    gui->addButton("add MultiSinus", newAnimBool);
//    gui->addButton("add MultiSinus2", newAnimBool);
//    gui->addButton("add Rect", newAnimBool);
//    gui->addButton("add Perlin", newAnimBool);
//    gui->addButton("add Ribbon", newAnimBool);
//    gui->addButton("add Sinus Ribbon", newAnimBool);
//    gui->addButton("add lines", newAnimBool);
//    gui->addButton("add circle", newAnimBool);
//    gui->addButton("add osc lines", newAnimBool);
//    gui->addButton("add osc multilines", newAnimBool);
//    gui->addButton("add imac straws", newAnimBool);
//    gui->addButton("add spiral", newAnimBool);
//    gui->addButton("add walls", newAnimBool);
//    gui->addButton("add points in line", newAnimBool);
//    gui->addButton("add rain", newAnimBool);
//    gui->addButton("add sound wave", newAnimBool);
//    gui->addSpacer();
    
//    gui->addRadio("anim list", animName, OFX_UI_ORIENTATION_VERTICAL);
    ofxUIDropDownList *ddl = gui->addDropDownList("anim list", animName);
    ddl->setAllowMultiple(false);
    
    gui->setHeight(ofGetWindowHeight());
    
    ofAddListener(gui->newGUIEvent, this, &AnimManager::guiEvent);
    
    gui->setVisible(false);

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
        else if (name == "add SVG multi"){
            createNewAnimationWithTextbox("AnimatedMultiSvg");
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
            createNewAnimationWithTextbox("AnimatedOSCMultilines");
        }
        else if (name == "add imac straws"){
            createNewAnimationWithTextbox("AnimatedImacStraw");
        }
        else if (name == "add spiral"){
            createNewAnimationWithTextbox("AnimatedSpiral");
        }
        else if (name == "add walls"){
            createNewAnimationWithTextbox("AnimatedWalls");
        }
        else if (name == "add points in line"){
            createNewAnimationWithTextbox("AnimatedPointsInALine");
        }
        else if (name == "add rain"){
            createNewAnimationWithTextbox("AnimatedRain");
        }
        else if (name == "add sound wave"){
            createNewAnimationWithTextbox("AnimatedSoundWave");
        }
        else if (name == "add ring"){
            createNewAnimationWithTextbox("AnimatedRing");
        }
        else if (name == "add solid"){
            createNewAnimationWithTextbox("AnimatedSolid");
        }
        else if (name == "add perlinCircle"){
            createNewAnimationWithTextbox("AnimatedPerlinCircle");
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

void AnimManager::createNewAnimation(string type, string aName){
    
    if (aName != ""){
//        aName = name+"."+aName;
        
        AnimatedStuff *a = NULL;
//        if (type == "AnimatedPolyline") {
//            a = new AnimatedPolyline();
//            a->setup(name);
//        }
        if (type == "AnimatedSinus") {
            a = new AnimatedSinus();
            a->setup(aName);
        }
        else if (type == "AnimatedMultiSinus") {
            a = new AnimatedMultiSinus();
            a->setup(aName);
        }
        else if (type == "AnimatedMultiSinus2") {
            a = new AnimatedMultiSin2();
            a->setup(aName);
        }
        else if (type == "AnimatedRect") {
            a = new AnimatedRect();
            a->setup(aName);
        }
//        else if (type == "AnimatedMultiline") {
//            a = new AnimatedMultiline();
//            a->setup(aName);
//        }
        else if (type == "AnimatedPerlin") {
            a = new AnimatedPerlinLines();
            a->setup(aName);
        }
        else if (type == "AnimatedRibbon") {
            a = new AnimatedRibbon();
            a->setup(aName);
        }
        else if (type == "AnimatedSinusRibbon") {
            a = new AnimatedSinusRibbon();
            a->setup(aName);
        }
        else if (type == "AnimatedSvg") {
            a = new AnimatedSvg();
            a->setup(aName);
        }
        else if (type == "AnimatedMultiSvg") {
            a = new AnimatedMultiSvg();
            a->setup(aName);
        }
        else if (type == "AnimatedLines") {
            a = new AnimatedLines();
            a->setup(aName);
        }
        else if (type == "AnimatedCircle") {
            a = new AnimatedCircle();
            a->setup(aName);
        }
        else if (type == "AnimatedOSCLines") {
            a = new AnimatedOSCLines();
            a->setup(aName);
        }
        else if (type == "AnimatedOSCMultilines") {
            a = new AnimatedOSCPolylines();
            a->setup(aName);
        }
        else if (type == "AnimatedImacStraw") {
            a = new AnimatedImacStraw();
            a->setup(aName);
        }
        else if (type == "AnimatedSpiral") {
            a = new AnimatedSpiral();
            a->setup(aName);
        }
        else if (type == "AnimatedWalls") {
            a = new AnimatedWalls();
            a->setup(aName);
        }
        else if (type == "AnimatedPointsInALine") {
            a = new AnimatedPointsInALine();
            a->setup(aName);
        }
        else if (type == "AnimatedRain") {
            a = new AnimatedRain();
            a->setup(aName);
        }
        else if (type == "AnimatedRegularPolygon") {
            a = new AnimatedRegularPolygon();
            a->setup(aName);
        }
        else if (type == "AnimatedSoundWave") {
            a = new AnimatedSoundWave();
            a->setup(aName);
        }
        else if (type == "AnimatedRing") {
            a = new AnimatedRing();
            a->setup(aName);
        }
        else if (type == "AnimatedSolid") {
            a = new AnimatedSolid();
            a->setup(aName);
        }
        else if (type == "AnimatedPerlinCircle") {
            a = new AnimatedPerlinCircle();
            a->setup(aName);
        }

        if (a != NULL){
            a->setDrawWidth(drawW);
            a->setDrawHeight(drawH);
            a->setDrawOffset(drawOffset);
            a->load(name);
    //        a->setTlOffset(guiOffset+ofVec2f(gui->getRect()->getWidth(),0));
            allAnims.push_back(a);
            animName.push_back(aName);
            
            // update animName gui menu
            ofxUIDropDownList *w = (ofxUIDropDownList *)gui->getWidget("anim list");
            w->addToggle(aName);
            
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
            
            cout<<"create new anim "<<aName<<" of type "<<type<<endl;
    //        vector<ofxUIToggle *> tg =r->getToggles();
    //        for (int i=0 ; i<tg.size() ; i++){
    //                    cout<<"radio : "<<tg[i]->getName()<<endl;
    //        }
        }
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
    polyColors.clear();
    
    if (!isFading) {
        if (curSelected != NULL) {
            polys = curSelected->getPolylines();
            polyColors = curSelected->getPolyColors();
        }

    }
    else{
        fadeCurrentTime = ofGetElapsedTimef()-fadeStartTime;
        if (fadeCurrentTime>fadeTime) {
            isFading = false;
            lastSelected = NULL;
            if (curSelected != NULL){
                polys = curSelected->getPolylines();
                polyColors = curSelected->getPolyColors();
            }
        }
        else{
            
            /* TODO **** GERER MERGE DE COULEUR */
            
            if(curSelected!=NULL){
                polysMerger[0].setPoly2(curSelected->getPolylines()[0]);
            }
            
            if (lastSelected != NULL) {
                polysMerger[0].setPoly1(lastSelected->getPolylines()[0]);
            }
            
            polysMerger[0].mergePolyline(fadeCurrentTime/fadeTime);
            polys.push_back(polysMerger[0].getPolyline());
            // gerer merge de couleur
            polyColors.push_back(ofFloatColor (1.));
        }
    }
    
    /* scale + offset layer */
    for (int i=0; i<polys.size(); i++) {
        vector<ofPoint> ppoints = polys[i].getVertices();
        for (int j=0; j<ppoints.size(); j++) {
            ppoints[j].x = ofMap(ppoints[j].x, 0., 1., offset.x, offset.x+scale.x);
            ppoints[j].y = ofMap(ppoints[j].y, 0., 1., offset.y, offset.y+scale.y);
        }
        polys[i].clear();
        polys[i].addVertices(ppoints);
    }
    
    /* scale colors */
    for (int i=0 ; i<polyColors.size() ; i++){
        polyColors[i] *= color;
    }
    
}

void AnimManager::draw() {
//    gui->draw();
    
//    ofSetColor(0);
//    ofRect(drawOffset, drawW, drawH);
    
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

vector<ofFloatColor> AnimManager::getPolyColors(){
    return polyColors;
}

void AnimManager::parseOSC(ofxOscMessage &m){
//    ofLog (OF_LOG_NOTICE, "this is a anim OSC"+name+" - "+m.getAddress());
    
    vector<string> osc = getOSCcmd(m.getAddress());
    string cmd = osc[0];
    string msg = osc[1];
    
    if (cmd == name){
        if (msg == "/load") {
            setCurrentSelected(m.getArgAsString(0));
        }
        else if (msg == "/fadetime"){
            fadeTime = m.getArgAsFloat(0);
        }
        else if (msg == "/offset"){
            offset.x = m.getArgAsFloat(0);
            offset.y = m.getArgAsFloat(1);
        }
        else if (msg=="/scale"){
            scale.x = m.getArgAsFloat(0);
            scale.y = m.getArgAsFloat(1);
        }
        else if (msg=="/color"){
            color.r = m.getArgAsFloat(0);
            color.g = m.getArgAsFloat(1);
            color.b = m.getArgAsFloat(2);
        }
        else{
            m.setAddress(msg);
            osc = getOSCcmd(m.getAddress());
            cmd = osc[0];
            msg = osc[1];

            if (cmd =="anim") {
                m.setAddress(msg);
                if (curSelected != NULL){
                    curSelected->parseOSC(m);
                }
                if (lastSelected != NULL){
                    lastSelected->parseOSC(m);
                }
            }
        }
    }
    
    
}
