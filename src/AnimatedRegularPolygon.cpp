//
//  AnimatedRegularPolygon.cpp
//  LaserLiveTool
//
//  Created by pach on 22/09/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//


#include "AnimatedRegularPolygon.h"

void AnimatedRegularPolygon::setup(string name) {
    AnimatedStuff::setup(name);
    center = ofVec2f(0., 0.);
    size = 0.;
    nbPoint = 6;
    rot = 0;
    
    gui->addSlider("size", 0., 1., &size);
    gui->addIntSlider("nb Point", 3, 10, &nbPoint);
    gui->addSlider("rot", 0., 2*PI, &rot);
    gui->add2DPad("center", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &center);
    
    type="AnimatedRegularPolygon";
    
    float quadra = (2*PI) / nbPoint;
   
    
    for (int i=0; i<nbPoint; i++) {
        ofPolyline p;
        p.addVertex(center.x+sin(quadra*i+rot)*size, center.y+cos(quadra*i+rot)*size);
        p.addVertex(center.x+sin(quadra*(i+1)+rot)*size, center.y+cos(quadra*(i+1)+rot)*size);
        polylines.push_back(p);
    }
    
    load();
    
}

void AnimatedRegularPolygon::update() {
    polylines.clear();
    float quadra = (2*PI) / nbPoint; 
    for (int i=0; i<nbPoint; i++) {
        ofPolyline p;
        p.addVertex(center.x+sin(quadra*i+rot)*size, center.y+cos(quadra*i+rot)*size);
        p.addVertex(center.x+sin(quadra*(i+1)+rot)*size, center.y+cos(quadra*(i+1)+rot)*size);
        polylines.push_back(p);
        
        cout<<"add "<<p[0]<<" "<<p[1]<< endl;
    }
}
