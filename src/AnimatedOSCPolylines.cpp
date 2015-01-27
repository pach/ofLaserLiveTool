//
//  AnimatedOSCPolylines.cpp
//  LaserLiveTool
//
//  Created by pach on 27/01/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//


#include "AnimatedOSCPolylines.h"

AnimatedOSCPolylines::AnimatedOSCPolylines(){
    
}

AnimatedOSCPolylines::~AnimatedOSCPolylines(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedOSCPolylines::setup(string name) {
    AnimatedStuff::setup(name);
    type = "AnimatedOSCPolylines";
    
    ofPolyline p;
    p.addVertex(ofVec2f(0.5, 0.5));
    polylines.push_back(p);
}

void AnimatedOSCPolylines::update(){
    
}

void AnimatedOSCPolylines::parseOSC(ofxOscMessage &m){
    vector<string> osc = getOSCcmd(m.getAddress());
    string cmd = osc[0];
    string msg = osc[1];
    
    cout<<"osc points "<<cmd<<endl;
    
    if (cmd == "oscLines"){
        ofPolyline p;
        polylines.clear();

        int ptOscArgs = 0;
        int nbPolylines = m.getArgAsInt32(
                                          
                                          
                                          
                                          ptOscArgs);
        ptOscArgs ++;
        
        cout<<"create new osc poly of "<<nbPolylines<<" lines "<<endl;
        
        for (int i=0; i<nbPolylines; i++) {
            p.clear();
            int nbPoints = m.getArgAsInt32(ptOscArgs);
            ptOscArgs ++;
            for (int j=0; j<nbPoints; j++) {
                p.addVertex(m.getArgAsFloat(ptOscArgs), m.getArgAsFloat(ptOscArgs+1));
                ptOscArgs += 2;
            }
            polylines.push_back(p);
        }
    }
}