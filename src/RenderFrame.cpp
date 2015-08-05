//
//  RenderFrame.cpp
//  SplitAnimatedLaser_test_project
//
//  Created by pach on 04/08/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//


#include "RenderFrame.h"

RenderFrame::RenderFrame(){
    
}

RenderFrame::~RenderFrame(){
    
}


void RenderFrame::setup() {
}

void RenderFrame::update() {
}

void RenderFrame::setPolys(vector<ofPolyline> newPolys){
    polys.clear();
    polys = newPolys;
}

void RenderFrame::addPolys(vector<ofPolyline> newPolys){
    for (int i=0; i<newPolys.size(); i++) {
        polys.push_back(newPolys[i]);
    }
}

void RenderFrame::clear(){
    polys.clear();
}

vector<ofPolyline> RenderFrame::getPolys(){
    return polys;
}

void RenderFrame::draw(int x, int y, int w, int h) {
    ofSetColor(0);
    ofFill();
    ofRect(x, y, w, h);
    
    ofSetColor(255);
    
    ofPushMatrix();
    ofTranslate(x, y);
    ofScale(w, h);
    ofSetColor(255);
    for (int i = 0; i<polys.size(); i++) {
        polys[i].draw();
    }
    ofPopMatrix();
}