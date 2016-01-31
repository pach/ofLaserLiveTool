//
//  AnimManager.h
//  LaserAnimTool
//
//  Created by pach on 29/05/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once


#include "ofMain.h"
#include "AnimatedStuff.h"

#include "ofxUI.h"
#include "ofxOSC.h"

#include "ofxPolylineMerger.h"

class AnimManager{
    
public:
    AnimManager();
    ~AnimManager();
    
    void setup();
    void update();
    void draw();
    
    void drawGui();
    
    void setName(string newName);
    
    void setDrawWidth(int w);
    void setDrawHeight(int h);
    void setDrawOffset(ofVec2f offset);
        
    void setGuiOffset(ofVec2f offset);
    
    void load();
    void save();
    
    vector<ofPolyline> getPolylines();
    
    void guiEvent(ofxUIEventArgs &e);
    
    void hasClicked (ofMouseEventArgs &e);
    
    void setCurrentSelected(string name);
//    void addActiveAnim(int trackId, string name);
//    void removeActiveAnim(int trackId);
    
    void createNewAnimation(string type, string name);
    void createNewAnimationWithTextbox(string type);
    
    void parseOSC (ofxOscMessage &m);
    
    inline ofxUICanvas * getGui(){return gui;};
    inline ofFloatColor getColor(){return color;};
    
private:
    
    void setupAnimatedList();
    void setupGui();
    
    vector<AnimatedStuff*> allAnims;
//    map<int, AnimatedStuff*> activeAnims;
    
//    bool updateSelected;
    
    AnimatedStuff * curSelected;
    AnimatedStuff * lastSelected;
    
    ofxUISuperCanvas *gui;
    
    int drawW;
    int drawH;
    ofVec2f drawOffset;
    ofVec2f guiOffset;
//    bool isTimelineActive;

//    map<int, AnimatedStuff*>::iterator itActive;
//    map<int, AnimatedStuff*>::iterator itActiveEnd;
    
    vector<string>animName;
    
    vector<ofPolyline> polys;
    vector<ofxPolylineMerger> polysMerger;
    
    bool newAnimBool ;
    
    bool animUIselectEvent;
    
    bool isFading;
    float fadeTime;
    float fadeCurrentTime;
    float fadeStartTime;
    
    string name;
    
    ofPoint offset;
    ofPoint scale;
    ofFloatColor color;
//    float rotate;
};