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
#include "ofxCurvesTool.h"

class IldaControl {
public:
    ~IldaControl();
    
    void setup(int idEtherdream = 0);
    void update();
    void draw(int x, int y, int w, int h);
    
    void clear();
    void addPoly(ofPolyline poly);
    
    void setIdEtherdream (int idEtherdream);
    
    void setName(string newName);
    
    int getGuiWidth();
    
    void load();
    void save();
    
    void parseOSC(ofxOscMessage &m);
    
    inline ofxUICanvas * getGui(){return gui;};
    
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
    
    
    bool ppsChanged;
    int oldPps;
    
    bool showCurve;
    
private:
    
    ofxIlda::Frame ildaFrame;   // stores and manages ILDA frame drawings
    
    ofxEtherdream etherdream;   // interface to the etherdream device
    
    ofxUISuperCanvas * gui;
    
    ofxCurvesTool redCurve;
    ofxCurvesTool greenCurve;
    ofxCurvesTool blueCurve;
    
    string name;
//    ofxUISuperCanvas * guiCurve;
//    ofxUITabBar *guiTabBar;
    
};