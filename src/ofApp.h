#pragma once

#include "ofMain.h"
#include "AnimManager.h"
#include "IldaControl.h"
#include "SvgLoader.h"

//#define OSC_ASPI_ADDR "169.254.48.100"
#define OSC_ASPI_ADDR "127.0.0.1"
#define OSC_ASPI_PORT 10000
#define OSC_LISTENING_PORT 10001

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
    
    
private:
    IldaControl ilda;
    
    AnimManager animManager;
    
    ofxOscSender oscSender;
    float oscTimeDelay;
    float lastOscTime;
    
    ofxOscReceiver oscReceive;
    
//    AnimatedPolyline test;
//    SvgLoader testSvg;
};
