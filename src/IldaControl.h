//
//  IldaControl.h
//  laserControl
//
//  Created by pach on 26/05/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxIldaFrame.h"
#include "ofxEtherdream.h"
#include "ofxUI.h"
#include "ofxOsc.h"

class IldaControl {
public:
    ~IldaControl();
    
    void setup();
    void update();
    void draw(int x, int y, int w, int h);
    
    void clear();
    void addPoly(ofPolyline poly);
    
    int getGuiWidth();
    
    void load();
    void save();
    
    void parseOSC(ofxOscMessage &m);
    
    int pps;
    bool capX;
    bool capY;
    int blankCount;
    int endCount;
    bool flipX;
    bool flipY;
    int pointCount;
//    bool doSmooth;
    int smoothing;
    float tolerance;
    ofFloatColor laserColor;
    ofPoint offset;
    ofPoint scale;
    
//    ofParameter<int> pps;
//
//    ofParameter<bool> capX;
//    ofParameter<bool> capY;
//    ofParameter<int> blankCount;
//    ofParameter<int> endCount;
//    
//    ofParameter<bool> flipX;
//    ofParameter<bool> flipY;
//    
//    ofParameter<int> pointCount;
//    ofParameter<int> smoothing;
//    ofParameter<float> tolerance;
//    
//    ofParameter<ofFloatColor> laserColor;
//    
//    ofParameter<ofVec2f> offset;
//    ofParameter<ofVec2f> scale;
    
    bool ppsChanged;
    int oldPps;
    
private:
    
    ofxIlda::Frame ildaFrame;   // stores and manages ILDA frame drawings
    
    ofxEtherdream etherdream;   // interface to the etherdream device
    
    ofxUISuperCanvas * gui;
    
};