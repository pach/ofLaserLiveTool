//
//  AnimatedSvg.cpp
//  LaserAnimTool
//
//  Created by pach on 14/09/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "AnimatedSvg.h"

AnimatedSvg::AnimatedSvg(){
    
}

AnimatedSvg::~AnimatedSvg(){
     AnimatedStuff::~AnimatedStuff();
}


void AnimatedSvg::setup(string name) {
    AnimatedStuff::setup(name);
    type = "AnimatedSvg";
    
    pos = ofPoint (0.5f, 0.5f);
    rot = 0.0f;
    size = 0.0f;
    
    hasLoaded = false;
    filename = "none";
    doLoad = false;
    
    type = "AnimatedSvg";
    gui->addSlider("size", 0., 1., &size);
    gui->addSlider("rot", 0., 360., &rot);
    gui->add2DPad("pos", ofxUIVec2f(0., 1.), ofxUIVec2f(0., 1.), &pos);
//    gui->addTextInput("filename", filename);
    gui->addButton("load svg", &doLoad);
    
    ofAddListener(gui->newGUIEvent,this,&AnimatedSvg::textInputEvent);
    
    load();
    
//    if (filename != "none"){
//        svg.load(filename);
//        hasLoaded = true;
//    }
}

void AnimatedSvg::textInputEvent(ofxUIEventArgs &e){
    
    if(e.getName() == "filename")
    {
        ofxUITextInput *ti = (ofxUITextInput *) e.widget;
        if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
            cout << "ON ENTER: ";
        }
        else if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
        {
            cout << "ON FOCUS: ";
        }
        else if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
        {
            cout << "ON BLUR: ";
        }
        string output = ti->getTextString();
        cout << output << endl;
        
        filename = ti->getTextString();
        hasLoaded = false;
    }
}

void AnimatedSvg::processOpenFileSelection(ofFileDialogResult openFileResult){
	
	ofLogVerbose("getName(): "  + openFileResult.getName());
	ofLogVerbose("getPath(): "  + openFileResult.getPath());
	
	ofFile file (openFileResult.getPath());
	
	if (file.exists()){
		
		ofLogVerbose("The file exists - now checking the type via file extension");
		string fileExtension = ofToUpper(file.getExtension());
		
		//We only want images
		if (fileExtension == "SVG") {
			
            filename = openFileResult.getName();
            
            svg.clear();
            svg.setup();
            
            svg.load(openFileResult.getPath());
            
            hasLoaded = true;
			
		}
	}
	
}


void AnimatedSvg::update() {
    
    svg.update();
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
    
    if (!hasLoaded){
        if (filename != "none"){
            svg.clear();
            svg.load(filename);
            hasLoaded = true;
        }
    }else{
        polylines.clear();
        ofPolyline p;
        while (svg.hasNextPolyline()){
            p.clear();
            p = svg.getPolyline();
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
        }
    }
    
}