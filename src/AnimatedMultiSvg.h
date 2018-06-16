//
//  AnimatedSvg.h
//  LaserAnimTool
//
//  Created by pach on 16/06/18.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"
#include "SvgLoader.h"

class AnimatedMultiSvg : public AnimatedStuff{
    
public:
    AnimatedMultiSvg();
    ~AnimatedMultiSvg();
    
    void setup (string name);
    void update ();
    
    void textInputEvent(ofxUIEventArgs &e);
    
private:
    
    void processOpenFileSelection(ofFileDialogResult openFileResult);
    
    ofPoint pos;
    float rot;
    float size;
    int nbPointSpacing;
    bool doSpacing;
    
    bool doLoad;
    string dirname;
    bool hasLoaded;
    
    vector<SvgLoader> svgVec;
    
    int idSvg ;
    float svgTime;
    float lastTime;
    
};
