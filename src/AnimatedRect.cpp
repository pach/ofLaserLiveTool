//
//  AnimatedRect.cpp
//  LaserAnimTool
//
//  Created by pach on 14/09/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "AnimatedRect.h"

AnimatedRect::AnimatedRect(){
    
}

AnimatedRect::~AnimatedRect(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedRect::setup(string name) {
    AnimatedStuff::setup(name);
    center = ofVec2f (0.5f, 0.5f);
    rot = 0.0f;
    size = 0.0f;
    
    type = "AnimatedRect";

    timeline.addCurves(name+".x");
    timeline.addCurves(name+".y");
    timeline.addCurves(name+".rot");
    timeline.addCurves(name+".size");
    
    ofPolyline p ;
    p.addVertex(center+ofVec2f(-size/2., -size/2.));
    p.addVertex(center+ofVec2f(size/2., -size/2.));
    polylines.push_back(p);
    p.clear();
    p.addVertex(center+ofVec2f(size/2., -size/2.));
    p.addVertex(center+ofVec2f(size/2., size/2.));
    polylines.push_back(p);
    p.clear();
    p.addVertex(center+ofVec2f(size/2., size/2.));
    p.addVertex(center+ofVec2f(-size/2., size/2.));
    polylines.push_back(p);
    p.clear();
    p.addVertex(center+ofVec2f(-size/2., size/2.));
    p.addVertex(center+ofVec2f(-size/2., -size/2.));
    polylines.push_back(p);
    
    load();
}

void AnimatedRect::update() {
    
    center.x = timeline.getValue(name+".x");
    center.y = timeline.getValue(name+".y");
    rot = timeline.getValue(name+".rot");
    rot = rot * 360.0;
    size = timeline.getValue(name+".size");
    
    ofPolyline p ;
    polylines.clear();
    p.addVertex(center+ofVec2f(-size/2., -size/2.).rotate(rot));
    p.addVertex(center+ofVec2f(size/2., -size/2.).rotate(rot));
    polylines.push_back(p);
    p.clear();
    p.addVertex(center+ofVec2f(size/2., -size/2.).rotate(rot));
    p.addVertex(center+ofVec2f(size/2., size/2.).rotate(rot));
    polylines.push_back(p);
    p.clear();
    p.addVertex(center+ofVec2f(size/2., size/2.).rotate(rot));
    p.addVertex(center+ofVec2f(-size/2., size/2.).rotate(rot));
    polylines.push_back(p);
    p.clear();
    p.addVertex(center+ofVec2f(-size/2., size/2.).rotate(rot));
    p.addVertex(center+ofVec2f(-size/2., -size/2.).rotate(rot));
    polylines.push_back(p);
    
}
