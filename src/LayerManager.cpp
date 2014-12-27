//
//  LayerManager.cpp
//  LaserLiveTool
//
//  Created by pach on 26/12/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "LayerManager.h"

LayerManager::LayerManager(){
    
}

LayerManager::~LayerManager(){
    
}


void LayerManager::setup(vector<string>anims) {
    gui->setup();
    animList = anims;
    gui->addRadio("anim list", animList, 0, gui->getRect()->getWidth(), 20);
}

void LayerManager::update() {
    
}

void LayerManager::draw() {
    
}