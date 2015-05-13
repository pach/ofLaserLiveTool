//
//  FixedShot.cpp
//  LaserLiveTool
//
//  Created by pach on 08/05/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//


#include "FixedShot.h"
#include "ofxIldaPoint.h"

FixedShot::FixedShot(){
    ofxIlda::Frame::setDefaultParams();
    params.output.blankCount = 0;
    params.output.endCount = 0;
}


void FixedShot::update() {
    
    clear();
    points.clear();
    
    ofPoint point = params.output.transform.offset+ofPoint(0.5, 0.5);
    
    for (int i=0; i<500; i++) {
        points.push_back(ofxIlda::Point (point, params.output.color) );
    }
    
}

void FixedShot::draw(float x, float y, float w, float h){
    if(w==0) w = ofGetWidth();
    if(h==0) h = ofGetHeight();
    
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(x, y);
    ofScale(w, h);
    
    ofSetColor(params.output.color.r*255, params.output.color.g*255, params.output.color.b*255);
    
    ofCircle(0.5, 0.5, 0.02);
    
    ofPopMatrix();
    ofPopStyle();
}