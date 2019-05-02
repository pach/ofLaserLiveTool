//
//  AnimatedSvg.cpp
//  LaserAnimTool
//
//  Created by pach on 14/09/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

/* possible d'animer avec adobe animate + plugin https://www.adobeexchange.com/creativecloud.details.7232.html */

#include "AnimatedMultiSvg.h"

AnimatedMultiSvg::AnimatedMultiSvg(){
    
}

AnimatedMultiSvg::~AnimatedMultiSvg(){
    AnimatedStuff::~AnimatedStuff();
}

void AnimatedMultiSvg::load(string layerName){
    AnimatedStuff::load(layerName);
    
    ofxXmlSettings loadFile ;
    loadFile.load(layerName+"/"+name+"_gui.xml");
    if (loadFile.tagExists("dirpath")){
        dirname = loadFile.getValue("dirpath", dirname);
        loadFromDir(dirname);
    }
}

void AnimatedMultiSvg::save(string layerName){
    AnimatedStuff::save(layerName);
    
    if (hasLoaded){
        ofxXmlSettings saveFile ;
        saveFile.load(layerName+"/"+name+"_gui.xml");
        saveFile.addValue("dirpath", dirname);
        saveFile.saveFile();
    }
}

void AnimatedMultiSvg::loadFromDir(string dirPath){
    ofDirectory dir;
    dir.open(dirname);
    dir.sort();
    
    ofLog(OF_LOG_NOTICE, "loading svg from dir "+dirname);
    
    svgVec.clear();
    
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
    if (svgVec.size()>0){
        hasLoaded = true;
        restart = true;
    }
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
    
    restart = false;
    
    idSvg = 0;
    svgTime = 0.04;
    
    doSpacing = true;
    nbPointSpacing = 700;
    
    gui->addSlider("size", 0., 1., &size);
    gui->addSlider("rot", 0., 360., &rot);
    gui->addSlider("svgTime", 0.01, 1., &svgTime);
    gui->add2DPad("pos", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &pos);
    //    gui->addTextInput("filename", filename);
    gui->addButton("directory", &doLoad);
    gui->addButton("restart", &restart);
    
    gui->addButton("doSpacing", &doSpacing);
    gui->addIntSlider("nbPointSpacing", 100, 2000, &nbPointSpacing);
    
    
//    ofAddListener(gui->newGUIEvent,this,&AnimatedMultiSvg::textInputEvent);
    
//    load();
    
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
//            ofDirectory dir;
            dirname = path.getEnclosingDirectory(openFileResult.getPath());
            loadFromDir(dirname);
//            dir.open(dirname);
//            dir.sort();
//            for (ofFile file : dir.getFiles()){
//                if (file.getExtension() == "svg"){
//                    SvgLoader svg ;
//                    svg.setup();
//                    svg.load(file.getAbsolutePath());
//                    svgVec.push_back(svg);
//                }
//            }
////            svg.clear();
////            svg.setup();
////
////            svg.load(openFileResult.getPath());
//
//            hasLoaded = true;
//            restart = true;
        }
    }
    
}


void AnimatedMultiSvg::update() {
    AnimatedStuff::update();
    
    if (restart){
        restart = 0;
        idSvg = 0;
        svgStartTime = ofGetElapsedTimef();
    }
    
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
//    if (ofGetElapsedTimef()>svgLastTime+svgTime){
//        svgLastTime = ofGetElapsedTimef();
//        idSvg ++;
//        if (idSvg >= svgVec.size())
//            idSvg = 0;
//    }
    idSvg = floor((ofGetElapsedTimef()-svgStartTime)/svgTime);
    
    if (idSvg >= svgVec.size()){
        idSvg = svgVec.size()-1;
        restart = true;
    }
    
    polylines.clear();
    colors.clear();
    
//    for (SvgLoader &svg : svgVec){
    if (hasLoaded){
        SvgLoader &svg = svgVec[idSvg];
        svg.update();
        
        ofPolyline p;
        ofFloatColor c ;
        int nbPoly = svg.getNbPoly();
        while (svg.hasNextPolyline()){
            p.clear();
            c = svg.getCurrentColor();
            p = svg.getPolyline();
            
            if (doSpacing){
                p = p.getResampledByCount(nbPointSpacing/nbPoly);
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
    
}

void AnimatedMultiSvg::draw(){
    
    AnimatedStuff::draw();
    
    ofDrawBitmapString("svg frame "+ofToString(idSvg), ofGetWidth()-250, ofGetHeight()-20);
}

void AnimatedMultiSvg::parseOSC(ofxOscMessage &m){

    vector<string> osc = getOSCcmd(m.getAddress());
    string cmd = osc[0];
    string msg = osc[1];
    
    if (cmd == "svg"){
        osc = getOSCcmd(msg);
        string cmd = osc[0];
        string msg = osc[1];
        
//        ofLog (OF_LOG_NOTICE, "received osc message for svg : "+cmd);
        
        if (cmd == "pos"){
            pos = ofPoint(ofMap(m.getArgAsFloat(0), 0, 1, -0.5, 0.5), ofMap(m.getArgAsFloat(1), 0, 1, -0.5, 0.5));
        }
        else if (cmd == "size"){
            size = m.getArgAsFloat(0);
        }
        else if (cmd == "rot"){
            rot = m.getArgAsFloat(0);
        }
        else if (cmd == "restart"){
            restart = true;
        }
        else if (cmd == "speed"){
            svgTime = m.getArgAsFloat(0);
        }
    }
}
