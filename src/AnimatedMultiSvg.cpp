//
//  AnimatedSvg.cpp
//  LaserAnimTool
//
//  Created by pach on 14/09/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "AnimatedMultiSvg.h"

AnimatedMultiSvg::AnimatedMultiSvg(){
    
}

AnimatedMultiSvg::~AnimatedMultiSvg(){
    AnimatedStuff::~AnimatedStuff();
}


void AnimatedMultiSvg::setup(string name) {
    AnimatedStuff::setup(name);
    type = "AnimatedMultiSvg";
    
    pos = ofPoint (0.5f, 0.5f);
    rot = 0.0f;
    size = 0.0f;
    
    hasLoaded = false;
    dirname = "none";
    doLoad = false;
    
    idSvg = 0;
    svgTime = 0.1;
    
    doSpacing = true;
    nbPointSpacing = 700;
    
    gui->addSlider("size", 0., 1., &size);
    gui->addSlider("rot", 0., 360., &rot);
    gui->addSlider("svgTime", 0.05, 1., &svgTime);
    gui->add2DPad("pos", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &pos);
    //    gui->addTextInput("filename", filename);
    gui->addButton("directory", &doLoad);
    
    gui->addButton("doSpacing", &doSpacing);
    gui->addIntSlider("nbPointSpacing", 100, 1000, &nbPointSpacing);
    
    
//    ofAddListener(gui->newGUIEvent,this,&AnimatedMultiSvg::textInputEvent);
    
    load();
    
    //    if (filename != "none"){
    //        svg.load(filename);
    //        hasLoaded = true;
    //    }
}

//void AnimatedMultiSvg::textInputEvent(ofxUIEventArgs &e){
//
//    if(e.getName() == "directory")
//    {
//        ofxUITextInput *ti = (ofxUITextInput *) e.widget;
//        if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
//        {
//            cout << "ON ENTER: ";
//        }
//        else if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
//        {
//            cout << "ON FOCUS: ";
//        }
//        else if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
//        {
//            cout << "ON BLUR: ";
//        }
//        string output = ti->getTextString();
//        cout << output << endl;
//
//        dirname = ti->getTextString();
//        hasLoaded = false;
//    }
//}

void AnimatedMultiSvg::processOpenFileSelection(ofFileDialogResult openFileResult){
    
    ofLogVerbose("getName(): "  + openFileResult.getName());
    ofLogVerbose("getPath(): "  + openFileResult.getPath());
    
    ofFile file (openFileResult.getPath());
    
    if (file.exists()){
        
        ofLogVerbose("The file exists - now checking the type via file extension");
        string fileExtension = ofToUpper(file.getExtension());
        
        //We only want images
        if (fileExtension == "SVG") {
            ofFilePath path ;
            ofDirectory dir;
            dirname = path.getEnclosingDirectory(openFileResult.getPath());
            dir.open(dirname);
            dir.sort();
            for (ofFile file : dir.getFiles()){
                if (file.getExtension() == "svg"){
                    SvgLoader svg ;
                    svg.setup();
                    svg.load(file.getAbsolutePath());
                    svgVec.push_back(svg);
                }
            }
//            svg.clear();
//            svg.setup();
//
//            svg.load(openFileResult.getPath());
            
            hasLoaded = true;
            
        }
    }
    
}


void AnimatedMultiSvg::update() {
    AnimatedStuff::update();
    
    if (doLoad) {
        ofLogVerbose("opening file");
        
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a svg file");
        
        //Check if the user opened a file
        if (openFileResult.bSuccess){
            //We have a file, check it and process it
            processOpenFileSelection(openFileResult);
            ofLogVerbose("success");
        }else{
            ofLogVerbose("fail");
        }
        
        doLoad = false;
    }
    
    // update time
    if (ofGetElapsedTimef()>lastTime+svgTime){
        lastTime = ofGetElapsedTimef();
        idSvg ++;
        if (idSvg > svgVec.size())
            idSvg = 0;
    }
    
    polylines.clear();
    
//    for (SvgLoader &svg : svgVec){
    if (hasLoaded){
        SvgLoader &svg = svgVec[idSvg];
        svg.update();
        
        ofPolyline p;
        ofFloatColor c ;
        while (svg.hasNextPolyline()){
            p.clear();
            c = svg.getCurrentColor();
            p = svg.getPolyline();
            if (doSpacing){
                p = p.getResampledByCount(nbPointSpacing);
            }
            // size and rot
            for (int i=0; i<p.size(); i++) {
                ofVec2f pt = p[i];
                pt.x *= 2.;
                pt.x -= 1.;
                pt.y *= 2.;
                pt.y -= 1.;

                pt *= size;
                pt.rotate(rot);
                p[i] = pos+pt;
            }
            polylines.push_back(p);
            colors.push_back(c);
        }
        
    }
    
   
    
//    if (!hasLoaded){
//        if (filename != "none"){
//            svg.clear();
//            svg.load(filename);
//            hasLoaded = true;
//        }
//    }else{
//        polylines.clear();
//        ofPolyline p;
//        while (svg.hasNextPolyline()){
//            p.clear();
//            p = svg.getPolyline();
//            if (doSpacing){
//                p = p.getResampledByCount(nbPointSpacing);
//            }
//            // size and rot
//            for (int i=0; i<p.size(); i++) {
//                ofVec2f pt = p[i];
//                pt.x *= 2.;
//                pt.x -= 1.;
//                pt.y *= 2.;
//                pt.y -= 1.;
//
//                pt *= size;
//                pt.rotate(rot);
//                p[i] = pos+pt;
//            }
//            polylines.push_back(p);
//        }
//    }
    
}
