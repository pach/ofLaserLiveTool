#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(125);
    
    
    ofxTimeline::removeCocoaMenusFromGlut("Laser Anim Toolbox");
    
    ilda.setup();
    ilda.load();
    
    animManager.setup();
    animManager.timeline.setDurationInSeconds(480);
    
//    animManager.timeline.addCurves("aspi_in");
//    animManager.timeline.addCurves("aspi_out");
//    animManager.timeline.addCurves("laser_nbPoints");
    
    animManager.setDrawWidth(150);
    animManager.setDrawHeight(150);
    animManager.setDrawOffset(ofVec2f(ofGetWidth()-400., ofGetHeight()-200));
    
    animManager.setGuiOffset(ofVec2f(ilda.getGuiWidth(), 0.));
    
    animManager.setTlWidth(ofGetWidth()-(ilda.getGuiWidth()*2));
    animManager.setTlOffset(ofVec2f((ilda.getGuiWidth()*2), 0.));
    
    
    
    oscSender.setup(OSC_ASPI_ADDR, OSC_ASPI_PORT);
    oscTimeDelay = 0.2;
    lastOscTime = 0;
    
    oscReceive.setup(OSC_LISTENING_PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    while (oscReceive.hasWaitingMessages()){
        ofxOscMessage m;
        oscReceive.getNextMessage(&m);
        if (m.getAddress() == "/time/millis"){
            float time = m.getArgAsFloat(0);
            animManager.timeline.setCurrentTimeMillis(time);
        }
    }
    
    animManager.update();
    
//    int aspi_in = ofMap(animManager.timeline.getValue("aspi_in"), 0., 1., 512, 200);
//    int aspi_out = ofMap(animManager.timeline.getValue("aspi_out"), 0., 1., 512, 215);
//    ilda.pointCount = ofMap(animManager.timeline.getValue("laser_nbPoints"), 0., 1., 2, 2500);
    
    if (ofGetElapsedTimef()-lastOscTime > oscTimeDelay) {
        
//        ofxOscMessage m;
//        m.setAddress("/motor/move/to");
//        m.addIntArg(2);
//        m.addIntArg(aspi_in);
////        cout<<m.getAddress()<<" "<<m.getArgAsInt32(0)<<" "<<m.getArgAsInt32(1)<<endl;
//        oscSender.sendMessage(m);
//
//        m.clear();
//        m.setAddress("/motor/move/to");
//        m.addIntArg(3);
//        m.addIntArg(aspi_out);
////        cout<<m.getAddress()<<" "<<m.getArgAsInt32(0)<<" "<<m.getArgAsInt32(1)<<endl;
//        oscSender.sendMessage(m);
        
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
