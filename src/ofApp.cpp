#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(125);
    
    
//    ofxTimeline::removeCocoaMenusFromGlut("Laser Anim Toolbox");
    
    ilda1.setup(0);
    ilda1.setName("laser.1");
    ilda1.load();
    
    ilda2.setup(1);
    ilda2.setName("laser.2");
    ilda2.load();
    
    animManager1.setup();
    animManager1.setDrawWidth(150);
    animManager1.setDrawHeight(150);
    animManager1.setDrawOffset(ofVec2f(ofGetWidth()-400., ofGetHeight()-400));
    animManager1.setGuiOffset(ofVec2f(ilda1.getGuiWidth()+150., 0.));
    animManager1.setName("layer.1");
    
    animManager2.setup();
    animManager2.setDrawWidth(150);
    animManager2.setDrawHeight(150);
    animManager2.setDrawOffset(ofVec2f(ofGetWidth()-400., ofGetHeight()-200));
    animManager2.setGuiOffset(ofVec2f(ilda1.getGuiWidth()+150., 0.));
    animManager2.setName("layer.2");

    ildaTabs.setup();
    ildaTabs.setPosition(0, 0);
    ildaTabs.addCanvas(ilda1.getGui());
    ildaTabs.addCanvas(ilda2.getGui());
    
    animManagerTabs.setup();
    animManagerTabs.setPosition(ilda1.getGuiWidth()+150., 0.);
    animManagerTabs.addCanvas(animManager1.getGui());
    animManagerTabs.addCanvas(animManager2.getGui());
    

    
//    oscSender.setup(OSC_ASPI_ADDR, OSC_ASPI_PORT);
    oscTimeDelay = 0.2;
    lastOscTime = 0;
    
    oscReceive.setup(OSC_LISTENING_PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    parseOSC();
    
    animManager1.update();
    animManager2.update();
    
    if (ofGetElapsedTimef()-lastOscTime > oscTimeDelay) {
        
        
        lastOscTime = ofGetElapsedTimef();
    }
    
    ilda1.clear();
    ilda2.clear();
    
    vector<ofPolyline> polys = animManager1.getPolylines();
    for (int i = 0; i<polys.size(); i++) {
        ilda1.addPoly(polys[i]);
    }
    polys.clear();
    polys = animManager2.getPolylines();
    for (int i = 0; i<polys.size(); i++) {
        ilda2.addPoly(polys[i]);
    }
    
    ilda1.update();
    ilda2.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    animManager1.draw();
    animManager2.draw();
    
    ilda1.draw(ofGetWidth()-200, ofGetHeight()-400, 150, 150);
    ilda2.draw(ofGetWidth()-200, ofGetHeight()-200, 150, 150);
}

void ofApp::exit(){
    ilda1.save();
    ilda2.save();
    animManager1.save();
    animManager2.save();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's'){
        ilda1.save();
        ilda2.save();
        animManager1.save();
        animManager2.save();
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

void ofApp::parseOSC(){
    while (oscReceive.hasWaitingMessages()){
        ofxOscMessage m ;
        oscReceive.getNextMessage(&m);
        
        cout<<"just received OSC "<<m.getAddress()<<endl;
        animManager1.parseOSC(m);
        animManager2.save();
        ilda1.parseOSC(m);
        ilda2.parseOSC(m);
    }
}
