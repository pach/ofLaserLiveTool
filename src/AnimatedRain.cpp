//
//  AnimatedSinus.cpp
//  LaserAnimTool
//
//  Created by pach on 07/08/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "AnimatedRain.h"

int oldNumDrops = 0;

AnimatedRain::AnimatedRain(){
    
}

AnimatedRain::~AnimatedRain(){
   AnimatedStuff::~AnimatedStuff();
}


void AnimatedRain::setup(string name)
{
    AnimatedStuff::setup(name);
    
    type = "AnimatedRain";
    
    numDrops = 1;
    rainSpeed = 0.05;
    rainSpeedVariation = 0.0;
    rainLength = 0.25;
    rainLengthVariation = 0.0;
    
    gui->addSpacer();
    gui->addIntSlider("/numDrops", 0, 16, &numDrops);
    gui->addSlider("/rainSpeed",0.0,0.25, &rainSpeed);
    gui->addSlider("/rainSpeedVariation",0.0,0.25, &rainSpeedVariation);
    gui->addSlider("/rainLength",0.0,0.5, &rainLength);
    gui->addSlider("/rainLengthVariation",0.0,0.25, &rainLengthVariation);
    
    ofAddListener(gui->newGUIEvent, this, &AnimatedRain::guiEvent);

//    load();
    
    ofPolyline* p = new ofPolyline();

    for(int i=0;i<numDrops;i++)
    {
        polylines.push_back(*p);
        vecADrops.push_back(ofVec2f(fabs(ofRandomf()),0.0));
        vecZDrops.push_back(ofVec2f(fabs(ofRandomf()),0.0));
        vecDropsSpeed.push_back(rainSpeed/2.0);
        vecDropsLength.push_back(rainLength);
    }
}

void AnimatedRain::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    
    if(name=="/numDrops")
    {
        changeNumDrops(numDrops);
    }
    else if(name=="/rainSpeedVariation")
    {
        changeRainSpeedVariation(rainSpeedVariation);
        
    }
    else if(name=="/rainLength")
    {
        changeRainLength(rainLength);
    }
    else if(name=="/rainLengthVariation")
    {
        changeRainLengthVariation(rainLengthVariation);
    }
}

void AnimatedRain::update() {
    AnimatedStuff::update();
    
    for(int i=0;i<vecADrops.size();i++)
    {
        vecADrops[i].y = vecADrops[i].y + rainSpeed + vecDropsSpeed[i];

        if ((vecADrops[i].y>=0.75))
        {
            vecADrops[i].y=0.75;
            
        }
        
        if(vecADrops[i].y>=vecDropsLength[i])
        {
            vecZDrops[i].y = vecZDrops[i].y + rainSpeed + vecDropsSpeed[i];
            
            if ((vecADrops[i].y>=0.75)&&(vecZDrops[i].y>=0.75))
            {
                vecADrops[i] = ofVec2f(ofRandom(0.0,1.0),0.0);
                vecZDrops[i] = ofVec2f(vecADrops[i].x,0.0);
            }
        }
        
        
        polylines[i].clear();
        polylines[i].addVertex(ofPoint(vecADrops[i].x,vecADrops[i].y));
        polylines[i].addVertex(ofPoint(vecZDrops[i].x,vecZDrops[i].y));
        
    }
    
    
/*
    //cout << ofGetElapsedTimef() <<" : " << lastChangeFreqTime << " ::-:: " << ofGetElapsedTimef()-lastChangeFreqTime << " // " << duration << endl;

    if(ofGetElapsedTimef()-lastChangeFreqTime > freq)
    {
        // it's time to change positions !!
        polylines.clear();
        //cout << "+ + + + + CREATING RANDOM POLYLINES !! " << endl;
        
        for (int i=0 ; i<numSimultaneousPoints ; i++){
            ofPolyline* p = new ofPolyline();
            polylines.push_back(*p);
            
            polylines[i].clear();
            polylines[i].addVertex(ofRandomf(),0.5+ofRandomf()/2.0);
            polylines[i].addVertex(polylines[i].getVertices()[0].x ,polylines[i].getVertices()[0].y + 0.025 );
        }
        lastChangeFreqTime = ofGetElapsedTimef();
        lastChangeDurationTime = lastChangeFreqTime;

    }
    
    else
    {
        
        
        //cout << ofGetElapsedTimef() << " last : " << lastChangeDurationTime << " RESULT : " << ofGetElapsedTimef()-lastChangeDurationTime <<" bigger then " << duration << endl;
        
        
        // we're waiting for a new creation of points
        if((ofGetElapsedTimef()-lastChangeDurationTime > duration)&&(true))
        {
            //cout << "- - - - - CLEANING POLYLINES size of polylines " << polylines.size() << endl;
            
            //polylines.clear();
//            for(int i=0;i<polylines.size();i++)
//            {
////                for(int j=0;j<polylines[i].getVertices().size();i++)
////                {
////                    vector<ofVec3f> v = polylines[i].getVertices();
////                    v.erase
////                }
//                vector<ofVec3f> v = polylines[i].getVertices();
//                for (vector<ofVec3f>::iterator it = v.begin(); it != v.end(); it++)
//                {
//                    v.erase(it--);
//                }
//                
//                cout << "num vertexs in polyline " << i << " = " << v.size()  <<endl;
//
//            }
            //ofPolyline* p = new ofPolyline();
            //polylines.push_back(*p);
            
        }
        //else cout << " !!! NON CLEANING ... size of polylines " << polylines.size() << endl;
    }
*/
}

void AnimatedRain::parseOSC(ofxOscMessage &m)
{
    ofLog (OF_LOG_NOTICE, "rain osc "+m.getAddress());
    
    vector<string> osc = getOSCcmd(m.getAddress());
    string cmd = osc[0];
    string msg = osc[1];
    if (cmd == "rain"){
        osc = getOSCcmd(msg);
        cmd = osc[0];
        msg = osc[1];
        
        ofLog (OF_LOG_NOTICE, "rain parse "+cmd);
        
        if (cmd == "numDrops"){
            ofLog(OF_LOG_NOTICE, "change drops");
            changeNumDrops(m.getArgAsFloat(0));
        }
        else if (cmd == "rainSpeed"){
            ofLog(OF_LOG_NOTICE, "change speed");
            changeRainSpeed(m.getArgAsFloat(0));
        }
        else if (cmd == "rainSpeedVariation"){
            changeRainSpeedVariation(m.getArgAsFloat(0));
        }
        else if (cmd == "rainLenth"){
            changeRainLength(m.getArgAsFloat(0));
        }
        else if (cmd == "rainLengthVariation"){
            changeRainLengthVariation(m.getArgAsFloat(0));
        }
    }

}

void AnimatedRain::changeNumDrops(int n)
{
    if(n != oldNumDrops)
    {
        numDrops = n;
        oldNumDrops = numDrops;
        
        vecADrops.clear();
        vecZDrops.clear();
        vecDropsSpeed.clear();
        vecDropsLength.clear();
        polylines.clear();
        
        for(int i=0;i<numDrops;i++)
        {
            float xpos = fabs(ofRandomf());
            vecADrops.push_back(ofVec2f(xpos,0.0));
            vecZDrops.push_back(ofVec2f(xpos,0.0));
            vecDropsSpeed.push_back(ofRandom(0,rainSpeedVariation));
            vecDropsLength.push_back(rainLength + ofRandom(0.0,rainLengthVariation));
            
            ofPolyline* p = new ofPolyline();
            polylines.push_back(*p);
        }
    }
}
void AnimatedRain:: changeRainSpeed(float n)
{
    rainSpeed = n;
}
void AnimatedRain:: changeRainSpeedVariation(float n)
{
    rainSpeedVariation = n;
    vecDropsSpeed.clear();
    for(int i=0;i<numDrops;i++)
    {
        vecDropsSpeed.push_back(rainSpeed + ofRandom(0.0,rainSpeedVariation));
    }
}

void AnimatedRain:: changeRainLength(float n)
{
    rainLength = n;
    
    vecDropsLength.clear();
    for(int i=0;i<numDrops;i++)
    {
        vecDropsLength.push_back(rainLength + ofRandom(0.0,rainLengthVariation));
    }

    
}
void AnimatedRain:: changeRainLengthVariation(float n)
{
    rainLengthVariation = n;

    
    vecDropsLength.clear();
    for(int i=0;i<numDrops;i++)
    {
        vecDropsLength.push_back(rainLength + ofRandom(0.0,rainLengthVariation));
    }
    
}
