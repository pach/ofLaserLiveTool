//
//  SvgLoader.h
//  laserControl
//
//  Created by pach on 26/05/14.
//
//

#pragma once
#include "ofMain.h"
#include "ofxSvg.h"

class SvgLoader {

public:
    void setup();
    void update();
    void draw();
    
    void clear();
    
    void load(string filename);
    
    bool hasNextPolyline();
    ofPolyline getPolyline();
    
private:
    vector<ofPolyline> polypocket;
    int curPoly;
    
    ofxSVG svg;
    
};
