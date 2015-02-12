#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(125);
    
    
//    ofxTimeline::removeCocoaMenusFromGlut("Laser Anim Toolbox");
    
    ilda.setup();
    ilda.load();
    
    animManager1.setup();
    animManager1.setDrawWidth(150);
    animManager1.setDrawHeight(150);
    animManager1.setDrawOffset(ofVec2f(ofGetWidth()-400., ofGetHeight()-400));
    animManager1.setGuiOffset(ofVec2f(ilda.getGuiWidth()+150., 0.));
    animManager1.setName("layer.1");
    
    animManager2.setup();
    animManager2.setDrawWidth(150);
    animManager2.setDrawHeight(150);
    animManager2.setDrawOffset(ofVec2f(ofGetWidth()-400., ofGetHeight()-200));
    animManager2.setGuiOffset(ofVec2f(ilda.getGuiWidth()+150., 0.));
    animManager2.setName("layer.2");

    ildaTabs.setup();
    ildaTabs.setPosition(0, 0);
    ildaTabs.addCanvas(animManager1.getGui());
    
    animManagerTabs.setup();
    animManagerTabs.setPosition(ilda.getGuiWidth()+150., 0.);
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
    
    ilda.clear();
    
    vector<ofPolyline> polys = animManager1.getPolylines();
    for (int i = 0; i<polys.size(); i++) {
        ilda.addPoly(polys[i]);
    }
//    polys = animManager2.getPolylines();
//    for (int i = 0; i<polys.size(); i++) {
//        ilda.addPoly(polys[i]);
//    }
    
    ilda.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    animManager1.draw();
    animManager2.draw();
    
    ilda.draw(ofGetWidth()-200, ofGetHeight()-200, 150, 150);
}

void ofApp::exit(){
    ilda.save();
    animManager1.save();
    animManager2.save();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's'){
        ilda.save();
        animManager1.save();
        animManager2.save();
    }
    if (key=='1'){
        ilda.setIdEtherdream(0);
    }
    else if (key == '2'){
        ilda.setIdEtherdream(1);
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
        ilda.parseOSC(m);
    }
}
