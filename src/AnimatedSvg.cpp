//
//  AnimatedSvg.cpp
//  LaserAnimTool
//
//  Created by pach on 14/09/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "AnimatedSvg.h"

AnimatedSvg::AnimatedSvg(){
    
}

AnimatedSvg::~AnimatedSvg(){
     AnimatedStuff::~AnimatedStuff();
}


void AnimatedSvg::setup(string name) {
    AnimatedStuff::setup(name);
    type = "AnimatedSvg";
    
    pos = ofVec2f (0.5f, 0.5f);
    rot = 0.0f;
    size = 0.0f;
    
    load();
}

void AnimatedSvg::update() {
    
}

void loadSvg(string filename){
    
}