//
//  AnimatedSinus.cpp
//  LaserAnimTool
//
//  Created by pach on 07/08/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "AnimatedPointsInALine.h"

AnimatedPointsInALine::AnimatedPointsInALine(){
    
}

AnimatedPointsInALine::~AnimatedPointsInALine(){
   AnimatedStuff::~AnimatedStuff();
}


void AnimatedPointsInALine::setup(string name) {
    AnimatedStuff::setup(name);
    
    type = "AnimatedPointsInALine";
    
    numSimultaneousPoints=3;
    freq=1.0;
    duration=0.25;
    
    gui->addSpacer();
    gui->addSlider("/pointsFreq", 0., 1., &freq);
    gui->addSlider("/pointsDuration", 0., 1, &duration);
    gui->addIntSlider("/pointsNumSimultaneousPoints", 0, 60, &numSimultaneousPoints);
    
    load();
    
    ofPolyline* p = new ofPolyline();
    polylines.push_back(*p);

    lastChangeFreqTime = ofGetElapsedTimef();
    lastChangeDurationTime = ofGetElapsedTimef();

 
}


void AnimatedPointsInALine::update() {
    
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
            polylines[i].addVertex(fabs(ofRandomf()),0.5+ofRandomf()/2.0);
            //cout << "point " << i << " _ " << " X : " << polylines[i].getVertices()[0].x << endl;
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

}

void AnimatedPointsInALine::parseOSC(ofxOscMessage &m){
    string address = m.getAddress();

    if(address.find("/pointsInLine/pointsFreq")!=-1)
    {
        freq = m.getArgAsFloat(0);
    }
    else if(address.find("/pointsInLine/pointsDuration")!=-1)
    {
        duration = m.getArgAsFloat(0);
    }
    else if(address.find("/pointsInLine/pointsNumSimultaneousPoints")!=-1)
    {
        numSimultaneousPoints = m.getArgAsFloat(0);
    }
    
    /*
    vector<string> osc = getOSCcmd(m.getAddress());
    string cmd = osc[0];
    string msg = osc[1];
    
    if (cmd == "freq"){
        freq = ofMap(m.getArgAsFloat(0), 0., 1., 0., 500.);
    }
    else if (cmd == "nbPoint"){
        nbPoint = m.getArgAsInt32(0);
    }
    else if (cmd == "speed"){
        speed = ofMap(m.getArgAsFloat(0), 0., 1., 0., 50.);
    }
    else if (cmd == "height"){
        height = m.getArgAsFloat(0);
    }
    else if (cmd == "posY"){
        posY = ofMap(m.getArgAsFloat(0), 0., 1., -1., 1.);
    }
    */
}
