//
//  RenderSub.h
//  SplitAnimatedLaser_test_project
//
//  Created by pach on 04/08/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "RenderFrame.h"
//#include "ofxHomography.h"

class RenderSub{
    
public:
    RenderSub();
    ~RenderSub();
    
    void setup();
    void update();
    void draw(int x, int y, int w, int h);
    void load();
    void save();
    void setName(string name);

    
    inline void setMainFrame (RenderFrame * fr){
        mainFrame = fr;
    }
    void setBoundingBox(float x, float y, float w, float h);
    
//    void setHomographySrc(ofVec2f a, ofVec2f b, ofVec2f c, ofVec2f d);
    
    vector<ofPolyline> getSubFrame();
    
private:
    ofPoint getIntersectPoint(ofPoint &p1, ofPoint &p2);
    ofPoint getReverseIntersectPoint(ofPoint &p1, ofPoint &p2);
    
    ofPoint rescale(ofPoint p);
    void createSubFrame();
    
    
    RenderFrame * mainFrame;
    vector <ofPolyline> polys;
    
    ofRectangle boundingBox;
    ofVec2f scale;
    ofVec2f translate;
    
    string renderName;
    
//    bool doHomography;
};
