//
//  IldaControl.cpp
//  laserControl
//
//  Created by pach on 26/05/14.
//
//

#include "IldaControl.h"
#include "Utils.h"

IldaControl::~IldaControl(){
    delete gui;
//    delete guiCurve;
//    delete guiTabBar;
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
//    guiCurve = new ofxUISuperCanvas("Laser Curve");
//    guiTabBar = new ofxUITabBar();
    
    gui->addSpacer();
    gui->addIntSlider("pps", 500, 60000, &pps);
    gui->addIntSlider("point count", 50, 2500, &pointCount);
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
    gui->addToggle("show curve", &showCurve);
    
    gui->addSpacer();
    gui->add2DPad("offset", ofxUIVec2f(-1., 1), ofxUIVec2f(-1., 1.), &offset);
    gui->add2DPad("scale", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &scale);
    
    
//    guiTabBar->addCanvas(gui);
//    
//    guiCurve->addSpacer();
//    
//    guiTabBar->addCanvas(guiCurve);
    
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
    
    redCurve.setup();
    greenCurve.setup();
    blueCurve.setup();
    
    load();

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
    ildaFrame.params.output.color.r = (float)redCurve[laserColor.r*255]/255.;
    ildaFrame.params.output.color.g = (float)greenCurve[laserColor.g*255]/255.;
    ildaFrame.params.output.color.b = (float)blueCurve[laserColor.b*255]/255.;
    ildaFrame.params.output.blankCount = blankCount;
    ildaFrame.params.output.endCount = endCount;
 
    // do your thang
    if (etherdream.checkConnection()){
        ildaFrame.update();
    }
}

void IldaControl::load(){
    gui->loadSettings("ilda.xml");
    redCurve.load("red.yml");
    redCurve.load("green.yml");
    redCurve.load("blue.yml");
}

void IldaControl::save(){
    gui->saveSettings("ilda.xml");
    redCurve.save("red.yml");
    redCurve.save("green.yml");
    redCurve.save("blue.yml");
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
    
    if (showCurve) {
        redCurve.draw(ofGetWidth()-830, 10);
        greenCurve.draw(ofGetWidth()-540, 10);
        blueCurve.draw(ofGetWidth()-270, 10);
    }
    gui->draw();
}

void IldaControl::parseOSC(ofxOscMessage &m){
//    string msg = m.getAddress();
//    string cmd ;
//    
//    int ces = msg.find_first_of("/");
//    
//    if (ces != -1) {
//        if (ces == 0){
//            msg = msg.substr(ces+1);
//            cmd = msg;
//            ces = msg.find_first_of("/");
//            if (ces != -1) {
//                cmd = msg.substr(0, ces);
//                msg = msg.substr(ces);
//            }
//        }
//        else{
//            cmd = msg.substr(0, ces);
//            msg = msg.substr(ces);
//        }
//    }

    vector<string> osc = getOSCcmd(m.getAddress());
    string cmd = osc[0];
    string msg = osc[1];
    
    if (cmd == "laser"){
        
//        m.setAddress(msg);
//        ces = msg.find_first_of("/");
//        
//        if (ces != -1) {
//            if (ces == 0){
//                msg = msg.substr(ces+1);
//                cmd = msg;
//                ces = msg.find_first_of("/");
//            }else{
//                cmd = msg.substr(0, ces);
//                msg = msg.substr(ces);
//            }
//        }
        osc = getOSCcmd(msg);
        cmd = osc[0];
        msg = osc[1];
        
        if (cmd == "offset"){
            offset.x = m.getArgAsFloat(0);
            offset.y = m.getArgAsFloat(1);
            cout<<"setting offset "<<offset<<endl;
        }
        else if (cmd == "scale"){
            scale.x = m.getArgAsFloat(0);
            scale.y = m.getArgAsFloat(1);
        }
        else if (cmd == "color"){
            laserColor.r = m.getArgAsFloat(0);
            laserColor.g = m.getArgAsFloat(1);
            laserColor.b = m.getArgAsFloat(2);
        }
        
    }
}