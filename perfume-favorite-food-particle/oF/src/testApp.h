#pragma once

// You have to get motion and sound data AND ofxBvh addon from http://www.perfume-global.com
// illustration by @SakeRice 

#include "ofMain.h"
#include "ofxBvh.h"
#include "myPCon.h"
#include "ofxOsc.h"
#include "metaController.h"

class testApp : public ofBaseApp{

  public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    void setGlobalImage(ofImage &img,int imgID,int mode,int _cMeta);
	
	ofSoundPlayer track;
	ofxBvh bvh[3];

	float play_rate, play_rate_t;

    ofImage curry;
    ofImage steak;
    ofImage ice;
    ofImage curry_high;
    ofImage steak_high;
    ofImage ice_high;
    ofImage global;
    ofImage letters;

    ofxOscReceiver receiver;
    
    metaController meta[3];
    
};
