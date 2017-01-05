//
//  AnimatedStuff.h
//  LaserAnimTool
//
//  Created by pach on 29/05/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
//#include "ofxTimeline.h"
#include "ofxUI.h"
#include "ofxOsc.h"
#include "Utils.h"

class AnimatedStuff{
    
public:
    AnimatedStuff();
    ~AnimatedStuff();
    
    virtual void setup(string name);
    virtual void update() = 0 ;
    virtual void draw();
    virtual void start(){};
    
//    void setTimelineActive(bool enable);
    
//    void drawTimeline();
    void drawGui();
    
    void setName(string newName);
    
    virtual void load(string layerName = "") ;
    virtual void save(string layerName) ;
    
    virtual void parseOSC (ofxOscMessage &m) {};
    
//    void play();
//    void stop();
//    void togglePlay();
//    void clear();
//    void setLoop(ofLoopType loop);
    
    void showGui(bool show);
    
    void setDrawWidth(int w);
    void setDrawHeight(int h);
    void setDrawOffset(ofVec2f offset);

//    void setTlWidth(int w);
//    void setTlHeight(int h);
//    void setTlOffset(ofVec2f offset);
    
    void setGuiOffset(ofVec2f offset);
    
    void setSelected(bool picking);
    inline bool getSelected() {return isSelected;};
    inline void toggleSelected() {setSelected(!isSelected);};
    
    void setLoopMode (ofLoopType mode);
    
    inline virtual vector<ofPolyline> getPolylines(){return polylines;};    
    
    inline string getName(){return name;}
    
    inline virtual void mousePressed(ofMouseEventArgs& e) {};
    inline virtual void mouseDragged(ofMouseEventArgs& e) {};
    inline virtual void mouseReleased(ofMouseEventArgs& e) {};
    inline virtual void mouseMoved(ofMouseEventArgs& e) {};
    
    inline virtual void mouseScrolled(ofMouseEventArgs& e) {};
    inline virtual void mouseEntered(ofMouseEventArgs& e) {};
    inline virtual void mouseExited(ofMouseEventArgs& e) {};
//
//    void setCurrentTime(unsigned long long time);
//    void setTimeLength(long time);
    
    string getType(){ return type;};
protected:
    
    string type;
    
    vector<ofPolyline> polylines;
    
//    ofxTimeline timeline;
    string name;

    int drawW;
    int drawH;
    ofVec2f drawOffset;
    bool isSelected;
    bool isTimelineActive;
    
    ofLoopType loopMode;
    
    ofxUISuperCanvas *gui;
    
//    bool useTimeline; // todo
    
};
