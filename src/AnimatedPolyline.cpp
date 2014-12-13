//
//  AnimatedPolyline.cpp
//  LaserAnimTool
//
//  Created by pach on 29/05/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "AnimatedPolyline.h"
#include "ofxTLTrackHeader.h"

AnimatedPolyline::AnimatedPolyline(){
//    AnimatedStuff::AnimatedStuff();
}

AnimatedPolyline::~AnimatedPolyline(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedPolyline::setup(string name) {
    AnimatedStuff::setup(name);
    pickingDistance = 0.1;
    timeKeyPickDistance = 10;
    
    type = "AnimatedPolyline";
    
    gui->addSpacer();
    gui->addButton("add point", false);
    gui->addButton("remove selected point", false);
    
    ofPolyline p;
    polylines.push_back(p);
    
    ofAddListener(gui->newGUIEvent,this,&AnimatedPolyline::guiEvent);
    
    load();
}

void AnimatedPolyline::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
    
    if (name == "add point"){
        ofxUIButton *button = (ofxUIButton *) e.widget;
        if(button->getValue() == 1){
            addPoint(ofPoint(0.5, 0.5));
        }
    }
    else if (name == "remove selected point" && pointPickedId != -1){
        ofxUIButton *button = (ofxUIButton *) e.widget;
        if(button->getValue() == 1){
            removePoint(pointPickedId);
        }
    }
}


void AnimatedPolyline::update() {
    vector<ofPoint> & vertices = polylines[0].getVertices();
    for (int i=0; i<vertices.size(); i++) {
        vertices[i].x = timeline.getValue(name+"."+ofToString(i)+".x");
        vertices[i].y = timeline.getValue(name+"."+ofToString(i)+".y");
    }
}

void AnimatedPolyline::draw() {
    
    ofSetColor(0);
    ofRect(drawOffset, drawW, drawH);
    
    ofPushMatrix();
    ofSetColor(255);
    
    ofTranslate(drawOffset);
    ofScale(drawW, drawH);
    
    polylines[0].draw();
    
    if (isSelected) {
        ofSetColor(255, 0, 0);
        vector<ofPoint> & vertices = polylines[0].getVertices();
        for (int i=0; i<vertices.size(); i++) {
            if(i==pointPickedId){
                ofFill();
            }
            else{
                ofNoFill();
            }
            ofCircle(vertices[i], pickingDistance);
        }
    }
    
    ofPopMatrix();
}


void AnimatedPolyline::save(){
    cout<<"saving animated polyline "<<name<<endl;
    
    // is their a way to call the super class method?
    timeline.save();
    gui->saveSettings(name+"_gui.xml");
    
    timeline.setCurrentTimeMillis(0);
    ofxXmlSettings xml;
    xml.addTag("POLYLINE");
    xml.pushTag("POLYLINE");
    
    for (int i=0 ; i<polylines[0].size(); i++){
        int idTag = xml.addTag("POINT");
        xml.setValue("POINT:X", polylines[0][i].x, idTag);
        xml.setValue("POINT:Y", polylines[0][i].y, idTag);
    }
    
    xml.popTag();
    
    xml.save(name+".xml");
}

void AnimatedPolyline::load(){
    cout<<"loading animated polyline "<<name<<endl;
    
    // is their a way to call the super class method?
    gui->loadSettings(name+"_gui.xml");
    timeline.loadTracksFromFolder(ofToDataPath(""));
    
    ofxXmlSettings xml;
    xml.load(name+".xml");
    xml.pushTag("POLYLINE", 0);
    
    int nbPoint = xml.getNumTags("POINT");
    
    for (int i=0 ; i<nbPoint ; i++){
        addPoint(ofPoint(xml.getValue("POINT:X", 0, i), xml.getValue("POINT:X", 0, i)));
    }
    
    xml.popTag();
}



void AnimatedPolyline::setActivePoint(int idPoint){
    pointPickedId = idPoint;
    if (idPoint != -1){
        timeline.getPage(name)->setExpandToHeight(400);
        timeline.getPage(name)->evenlyDistributeTrackHeights();
        for (int i=0 ; i<polylines[0].size() ; i++){
            if (i!=idPoint){
                timeline.getPage(name)->collapseTrack(timeline.getTrack(name+"."+ofToString(i)+".x"));
                timeline.getPage(name)->collapseTrack(timeline.getTrack(name+"."+ofToString(i)+".y"));
            }
    //        else{
    //            timeline.getPage(name)->expandTrack(timeline.getTrack(name+"."+ofToString(i)+".x"));
    //            timeline.getPage(name)->expandTrack(timeline.getTrack(name+"."+ofToString(i)+".y"));
    //        }
        }
    }
    
}

void AnimatedPolyline::addPoint(ofPoint pos){
    int id = polylines[0].size();
    polylines[0].addVertex(pos);
    
    timeline.addCurves(name+"."+ofToString(id)+".x");
    timeline.addCurves(name+"."+ofToString(id)+".y");
    
    

//    ofxTLKeyframes * key = dynamic_cast<ofxTLKeyframes *>(timeline.getTrack(name+"."+ofToString(id)+".x"));
//    ofxTLCurves * key = (ofxTLCurves *)(timeline.getTrack(name+"."+ofToString(id)+".x"));
//    key->addKeyframe(pos.x);
    
//    key = dynamic_cast<ofxTLKeyframes *>(timeline.getTrack(name+"."+ofToString(id)+".y"));
//    key = (ofxTLCurves *)(timeline.getTrack(name+"."+ofToString(id)+".y"));
//    key->addKeyframe(pos.y);
}


void AnimatedPolyline::removePoint(int idPoint){
    
    ofLog(OF_LOG_NOTICE, "removing point "+ofToString(idPoint));
    
    vector<ofPoint> points = polylines[0].getVertices();
    polylines[0].clear();
    for (int i=0; i<points.size(); i++) {
        if (i!= idPoint){
            polylines[0].addVertex(points[i]);
        }
    }
    timeline.removeTrack(name+"."+ofToString(idPoint)+".x");
    timeline.removeTrack(name+"."+ofToString(idPoint)+".y");
}



void AnimatedPolyline::updatePoint(unsigned int idPoint, ofPoint pos){
    ofLog(OF_LOG_NOTICE, "update point "+ofToString(idPoint)+ " to pos "+ofToString(pos));
//    vector<ofPoint> & points = polyline.getVertices();
//    points[idPoint].set(pos.x, pos.y);
//
    // update x point
    ofxTLCurves * keysX = (ofxTLCurves *)(timeline.getTrack(name+"."+ofToString(idPoint)+".x"));
    vector<ofxTLKeyframe *> & keyframesX = keysX->getKeyframes();
    
    bool found = false;
    int idKey = -1;
    for (int i=0; i<keyframesX.size() && !found; i++) {
        if (keyframesX[i]->previousTime >= timeline.getCurrentTimeMillis()-timeKeyPickDistance
            && keyframesX[i]->previousTime <= timeline.getCurrentTimeMillis()+timeKeyPickDistance) {
            found = true;
            idKey = i;
        }
    }
    
    if (found){
        keysX->updateKey(idKey, pos.x);
        ofLog(OF_LOG_NOTICE, "updating x key "+ofToString(idKey)+" to pos "+ofToString(pos.x));
    }
    else {
        keysX->addKeyframe(pos.x);
        ofLog(OF_LOG_NOTICE, "adding a new x key ");
    }
    
    
    // update y point
    ofxTLCurves * keysY = (ofxTLCurves *)(timeline.getTrack(name+"."+ofToString(idPoint)+".y"));
    vector<ofxTLKeyframe *> & keyframesY = keysY->getKeyframes();
    
    found = false;
    for (int i=0; i<keyframesY.size() && !found; i++) {
        if (keyframesY[i]->previousTime >= timeline.getCurrentTimeMillis()-timeKeyPickDistance
            && keyframesY[i]->previousTime <= timeline.getCurrentTimeMillis()+timeKeyPickDistance) {
            found = true;
            idKey = i;
        }
    }
    
    if (found){
        keysY->updateKey(idKey, pos.y);
        ofLog(OF_LOG_NOTICE, "updating y key "+ofToString(idKey)+" to pos "+ofToString(pos.y));
    }
    else {
        keysY->addKeyframe(pos.y);
        ofLog(OF_LOG_NOTICE, "adding a new y key ");
    }
}



int AnimatedPolyline::getClosestPointId (ofPoint pos){
    unsigned int idPoint = -1;
    ofPoint p = polylines[0].getClosestPoint(pos, &idPoint);
    
    ofLog(OF_LOG_NOTICE, "closest point is "+ofToString(p)+" at distance of pos "+ofToString(p.distance(pos)));
    
    if (p.distance(pos)>pickingDistance){
        idPoint = -1;
    }
    return idPoint;
}




void AnimatedPolyline::mousePressed(ofMouseEventArgs& e){
    // y>drawOffset.y for being able to clic on gui without unselected point. C'est degueulasse mais ca marche.
    if (isSelected && e.y>drawOffset.y-50){
        ofPoint mousePoint = ofVec2f((float)(e.x-drawOffset.x)/(float)drawW, (float)(e.y-drawOffset.y)/(float)drawH);
        
        ofLog(OF_LOG_NOTICE, "mouse pressed at "+ofToString(mousePoint));
        
        int idPoint = getClosestPointId(mousePoint);
        if (idPoint != -1){
//            pointPickedId = idPoint;
            pointIsPicked = true;
            ofLog(OF_LOG_NOTICE, "picking point "+ofToString(idPoint));
        }
       setActivePoint(idPoint);
    }
}

void AnimatedPolyline::mouseDragged(ofMouseEventArgs& e){
    if (isSelected && pointIsPicked){
        ofLog(OF_LOG_NOTICE, "moving point "+ofToString(pointPickedId));
        ofPoint mousePoint = ofVec2f((float)(e.x-drawOffset.x)/(float)drawW, (float)(e.y-drawOffset.y)/(float)drawH);
        updatePoint(pointPickedId, mousePoint);
    }
}

void AnimatedPolyline::mouseReleased(ofMouseEventArgs& e){
    if (isSelected && pointIsPicked) {
//        ofPoint mousePoint = ofVec2f((float)(x-drawOffset.x)/(float)drawW, (float)(y-drawOffset.y)/(float)drawH);
//        updatePoint(pointPickedId, mousePoint);
        ofLog(OF_LOG_NOTICE, "release point "+ofToString(pointPickedId));
        pointIsPicked = false;
    }
}
