//
//  RenderSub.cpp
//  SplitAnimatedLaser_test_project
//
//  Created by pach on 04/08/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//


#include "RenderSub.h"

RenderSub::RenderSub(){
    
}

RenderSub::~RenderSub(){
    mainFrame = NULL;
}


void RenderSub::setup() {
    mainFrame = NULL;
    renderName="..";
    setBoundingBox(0., 0., 1., 1.);
}

void RenderSub::update() {
    polys.clear();
    createSubFrame();
}

vector<ofPolyline> RenderSub::getSubFrame(){
    return polys;
}

void RenderSub::load(){
    
}

void RenderSub::save(){
    
}

void RenderSub::setName(string name){
    renderName = name;
}

void RenderSub::createSubFrame(){
    bool lastInside = false;
    if (mainFrame != NULL) {
        ofPolyline newLine;
        vector<ofPolyline> mfPolys = mainFrame->getPolys();
        for (int i=0; i<mfPolys.size(); i++) {
            newLine.clear();
            lastInside = false;
            
            int p = 0;
            
            while (p<mfPolys[i].size()-1) {
                bool previousInside = lastInside;
                
                // si segment de polyline partant intersect (ou est inclu) dans la bounding box, ajout d'un point
                if (boundingBox.intersects(mfPolys[i][p], mfPolys[i][p+1])){
                    // si le point de départ est inclu dans la bounding box -> ajout du point
                    if (boundingBox.inside(mfPolys[i][p])) {
                        newLine.addVertex(rescale(mfPolys[i][p]));
                        lastInside = true;
                    }
                    else{
                        if (previousInside) {
                            newLine.addVertex(rescale(getIntersectPoint(mfPolys[i][p-1], mfPolys[i][p])));
                            polys.push_back(newLine);
                            
                            newLine.clear();
                            lastInside = false;
                            previousInside = false; // already added - bypass end condition test
                        }
                        
                        if (!boundingBox.inside(mfPolys[i][p+1])){
                            newLine.addVertex(rescale(getIntersectPoint(mfPolys[i][p], mfPolys[i][p+1])));
                            newLine.addVertex(rescale(getReverseIntersectPoint(mfPolys[i][p], mfPolys[i][p+1])));
                            polys.push_back(newLine);
                            newLine.clear();
                            lastInside = false;
                        }
                        else{
                            newLine.addVertex(rescale(getIntersectPoint(mfPolys[i][p], mfPolys[i][p+1])));
                            lastInside = true;
                        }
                    }
                }
                else{
                    lastInside = false;
                }
                
                if (previousInside && !lastInside) {
                    newLine.addVertex(rescale(getIntersectPoint(mfPolys[i][p-1], mfPolys[i][p])));
                    polys.push_back(newLine);
                    
                    newLine.clear();
                }
                p ++;
                
            }
            if (boundingBox.inside(mfPolys[i][p])) {
                newLine.addVertex(rescale(mfPolys[i][p]));
                polys.push_back(newLine);
            }else if (lastInside){
                newLine.addVertex(rescale(getIntersectPoint(mfPolys[i][p-1], mfPolys[i][p])));
                polys.push_back(newLine);
            }
        }
    }
}

ofPoint RenderSub::rescale(ofPoint p){
    return (p-translate)*scale;
}

ofPoint RenderSub::getIntersectPoint(ofPoint &p1, ofPoint &p2){
    // recherche avec quel segment du carré il y a intersection
    bool foundSide = false;
    int testedSide = 0;
    ofRectangle segmentBound ;
    
    while (!foundSide && testedSide<4) {
        if(testedSide == 0){
            segmentBound = ofRectangle(boundingBox.x, boundingBox.y, boundingBox.width, 0.0001);
        }else if(testedSide == 1){
            segmentBound = ofRectangle(boundingBox.x+boundingBox.width, boundingBox.y, 0.0001, boundingBox.height);
        }else if (testedSide == 2){
            segmentBound = ofRectangle(boundingBox.x, boundingBox.y+boundingBox.height, boundingBox.width, 0.0001);
        }else{
            segmentBound = ofRectangle(boundingBox.x, boundingBox.y, 0.0001, boundingBox.height);
        }
        
        if (segmentBound.intersects(p1, p2)) {
            foundSide = true;
        }
        else{
            testedSide++;
        }
    }
    
    if (!foundSide) {
        return p1.interpolate(p2, 0.5);
    }
    
    float dirCoeff = (p2.y - p1.y) / (p2.x - p1.x);
    float bCoeff = p1.y-dirCoeff*p1.x;
    
    // horizontal
    if (testedSide %2) {
        return ofPoint(segmentBound.x, dirCoeff*segmentBound.x+bCoeff);
    }
    // vertical
    else{
        return ofPoint((segmentBound.y-bCoeff)/dirCoeff, segmentBound.y);
    }
}
ofPoint RenderSub::getReverseIntersectPoint(ofPoint &p1, ofPoint &p2){
    // recherche avec quel segment du carré il y a intersection, ordre des segment inverse
    bool foundSide = false;
    int testedSide = 3;
    ofRectangle segmentBound ;
    
    while (!foundSide && testedSide>=0) {
        if(testedSide == 0){
            segmentBound = ofRectangle(boundingBox.x, boundingBox.y, boundingBox.width, 0.0001);
        }else if(testedSide == 1){
            segmentBound = ofRectangle(boundingBox.x+boundingBox.width, boundingBox.y, 0.0001, boundingBox.height);
        }else if (testedSide == 2){
            segmentBound = ofRectangle(boundingBox.x, boundingBox.y+boundingBox.height, boundingBox.width, 0.0001);
        }else{
            segmentBound = ofRectangle(boundingBox.x, boundingBox.y, 0.0001, boundingBox.height);
        }
        
        if (segmentBound.intersects(p1, p2)) {
            foundSide = true;
        }
        else{
            testedSide--;
        }
    }
    
    if (!foundSide) {
        return p1.interpolate(p2, 0.5);
    }
    
    float dirCoeff = (p2.y - p1.y) / (p2.x - p1.x);
    float bCoeff = p1.y-dirCoeff*p1.x;
    
    // horizontal
    if (testedSide %2) {
        return ofPoint(segmentBound.x, dirCoeff*segmentBound.x+bCoeff);
    }
    // vertical
    else{
        return ofPoint((segmentBound.y-bCoeff)/dirCoeff, segmentBound.y);
    }
}

void RenderSub::setBoundingBox(float x, float y, float w, float h){
    boundingBox.set(x, y, w, h);
    scale.set(1./ofVec2f(w, h));
    translate.set(x, y);
    
    ofLogNotice("setting render sub "+renderName+" to bound "+ofToString(boundingBox)+" scale "+ofToString(scale)+" translate "+ofToString(translate));
}

void RenderSub::draw(int x, int y, int w, int h) {
    ofSetColor(0);
    ofFill();
    ofRect(x, y, w, h);
    
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(x, y);
    ofScale(w, h);
    for (int i=0; i<polys.size(); i++) {
        polys[i].draw();
    }

    ofPopMatrix();
}
