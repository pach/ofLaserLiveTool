//
//  AnimatedSinus.h
//  LaserAnimTool
//
//  Created by pach on 07/08/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimatedStuff.h"

class AnimatedSoundWave : public AnimatedStuff, ofBaseSoundInput {
    
public:
    
    AnimatedSoundWave();
    ~AnimatedSoundWave();
    
    void setup(string name);
    void update();
    void guiEvent(ofxUIEventArgs &e);
    void parseOSC(ofxOscMessage &m);
    
private:
    
    /// AUDIO
    ofSoundStream soundStream;
    void audioIn(float * input, int bufferSize, int nChannels);
    vector <float> left;
    vector <float> right;
    int 	bufferCounter;
    float   smoothedVol;
    int bufferSize;
    
    float amplitude;
    
};