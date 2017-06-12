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
    setBoundingBox(0., 0., 1., 1.);
    homoBoundingBox.set(0., 0., 1., 1.);
    
    srcA.set("src A", ofVec2f(0., 0.), ofVec2f(-0.5, -0.5), ofVec2f(1.5, 1.5));
    srcB.set("src B", ofVec2f(1., 0.), ofVec2f(-0.5, -0.5), ofVec2f(1.5, 1.5));
    srcC.set("src C", ofVec2f(1., 1.), ofVec2f(-0.5, -0.5), ofVec2f(1.5, 1.5));
    srcD.set("src D", ofVec2f(0., 1.), ofVec2f(-0.5, -0.5), ofVec2f(1.5, 1.5));
    
    dstA.set("dst A", ofVec2f(0., 0.), ofVec2f(-0.5, -0.5), ofVec2f(1.5, 1.5));
    dstB.set("dst B", ofVec2f(1., 0.), ofVec2f(-0.5, -0.5), ofVec2f(1.5, 1.5));
    dstC.set("dst C", ofVec2f(1., 1.), ofVec2f(-0.5, -0.5), ofVec2f(1.5, 1.5));
    dstD.set("dst D", ofVec2f(0., 1.), ofVec2f(-0.5, -0.5), ofVec2f(1.5, 1.5));
    
    recomputeHomography.set("recompute Homography", false);
    doHomography.set("do Homography", false);
    doRecut.set("do recut homo", true);
    
    renderSubParams.setName(renderName);
    renderSubParams.add(srcA);
    renderSubParams.add(srcB);
    renderSubParams.add(srcC);
    renderSubParams.add(srcD);
    renderSubParams.add(dstA);
    renderSubParams.add(dstB);
    renderSubParams.add(dstC);
    renderSubParams.add(dstD);
    renderSubParams.add(recomputeHomography);
    renderSubParams.add(doHomography);
    renderSubParams.add(doRecut);
    
    resetHomographySrc();
    resetHomographyDst();
    
    computeHomography();
}

void RenderSub::resetHomographySrc(){
    srcCornerHomo[0].set(srcA->x, srcA->y);
    srcCornerHomo[1].set(srcB->x, srcB->y);
    srcCornerHomo[2].set(srcC->x, srcC->y);
    srcCornerHomo[3].set(srcD->x, srcD->y);
}

void RenderSub::resetHomographyDst(){
    dstCornerHomo[0].set(dstA->x, dstA->y);
    dstCornerHomo[1].set(dstB->x, dstB->y);
    dstCornerHomo[2].set(dstC->x, dstC->y);
    dstCornerHomo[3].set(dstD->x, dstD->y);
}

void RenderSub::update() {
    if (recomputeHomography){
        resetHomographySrc();
        resetHomographyDst();
        
        computeHomography();
        
//        recomputeHomography = false;
    }
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

void RenderSub::createSubFrame(){
    bool lastInside = false;
    if (mainFrame != NULL) {
        ofPolyline newLine;
        vector<ofPolyline> mfPolys = mainFrame->getPolys();
        
        if (doHomography){
            for (int i=0; i<mfPolys.size(); i++) {
                ofPolyline newPoly;
                
                for (int j=0 ; j<mfPolys[i].size() ; j++){
                    newPoly.addVertex(rescale(mfPolys[i][j]));
                }
                
                if (doRecut){
                    newLine.clear();
                    lastInside = false;
                    
                    int p = 0;
                    while (p<newPoly.size()-1) {
                        bool previousInside = lastInside;
                        
                        // si segment de polyline partant intersect (ou est inclu) dans la bounding box, ajout d'un point
                        if (homoBoundingBox.intersects(newPoly[p], newPoly[p+1])){
                            // si le point de départ est inclu dans la bounding box -> ajout du point
                            if (homoBoundingBox.inside(newPoly[p])) {
                                newLine.addVertex(newPoly[p]);
                                lastInside = true;
                            }
                            else{
                                if (previousInside) {
                                    newLine.addVertex(getIntersectPoint(newPoly[p-1], newPoly[p]));
                                    polys.push_back(newLine);
                                    
                                    newLine.clear();
                                    lastInside = false;
                                    previousInside = false; // already added - bypass end condition test
                                }
                                
                                if (!homoBoundingBox.inside(newPoly[p+1])){
                                    newLine.addVertex(getIntersectPoint(newPoly[p], newPoly[p+1]));
                                    newLine.addVertex(getReverseIntersectPoint(newPoly[p], newPoly[p+1]));
                                    polys.push_back(newLine);
                                    newLine.clear();
                                    lastInside = false;
                                }
                                else{
                                    newLine.addVertex(getIntersectPoint(newPoly[p], newPoly[p+1]));
                                    lastInside = true;
                                }
                            }
                        }
                        else{
                            lastInside = false;
                        }
                        
                        if (previousInside && !lastInside) {
                            newLine.addVertex(getIntersectPoint(newPoly[p-1], newPoly[p]));
                            polys.push_back(newLine);
                            
                            newLine.clear();
                        }
                        p ++;
                        
                    }
                    if (homoBoundingBox.inside(newPoly[p])) {
                        newLine.addVertex(newPoly[p]);
                        polys.push_back(newLine);
                    }else if (lastInside){
                        newLine.addVertex(getIntersectPoint(newPoly[p-1], newPoly[p]));
                        polys.push_back(newLine);
                    }
                }
                else {
                    polys.push_back(newPoly);
                }
                
                newPoly.clear();
            }
        }
        
        // bounding box classique
        else{
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
}

ofPoint RenderSub::rescale(ofPoint p){
    if (doHomography){
        return ofxHomography::toScreenCoordinates(p, homography);
    }
    else {
        return (p-translate)*scale;
    }
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

void RenderSub::setHomographySrcA(ofVec2f a){
    srcA = a;
    srcCornerHomo[0] = a;
    computeHomography();
}

void RenderSub::setHomographySrcB(ofVec2f b){
    srcB = b;
    srcCornerHomo[1] = b;
    computeHomography();
}

void RenderSub::setHomographySrcC(ofVec2f c){
    srcC = c;
    srcCornerHomo[2] = c;
    computeHomography();
}

void RenderSub::setHomographySrcD(ofVec2f d){
    srcD = d;
    srcCornerHomo[3] = d;
    computeHomography();
}

void RenderSub::computeHomography(){
    homography = ofxHomography::findHomography(srcCornerHomo, dstCornerHomo);
}
