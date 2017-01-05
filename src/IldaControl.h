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
//#include "ofxCurvesTool.h"

#include "FixedShot.h"

class IldaControl {
public:
    ~IldaControl();
    
    void setup(int idEtherdream = 0);
    void update();
    void draw(int x, int y, int w, int h);
    
    void clear();
    void addPoly(ofPolyline poly);
    void addPoly(ofPolyline poly, ofFloatColor color);
    
    void setIdEtherdream (int idEtherdream);
    
    void setName(string newName);
    
    int getGuiWidth();
    
    void load();
    void save();
    
    void forceReconnect();
    
    void parseOSC(ofxOscMessage &m);
    
//    inline ofxUITabBar * getGui(){return &laserTabs;};
//    inline ofxUISuperCanvas * getGui(){return laserGui;}
    inline ofxUIScrollableCanvas * getGui(){return laserGui;}
    
    int pps;
    bool capX;
    bool capY;
    int blankCount;
    int endCount;
    bool flipX;
    bool flipY;
    int pointCount;
    int minimumPointCount;
//    bool doSmooth;
    bool doSpacing;
    int smoothing;
    float tolerance;
    ofFloatColor laserColor;
    ofPoint offset;
    ofPoint scale;
    
    
    bool ppsChanged;
    int oldPps;
    
//    bool showCurve;
    
private:
    
    ofxIlda::Frame ildaFrame;   // stores and manages ILDA frame drawings
    FixedShot ildaShot;
    
    ofxEtherdream etherdream;   // interface to the etherdream device
    long ethId = 0;
    
    ofxUIScrollableCanvas * laserGui;
//    ofxUISuperCanvas * renderGui;3
//    ofxUITabBar laserTabs;
    
//    ofxCurvesTool redCurve;
//    ofxCurvesTool greenCurve;
//    ofxCurvesTool blueCurve;
  
    
    bool freezeFrame;
    bool drawCalib;
    bool fixedShotCalib;
    
    string name;
//    ofxUISuperCanvas * guiCurve;
//    ofxUITabBar *guiTabBar;
    
};
