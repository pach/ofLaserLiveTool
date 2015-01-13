//
//  SvgLoader.cpp
//  laserControl
//
//  Created by pach on 26/05/14.
//
//

#include "SvgLoader.h"
#include "ofxSvg.h"

void SvgLoader::setup(){
    curPoly = 0;
}

void SvgLoader::update(){
    
}

void SvgLoader::draw(){
    svg.draw();
    
}

void SvgLoader::clear(){
    polypocket.clear();
}

bool SvgLoader::hasNextPolyline(){
    bool hasPoly = curPoly < polypocket.size();
    if (curPoly >= polypocket.size())
        curPoly = 0;
    return hasPoly;
}

ofPolyline SvgLoader::getPolyline(){
    if (!hasNextPolyline()){
        return ;
    }
    ofPolyline poly = polypocket.at(curPoly);
    curPoly ++;
    return poly;
    
}

void SvgLoader::load(string filename){
    clear();
    
    cout<<"loading svg "<<filename<<endl;
    
//    ofxSVG svg ;
    svg.load(filename);
    
    ofVec2f svgSize = ofVec2f(svg.getWidth(), svg.getHeight());
    
    bool doesClose = false;
    
    for (int i=0; i<svg.getNumPath(); i++) {
        ofPath path = svg.getPathAt(i);
        vector<ofPolyline> polypath = path.getOutline();
        for (int j=0; j<polypath.size(); j++) {
            ofPolyline poly = polypath.at(j);
            vector<ofPoint> polyPoints = poly.getVertices();
            doesClose = poly.isClosed();
            poly.clear();
            // normalize the line
            for (int k =0 ; k<polyPoints.size() ; k++){
                poly.addVertex(polyPoints.at(k).x/svgSize.x, polyPoints.at(k).y/svgSize.y);
            }
            if (doesClose){
                poly.close();
            }
            
            polypocket.push_back(poly);
        }
    }
}