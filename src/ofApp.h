#pragma once

#include "ofMain.h"
#include "ofxArtnet.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
        void onButtonEvent(ofxDatGuiButtonEvent(e));
        ofxArtnetReceiver receiver;
        int dataSize;
        bool isRecording;
        unsigned int WindowWidth;
        unsigned int WindowHeight;
        ofPixels pixdata;
        ofPixels pixdata1;
        unsigned char *data;
        ofTexture texGray;
        ofxDatGui* gui;
        ofxArtnetMessage m;
        bool newframe;
        
};
