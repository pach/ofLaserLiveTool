//
//  IldaControl.cpp
//  laserControl
//
//  Created by pach on 26/05/14.
//
//

#include "IldaControl.h"

IldaControl::~IldaControl(){
    delete gui;
}

void IldaControl::setup(){
    pps = 20000;
    pointCount = 300;
    smoothing = 0;
    tolerance = 0;
    blankCount = 25;
    endCount = 25;
    capX = false;
    capY = false;
    flipX = true;
    flipY = true;
    laserColor = ofFloatColor(1., 1., 1., 1.);
    offset = ofPoint(0., 0.);
    scale = ofPoint(0.5, 0.5);
    
    gui = new ofxUISuperCanvas("ILDA Control");
    
    gui->addSpacer();
    gui->addIntSlider("pps", 500, 90000, &pps);
    gui->addIntSlider("point count", 2, 2500, &pointCount);
//    gui->addToggle("do Smooth", &doSmooth);
    gui->addIntSlider("smooth amount", 0, 10, &smoothing);
    gui->addSlider("tolerance", 0, 1., &tolerance);
    gui->addIntSlider("blank count", 0, 60, &blankCount);
    gui->addIntSlider("end count", 0, 60, &endCount);
    gui->addToggle("cap X", &capX);
    gui->addToggle("cap Y", &capY);
    gui->addToggle("flip X", &flipX);
    gui->addToggle("flip Y", &flipY);
    
    gui->addSpacer();
    gui->addSlider("red", 0, 1, &laserColor.r);
    gui->addSlider("green", 0, 1, &laserColor.g);
    gui->addSlider("blue", 0, 1, &laserColor.b);
    
    gui->addSpacer();
    gui->add2DPad("offset", ofxUIVec2f(-1., 1), ofxUIVec2f(-1., 1.), &offset);
    gui->add2DPad("scale", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &scale);
    
//    gui->autoSizeToFitWidgets();
    gui->setHeight(ofGetWindowHeight());
//	ofAddListener(gui1->newGUIEvent,this,&ofApp::guiEvent);
    
//    gui.add(pps.set("pps", 20000, 1000, 90000));
//    gui.add(pointCount.set("point count", 300, 0, 2000));
//    gui.add(smoothing.set("smooth amount", 0, 0, 10));
//    gui.add(tolerance.set("tolerance", 0., 0., 1.));
//    gui.add(blankCount.set("blank count", 25, 0, 60));
//    gui.add(endCount.set("end count", 25, 0, 60));
//    
//    gui.add(capX.set("cap X", false));
//    gui.add(capY.set("cap Y", false));
//    
//    gui.add(flipX.set("flip X", true));
//    gui.add(flipY.set("flip Y", true));
//    gui.add(laserColor.set("color", ofColor(255., 255.),ofColor(0., 255.),ofColor(255., 255.)));
//    
//    gui.add(offset.set("offset", ofVec2f(0., 0.), ofVec2f(-1., -1.), ofVec2f(1., 1.)));
//    gui.add(scale.set("scale", ofVec2f(0.5, 0.5), ofVec2f(0., 0.), ofVec2f(1., 1.)));
    
    etherdream.setup();
    etherdream.setPPS(pps);

}

void IldaControl::clear(){
    ildaFrame.clear();
}

void IldaControl::addPoly(ofPolyline poly){
    ildaFrame.addPoly(poly);
}

void IldaControl::update(){
    if (oldPps != pps){
        etherdream.setPPS(pps);
        oldPps = pps;
    }
    
    ildaFrame.polyProcessor.params.targetPointCount=pointCount;
    ildaFrame.polyProcessor.params.smoothAmount=smoothing;
    ildaFrame.polyProcessor.params.optimizeTolerance=tolerance;
    
    ildaFrame.params.output.transform.scale = scale;
    ildaFrame.params.output.transform.offset = offset;
    ildaFrame.params.output.transform.doFlipX = flipX;
    ildaFrame.params.output.transform.doFlipY = flipY;
    ildaFrame.params.output.doCapX = capX;
    ildaFrame.params.output.doCapY = capY;
    ildaFrame.params.output.color = laserColor;
    ildaFrame.params.output.blankCount = blankCount;
    ildaFrame.params.output.endCount = endCount;
 
    // do your thang
    if (etherdream.checkConnection()){
        ildaFrame.update();
    }
}

void IldaControl::load(){
    gui->loadSettings("ilda.xml");
}

void IldaControl::save(){
    gui->saveSettings("ilda.xml");
}

int IldaControl::getGuiWidth(){
    return gui->getRect()->getWidth();
}

void IldaControl::draw(int x, int y, int w, int h){
    ofSetColor(0);
    ofRect(x, y, w, h);
    // draw to the screen
    ofSetColor(255);
    ildaFrame.draw(x, y, w, h);
    
    // send points to the etherdream
    etherdream.setPoints(ildaFrame);
    
    gui->draw();
}