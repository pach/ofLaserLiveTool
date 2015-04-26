//
//  AnimatedSinus.cpp
//  LaserAnimTool
//
//  Created by pach on 07/08/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "AnimatedSoundWave.h"


AnimatedSoundWave::AnimatedSoundWave(){
   
}

AnimatedSoundWave::~AnimatedSoundWave(){
    soundStream.close();
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedSoundWave::setup(string name)
{
    AnimatedStuff::setup(name);
    type = "AnimatedSoundWave";

    /// AUDIO
    // 0 output channels,
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	soundStream.listDevices();
	//if you want to set a different device id
	soundStream.setDeviceID(1); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
	bufferSize = 512;
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
    // 	volHistory.assign(400, 0.0);
    //	bufferCounter	= 0;
    //	drawCounter		= 0;
    //	smoothedVol     = 0.0;
    //	scaledVol		= 0.0;
	soundStream.setup(0, 2, 44100, bufferSize, 4);
    soundStream.setInput(this);

    amplitude=1.0;
    /// GUI
    gui->addSlider("/amplitude", 0.0, 0.5, &amplitude);
    ofAddListener(gui->newGUIEvent, this, &AnimatedSoundWave::guiEvent);
    load();
    
    ofPolyline* p = new ofPolyline();
    polylines.push_back(*p);

    
}


//--------------------------------------------------------------
void AnimatedSoundWave::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    
    if(name=="/amplitude")
    {
        
    }
}

//--------------------------------------------------------------
void AnimatedSoundWave::update()
{
    polylines.clear();
    
    ofPolyline p ;
    for(int i=0;i<bufferSize;i++)
    {
        int interpolatePos = ofMap(i,0,bufferSize,0,ofGetWidth());
        float bothCh = (right[i] + left[i]) / 2.0;
        p.addVertex(ofPoint((float(interpolatePos))/ofGetWidth(),(0.55f + bothCh *amplitude)));
    }
    polylines.push_back(p);
}

//--------------------------------------------------------------
void AnimatedSoundWave::parseOSC(ofxOscMessage &m)
{
    string address = m.getAddress();

    if(address.find("/amplitude")!=-1)
    {
        amplitude = m.getArgAsFloat(0);
    }
}

//--------------------------------------------------------------
void AnimatedSoundWave::audioIn(float * input, int bufferSize, int nChannels)
{
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;
    
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
        
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :)
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
	
}
