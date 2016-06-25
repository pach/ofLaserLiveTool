#pragma once

#include "ofMain.h"
#include "AnimManager.h"
#include "IldaControl.h"
#include "SvgLoader.h"

#include "RenderFrame.h"
#include "RenderSub.h"

#include "ofxUI.h"

#define OSC_LISTENING_PORT 10000
#define NB_LAYERS 30

static int etherdreamID[]={14425400, 15243823, 14441185, 15153313};

#include "ofxOsc.h" 

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void parseOSC();
    
private:
    vector<IldaControl *> ilda;
    vector<AnimManager *> animManager;
    RenderFrame frame;
    vector<RenderSub *> subframes;
    
//    AnimManager animManager1;
//    AnimManager animManager2;
    
    ofxOscSender oscSender;
    float oscTimeDelay;
    float lastOscTime;
    
    ofxOscReceiver oscReceive;
    
    ofxUITabBar animManagerTabs;
    ofxUITabBar ildaTabs;
};
