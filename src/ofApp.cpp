#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(125);
    ofSetFrameRate(240);
    
//    ofxTimeline::removeCocoaMenusFromGlut("Laser Anim Toolbox");
//    ofxEtherdream::startEtherdreamLib();
    int nbEtherdream = ofxEtherdream::getNumEtherdream() ;
    ofLog(OF_LOG_NOTICE, "there is "+ofToString(nbEtherdream)+" etherdream detected");

    ilda.clear();
    
    ildaTabs.setup();
    ildaTabs.setPosition(0, 0);
    
    animManagerTabs.setup();
    animManagerTabs.setPosition(ildaTabs.getGlobalCanvasWidth()+150., 0.);
    
    renderParams.setName ("sub render parameters");
//
    for (int i=0; i<nbEtherdream; i++) {
    /*****************************/
    /*** debug hotel *************/
    /*****************************/
//    for (int i=0; i<4; i++) {
    /** fin debug **/
        
        IldaControl * ildaController = new IldaControl();
        
/*************************************************/
/* TODO : Ajout d'un moyen de sauvegarde des ids */
/*************************************************/
        
/*****************************/
// temporaire : id laser specifique perf.
        if (i<4){
            ildaController->setup(etherdreamID[i]);
        }else{
            ildaController->setup(i);
        }
        
        ildaController->setup(i);
        
        ildaController->setName("laser."+ofToString(i+1));
        ildaController->load();
        
        ildaTabs.addCanvas(ildaController->getGui());
        
        ilda.push_back(ildaController);
        
        RenderSub *ildaRender = new RenderSub();
        ildaRender->setName("subRender."+ofToString(i+1));
        ildaRender->setup();
        ildaRender->setMainFrame(&frame);
        
        // should not be 1-xxx -> bounding box looks reversed. weird...
        ildaRender->setBoundingBox((float)i/(float)nbEtherdream, 0., 1./(float)nbEtherdream , 1.);
        ildaRender->load();
        subframes.push_back(ildaRender);
        
        renderParams.add(ildaRender->renderSubParams);
    }
    
    for (int i=0; i<NB_LAYERS; i++) {
        AnimManager *anim = new AnimManager();
        anim->setup();
        anim->setDrawWidth(150);
        anim->setDrawHeight(150);
        anim->setDrawOffset(ofVec2f(ofGetWidth()-200., ofGetHeight()-600));
        anim->setGuiOffset(ofVec2f(ildaTabs.getGlobalCanvasWidth()+150., 0.));
        anim->setName("layer."+ofToString(i+1));
        anim->load();
        
        animManagerTabs.addCanvas(anim->getGui());
        animManager.push_back(anim);
    }
    
    renderGui.setup(renderParams);
    
    frame.clear();
    
    oscTimeDelay = 0.2;
    lastOscTime = 0;
    
    oscReceive.setup(OSC_LISTENING_PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    parseOSC();
    
    frame.clear();
    
    for (int i=0; i<animManager.size(); i++) {
        animManager[i]->update();
        frame.addPolys(animManager[i]->getPolylines());
    }
    
    if (ofGetElapsedTimef()-lastOscTime > oscTimeDelay) {
        lastOscTime = ofGetElapsedTimef();
    }
    
    vector<IldaControl *>::iterator ildaIt = ilda.begin();
    vector<IldaControl *>::iterator ildaEnd = ilda.end();
    vector<RenderSub *>::iterator ildaRenderIt = subframes.begin();
    vector<RenderSub *>::iterator ildaRenderEnd = subframes.end();
    vector<ofPolyline> rp;
    
    while (ildaIt != ildaEnd) {
        rp.clear();
        
        (*ildaIt)->clear();
        (*ildaRenderIt)->update();
        
        rp = (*ildaRenderIt)->getSubFrame() ;
        for (int i = 0; i<rp.size(); i++) {
            (*ildaIt)->addPoly(rp[i]);
        }
        
        (*ildaIt)->update();
        
        ildaIt ++;
        ildaRenderIt ++;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for (int i=0; i<animManager.size(); i++) {
        animManager[i]->draw();
    }
    
    for (int i=0; i<ilda.size(); i++) {
        subframes[i]->draw(ofGetWidth()-200*ilda.size()+200*(i), ofGetHeight()-400, 150, 150);
        ilda[i]->draw(ofGetWidth()-200*ilda.size()+200*(i), ofGetHeight()-200, 150, 150);
    }
    
    renderGui.draw();
}

//--------------------------------------------------------------
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

    vector<RenderSub *>::iterator ildaRenderIt = subframes.begin();
    vector<RenderSub *>::iterator ildaRenderEnd = subframes.end();
    
    while (ildaRenderIt != ildaRenderEnd) {
        RenderSub * ildaT = *ildaRenderIt;
        ildaT->save();
        ildaRenderIt ++;
        delete ildaT;
    }
    subframes.clear();
    
    vector<AnimManager *>::iterator animIt = animManager.begin();
    vector<AnimManager *>::iterator animEnd = animManager.end();
    
    while (animIt != animEnd) {
        AnimManager * animT = *animIt;
        animT->save();
        animIt ++;
        delete animT;
    }
    animManager.clear();
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

        vector<AnimManager *>::iterator animIt = animManager.begin();
        vector<AnimManager *>::iterator animEnd = animManager.end();
        
        while (animIt != animEnd) {
            (*animIt)->save();
            animIt ++;
        }
    }
    if (key == '1'){
        if (ilda.size()>=1) {
            ilda[1]->forceReconnect();
        }
    }
    else if (key == '2'){
        if (ilda.size()>=2) {
            ilda[2]->forceReconnect();
        }
    }
    else if (key == '3'){
        if (ilda.size()>=3) {
            ilda[3]->forceReconnect();
        }
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
        
//        ofLog (OF_LOG_NOTICE, "osc message received : "+m.getAddress());
        
        vector<AnimManager *>::iterator animIt = animManager.begin();
        vector<AnimManager *>::iterator animEnd = animManager.end();
        
        while (animIt != animEnd) {
            (*animIt)->parseOSC(m);
            animIt ++;
        }
        
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
