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
#include "ofxHomography.h"

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
    
    // top left
    void setHomographySrcA(ofVec2f a);
    // top right
    void setHomographySrcB(ofVec2f b);
    // bottom right
    void setHomographySrcC(ofVec2f c);
    // bottom left
    void setHomographySrcD(ofVec2f d);
    void resetHomographySrc();
    void resetHomographyDst();
    void computeHomography();
    
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
    
    bool doHomography;
    ofMatrix4x4 homography;
    ofPoint srcCornerHomo [4] ;
    ofPoint dstCornerHomo [4] ;
};
