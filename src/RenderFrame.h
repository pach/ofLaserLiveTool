//
//  RenderFrame.h
//  SplitAnimatedLaser_test_project
//
//  Created by pach on 04/08/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"


class RenderFrame{
    
public:
    RenderFrame();
    ~RenderFrame();
    
    void setup();
    void update();
    void draw(int x, int y, int w, int h);
    vector<ofPolyline> getPolys();
    vector<ofFloatColor> getColors();
    void setPolys(vector <ofPolyline> newPolys);
    void addPolys(vector <ofPolyline> newPolys);
    void setPolys(vector <ofPolyline> newPolys, vector<ofFloatColor> colors);
    void addPolys(vector <ofPolyline> newPolys, vector<ofFloatColor> colors);
    void clear();
    
private:
    vector<ofPolyline> polys;
    vector<ofFloatColor> polyColors;
};
