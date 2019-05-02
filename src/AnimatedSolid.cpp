//
//  AnimatedSolid.cpp
//  LaserLiveTool
//
//  Created by Thomas Pachoud on 03/07/2016.
//
//

#include "AnimatedSolid.h"

void AnimatedSolid::setup(string name){
    AnimatedStuff::setup(name);
    
    center = ofVec2f (0.5, 0.5);
    size1 = 0.25;
    size2 = 0.;
    nbPoint = 6;
    rot1 = 0.;
    rot2 = 0.;
    perlinCoeff = 0.;
    perlinSpeed = 0.;
    
    gui->addSlider("/size/1", 0., 1., &size1);
    gui->addSlider("/size/2", -0.5, 0.5, &size2);
    gui->addIntSlider("/nbPoint", 3, 10, &nbPoint);
    gui->addSlider("/rot/1", 0., 2*PI, &rot1);
    gui->addSlider("/rot/2", -1., 1., &rot2);
    gui->add2DPad("/center", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &center);
    gui->addSlider("/perlin/coeff", 0., 1., &perlinCoeff);
    gui->addSlider("/perlin/speed", 0., 1., &perlinSpeed);
    
    type = "AnimatedSolid";
    
    easingType = ofxTween::easeInOut;
    clamp = true;
    
    float quadra = (2*PI) / nbPoint;
    polylines.clear();
    
    targetPoint.clear();
    for (int i=0; i<=nbPoint; i++) {
        targetPoint.addVertex(center.x+sin(quadra*i+rot1)*size1, center.y+cos(quadra*i+rot1)*size1);
    }
    
    ofPolyline p;
    ofPoint pt;
    int pointPerLine = NB_POINTS/targetPoint.size();
    for (int i=0; i<targetPoint.size()-1; i++) {
        for (int j=0; j<pointPerLine; j++) {
            pt = ofVec2f(ofxTween::map(j, 0, pointPerLine, targetPoint[i].x, targetPoint[i+1].x, clamp, easing, easingType), ofxTween::map(j, 0, pointPerLine, targetPoint[i].y, targetPoint[i+1].y, clamp, easing, easingType));
            p.addVertex(pt);
        }
    }
    
    polylines.push_back(p);
    
    time = 0;
    lastTime = ofGetElapsedTimef();
    
//    load();
    
    
}

void AnimatedSolid::update(){
    AnimatedStuff::update();
    
    polylines.clear();
    
    float quadra = (2*PI) / nbPoint;
    
    time += (ofGetElapsedTimef()-lastTime)*perlinSpeed;
    lastTime = ofGetElapsedTimef();
    
    targetPoint.clear();
    for (int i=0; i<nbPoint; i++) {
        ofPoint pt;
        
        float disp = ofNoise(time, i*10000)-0.5;
        disp *= perlinCoeff;
        
        if (i%2 == 0){
            pt = ofVec2f(center.x+sin(quadra*i+rot1)*(size1+disp), center.y+cos(quadra*i+rot1)*(size1+disp));
        }
        else{
            float bRot = rot2*((2*PI)/nbPoint);
            
            pt = ofVec2f(center.x+sin(quadra*i+rot1+bRot)*(size1+size2+disp), center.y+cos(quadra*i+rot1+bRot)*(size1+size2+disp));
        }
        targetPoint.addVertex(pt);
    }
    targetPoint.addVertex(targetPoint[0]);
    
    ofPolyline p;
    ofPoint pt;
    int pointPerLine = NB_POINTS/targetPoint.size();
    for (int i=0; i<targetPoint.size()-1; i++) {
        for (int j=0; j<pointPerLine; j++) {
            pt = ofVec2f(ofxTween::map(j, 0, pointPerLine, targetPoint[i].x, targetPoint[i+1].x, clamp, easing, easingType), ofxTween::map(j, 0, pointPerLine, targetPoint[i].y, targetPoint[i+1].y, clamp, easing, easingType));
            p.addVertex(pt);
        }
    }
    
    polylines.push_back(p);
    
}

void AnimatedSolid::parseOSC(ofxOscMessage &m){
    vector<string> osc = getOSCcmd(m.getAddress());
    string cmd = osc[0];
    string msg = osc[1];
    if (cmd == "solid"){
        osc = getOSCcmd(msg);
        string cmd = osc[0];
        string msg = osc[1];
        
        if (cmd == "center"){
            center = ofPoint(m.getArgAsFloat(0), m.getArgAsFloat(1));
        }
        if (cmd == "nbPoint"){
            nbPoint = m.getArgAsInt32(0);
        }
        else if (cmd == "rot"){
            osc = getOSCcmd(msg);
            cmd = osc[0];
            msg = osc[1];
            if (cmd == "1"){
                rot1 = ofMap(m.getArgAsFloat(0), 0., 1., 0., 2*PI);
            }
            else if (cmd == "2"){
                rot2 = m.getArgAsFloat(0);
            }
        }
        else if (cmd == "size"){
            osc = getOSCcmd(msg);
            cmd = osc[0];
            msg = osc[1];
            if (cmd == "1"){
                size1 = m.getArgAsFloat(0);
            }
            else if (cmd == "2"){
                size2 = m.getArgAsFloat(0);
            }
        }
        else if (cmd == "perlin"){
            osc = getOSCcmd(msg);
            cmd = osc[0];
            msg = osc[1];
            if (cmd == "coeff"){
                perlinCoeff = m.getArgAsFloat(0);
            }
            else if (cmd == "speed"){
                perlinSpeed = m.getArgAsFloat(0);
            }
        }
    }
}
