#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(125);
    ofSetFrameRate(60);
    
//    ofxTimeline::removeCocoaMenusFromGlut("Laser Anim Toolbox");
//    ofxEtherdream::startEtherdreamLib();
    int nbEtherdream = ofxEtherdream::getNumEtherdream() ;
    ofLog(OF_LOG_NOTICE, "there is "+ofToString(nbEtherdream)+" etherdream detected");

    ilda.clear();
    
    ildaTabs.setup();
    ildaTabs.setPosition(0, 0);
//
    for (int i=0; i<nbEtherdream; i++) {
        IldaControl * ildaController = new IldaControl();
        ildaController->setup(i);
        ildaController->setName("laser."+ofToString(i+1));
        ildaController->load();
        
        ildaTabs.addCanvas(ildaController->getGui());
        
        ilda.push_back(ildaController);
    }
    
    animManager1.setup();
    animManager1.setDrawWidth(150);
    animManager1.setDrawHeight(150);
    animManager1.setDrawOffset(ofVec2f(ofGetWidth()-400., ofGetHeight()-400));
    animManager1.setGuiOffset(ofVec2f(ildaTabs.getGlobalCanvasWidth()+150., 0.));
    animManager1.setName("layer.1");
//
//    animManager2.setup();
//    animManager2.setDrawWidth(150);
//    animManager2.setDrawHeight(150);
//    animManager2.setDrawOffset(ofVec2f(ofGetWidth()-400., ofGetHeight()-200));
//    animManager2.setGuiOffset(ofVec2f(ildaTabs.getGlobalCanvasWidth()+150., 0.));
//    animManager2.setName("layer.2");
    
    animManagerTabs.setup();
    animManagerTabs.setPosition(ildaTabs.getGlobalCanvasWidth()+150., 0.);
    animManagerTabs.addCanvas(animManager1.getGui());
//    animManagerTabs.addCanvas(animManager2.getGui());
    

    
//    oscSender.setup(OSC_ASPI_ADDR, OSC_ASPI_PORT);
    oscTimeDelay = 0.2;
    lastOscTime = 0;
    
    oscReceive.setup(OSC_LISTENING_PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    parseOSC();
    
    animManager1.update();
//    animManager2.update();
    
    if (ofGetElapsedTimef()-lastOscTime > oscTimeDelay) {
        
        
        lastOscTime = ofGetElapsedTimef();
    }
    
    vector<IldaControl *>::iterator ildaIt = ilda.begin();
    vector<IldaControl *>::iterator ildaEnd = ilda.end();
    
    vector<ofPolyline> polys = animManager1.getPolylines();
    
    while (ildaIt != ildaEnd) {
        (*ildaIt)->clear();
        
        for (int i = 0; i<polys.size(); i++) {
            (*ildaIt)->addPoly(polys[i]);
        }
        
        (*ildaIt)->update();
        
        ildaIt ++;
    }
    
//    ilda1.clear();
//    ilda2.clear();
//    
//    vector<ofPolyline> polys = animManager1.getPolylines();
//    for (int i = 0; i<polys.size(); i++) {
//        ilda1.addPoly(polys[i]);
//    }
//    polys.clear();
//    polys = animManager2.getPolylines();
//    for (int i = 0; i<polys.size(); i++) {
//        ilda2.addPoly(polys[i]);
//    }
//    
//    ilda1.update();
//    ilda2.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    animManager1.draw();
//    animManager2.draw();
    
    for (int i=0; i<ilda.size(); i++) {
        ilda[i]->draw(ofGetWidth()-200, ofGetHeight()-400, 150, 150);
    }
}

void ofApp::exit(){
    vector<IldaControl *>::iterator ildaIt = ilda.begin();
    vector<IldaControl *>::iterator ildaEnd = ilda.end();
    
    while (ildaIt != ildaEnd) {
        IldaControl * ildaT = *ildaIt;
        ildaT->save();
        ildaIt ++;
        delete ildaT;
    }
    ilda.clear();

    animManager1.save();
//    animManager2.save();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's'){
        vector<IldaControl *>::iterator ildaIt = ilda.begin();
        vector<IldaControl *>::iterator ildaEnd = ilda.end();
        
        while (ildaIt != ildaEnd) {
            (*ildaIt)->save();
            ildaIt ++;
        }

        animManager1.save();
//        animManager2.save();
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
        
//        cout<<"just received OSC "<<m.getAddress()<<endl;
        animManager1.parseOSC(m);
        
        vector<IldaControl *>::iterator ildaIt = ilda.begin();
        vector<IldaControl *>::iterator ildaEnd = ilda.end();
        
        while (ildaIt != ildaEnd) {
            (*ildaIt)->parseOSC(m);
            ildaIt ++;
        }
//        animManager2.parseOSC(m);
//        ilda1.parseOSC(m);
//        ilda2.parseOSC(m);
    }
}
