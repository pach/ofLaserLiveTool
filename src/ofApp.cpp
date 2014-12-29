#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(125);
    
    
    ofxTimeline::removeCocoaMenusFromGlut("Laser Anim Toolbox");
    
    ilda.setup();
    ilda.load();
    
    animManager.setup();
    
    animManager.setDrawWidth(150);
    animManager.setDrawHeight(150);
    animManager.setDrawOffset(ofVec2f(ofGetWidth()-400., ofGetHeight()-200));
    
    animManager.setGuiOffset(ofVec2f(ilda.getGuiWidth()+10., 0.));
    
    
//    oscSender.setup(OSC_ASPI_ADDR, OSC_ASPI_PORT);
    oscTimeDelay = 0.2;
    lastOscTime = 0;
    
    oscReceive.setup(OSC_LISTENING_PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    animManager.update();
    
    if (ofGetElapsedTimef()-lastOscTime > oscTimeDelay) {
        
        
        lastOscTime = ofGetElapsedTimef();
    }
    
    ilda.clear();
    
    vector<ofPolyline> polys = animManager.getPolylines();
    for (int i = 0; i<polys.size(); i++) {
        ilda.addPoly(polys[i]);
    }
    
    ilda.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    animManager.draw();
    
    ilda.draw(ofGetWidth()-200, ofGetHeight()-200, 150, 150);
}

void ofApp::exit(){
    ilda.save();
    animManager.save();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' '){
        animManager.togglePlay();
    }
    if (key == 's'){
        ilda.save();
        animManager.save();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
