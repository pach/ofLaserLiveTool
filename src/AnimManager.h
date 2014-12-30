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


class AnimManager{
    
public:
    AnimManager();
    ~AnimManager();
    
    void setup();
    void update();
    void draw();
    
    void setTimelineActive(bool enable);
    
    void drawTimeline();
    void drawGui();
    
    void play();
    void stop();
    void togglePlay();
    void clear();
    void setLoop(ofLoopType loop);
    
    void setDrawWidth(int w);
    void setDrawHeight(int h);
    void setDrawOffset(ofVec2f offset);
        
    void setGuiOffset(ofVec2f offset);
    
    void load();
    void save();
    
    void setupAnimatedList();
    void setupGui();
    
    vector<ofPolyline> getPolylines();
    
    void guiEvent(ofxUIEventArgs &e);
    
    void hasClicked (ofMouseEventArgs &e);
    
    void setCurrentSelected(string name);
    void addActiveAnim(int trackId, string name);
    void removeActiveAnim(int trackId);
    
    void createNewAnimation(string type, string name);
    void createNewAnimationWithTextbox(string type);
    
    void parseOSC (ofxOscMessage &m);
    
private:
    vector<AnimatedStuff*> allAnims;
    map<int, AnimatedStuff*> activeAnims;
    
//    bool updateSelected;
    
    AnimatedStuff * curSelected;
    
    int nbLayer;
    
    ofxUISuperCanvas *gui;
    
    int drawW;
    int drawH;
    ofVec2f drawOffset;
    ofVec2f guiOffset;
//    bool isTimelineActive;

    map<int, AnimatedStuff*>::iterator itActive;
    map<int, AnimatedStuff*>::iterator itActiveEnd;
    
    vector<string>animName;
    
    bool newAnimBool ;
    
    bool animUIselectEvent;
    
//    LayerManager layer1;
    
};