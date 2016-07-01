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
    delete laserGui;
//    delete renderGui;
//    delete guiCurve;
//    delete guiTabBar;
}

void IldaControl::setup(int idEtherdream){
    name = "/laser."+ofToString(idEtherdream);
    
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
    doSpacing = true;
    laserColor = ofFloatColor(1., 1., 1., 1.);
    offset = ofPoint(0., 0.);
    scale = ofPoint(0.5, 0.5);
    minimumPointCount = 1000;
    
//    laserGui = new ofxUIScrollableCanvas("ILDA Control");
    laserGui = new ofxUIScrollableCanvas();
    laserGui->setScrollAreaToScreen();
    laserGui->setScrollableDirections(false, true);
    
//    renderGui = new ofxUISuperCanvas("render Control");
    
//    laserTabs.setup();
//    laserTabs.setPosition(60, 0);
//    guiCurve = new ofxUISuperCanvas("Laser Curve");
//    guiTabBar = new ofxUITabBar();
    
    laserGui->setName(name);
    laserGui->addLabel(name);
    
    laserGui->addSpacer();
    laserGui->addIntSlider("pps", 500, 60000, &pps);
    laserGui->addIntSlider("point count", 0, 2500, &pointCount);
    laserGui->addIntSlider("min point count", 0, 2500, &minimumPointCount);
//    gui->addToggle("do Smooth", &doSmooth);
    laserGui->addIntSlider("smooth amount", 0, 10, &smoothing);
    laserGui->addSlider("tolerance", 0, 1., &tolerance);
    laserGui->addToggle("/doSpacing", &doSpacing);
    laserGui->addIntSlider("blank count", 0, 60, &blankCount);
    laserGui->addIntSlider("end count", 0, 60, &endCount);
    laserGui->addToggle("cap X", &capX);
    laserGui->addToggle("cap Y", &capY);
    laserGui->addToggle("flip X", &flipX);
    laserGui->addToggle("flip Y", &flipY);
    
    laserGui->addSpacer();
    laserGui->addToggle("freeze", &freezeFrame);
    laserGui->addToggle("/calib", &drawCalib);
    laserGui->addToggle("fixed shot", &fixedShotCalib);
   
    /* render GUI */
    laserGui->addSpacer();
    laserGui->addSlider("red", 0, 1, &laserColor.r);
    laserGui->addSlider("green", 0, 1, &laserColor.g);
    laserGui->addSlider("blue", 0, 1, &laserColor.b);
    laserGui->addToggle("show curve", &showCurve);
    
    laserGui->addSpacer();
    laserGui->add2DPad("/offset", ofxUIVec2f(-1., 1), ofxUIVec2f(-1., 1.), &offset);
    laserGui->add2DPad("/scale", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &scale);
    laserGui->addSpacer();
//    laserTabs.addCanvas(laserGui);
//    laserTabs.addCanvas(renderGui);
    
//    guiTabBar->addCanvas(gui);
//    
//    guiCurve->addSpacer();
//    
//    guiTabBar->addCanvas(guiCurve);
    
    laserGui->setHeight(ofGetWindowHeight());
    laserGui->setVisible(false);
//    renderGui->setHeight(ofGetWindowHeight());
//    renderGui->setVisible(false);
    
    if (ethId == 0) {
        
        etherdream.setup(true, idEtherdream);
        etherdream.setPPS(pps);
        
        ethId = etherdream.getEtherdreamId();
        
        ofLog(OF_LOG_NOTICE, "etherdream "+ofToString(idEtherdream)+" id is "+ofToString(ethId));
    }else{
        
    }
    
    redCurve.setup();
    greenCurve.setup();
    blueCurve.setup();
    
    load();

}

void IldaControl::setName(string newName){
    name = newName;
    laserGui->setName(name);
    laserGui->addLabel(name);
//    renderGui->setName(name+".rnd");
//    renderGui->addLabel(name+".rnd");
//    laserTabs.setName(name);
    load();
}

void IldaControl::setIdEtherdream(int idEtherdream){
    etherdream.kill();
    etherdream.setup(true, idEtherdream);
}

void IldaControl::clear(){
    if (!freezeFrame)
        ildaFrame.clear();
}

void IldaControl::addPoly(ofPolyline poly){
    addPoly(poly, laserColor);
}

void IldaControl::addPoly(ofPolyline poly, ofFloatColor color){
    if (!freezeFrame && !drawCalib && !fixedShotCalib){
        ildaFrame.addPoly(poly, color);
    }
    else if (drawCalib){
        ildaFrame.drawCalibration();
    }
    else if (fixedShotCalib){
        
    }
}

void IldaControl::update(){
    if (oldPps != pps){
        etherdream.setPPS(pps);
        oldPps = pps;
    }
    
    ildaFrame.polyProcessor.params.targetPointCount=pointCount-(blankCount+endCount)*ildaFrame.getPolys().size()*2;
    if (pointCount != 0 && ildaFrame.polyProcessor.params.targetPointCount < 0)
        ildaFrame.polyProcessor.params.targetPointCount = 10;
    else if (pointCount == 0)
        ildaFrame.polyProcessor.params.targetPointCount = 0;
    
    ildaFrame.polyProcessor.params.smoothAmount=smoothing;
    ildaFrame.polyProcessor.params.optimizeTolerance=tolerance;
    ildaFrame.polyProcessor.params.doSpacing=doSpacing;
    
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
    ildaFrame.params.output.minimumPointCount = minimumPointCount;
 
    // do your thang
    
    if (etherdream.checkConnection()){
        if (fixedShotCalib){
            ildaShot.params.output.color = ildaFrame.params.output.color;
            ildaShot.params.output.transform.offset = offset;
            ildaShot.update();
            etherdream.setPoints(ildaShot);
        }else{
            ildaFrame.update();
            etherdream.setPoints(ildaFrame);
        }
    }
    
    // send points to the etherdream
    //    etherdream.setPoints(ildaFrame);
//    etherdream2.setPoints(ildaFrame);
}

void IldaControl::load(){
    laserGui->loadSettings(name+"_ctrl_ilda.xml");
//    renderGui->loadSettings(name+"_rnd_ilda.xml");
    redCurve.load(name+"red.yml");
    greenCurve.load(name+"green.yml");
    blueCurve.load(name+"blue.yml");
    
    freezeFrame = false;
    drawCalib = false;
    fixedShotCalib = false;
}

void IldaControl::save(){
    laserGui->saveSettings(name+"_ctrl_ilda.xml");
//    renderGui->saveSettings(name+"_rnd_ilda.xml");
    redCurve.save(name+"red.yml");
    greenCurve.save(name+"green.yml");
    blueCurve.save(name+"blue.yml");
}

void IldaControl::forceReconnect(){
//    cout<<"--------------------------------"<<endl;
//    cout<<"is going to force laser "<<name<<" to reconnect"<<endl;
//    cout<<"--------------------------------"<<endl;
    etherdream.forceReconnect();
}

int IldaControl::getGuiWidth(){
    return laserGui->getRect()->getWidth();
//    return laserTabs.getRect()->getWidth();
}

void IldaControl::draw(int x, int y, int w, int h){
    ofSetColor(0);
    ofRect(x, y, w, h);
    // draw to the screen
    ofSetColor(255);
    if(fixedShotCalib){
        ildaShot.draw(x, y, w, h);
    }else{
        ildaFrame.draw(x, y, w, h);
    }
    
    if (showCurve) {
        redCurve.draw(ofGetWidth()-830, 10);
        greenCurve.draw(ofGetWidth()-540, 10);
        blueCurve.draw(ofGetWidth()-270, 10);
    }
//    gui->draw();
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
    
    if (cmd == name){
        
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
        else if (cmd == "spacing"){
            doSpacing = m.getArgAsInt32(0);
        }
        else if (cmd == "calib"){
            drawCalib = m.getArgAsInt32(0);
        }
        
    }
}