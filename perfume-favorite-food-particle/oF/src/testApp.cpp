#include "testApp.h"

float att[3];

ofPoint r;
ofPoint trans;
ofPoint pR;
ofPoint pTrans;

float blurAmt;
float thresh;
float bloomScale;

int blendMode = 0;

float flash;
bool isFlash = false;

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
	
	ofBackground(0);
    
// You have to get motion and sound data AND ofxBvh addon from http://www.perfume-global.com
    
	bvh[0].load("aachan.bvh");
	bvh[1].load("nocchi.bvh");
	bvh[2].load("kashiyuka.bvh");
	
	for (int i = 0; i < 3; i++)
	{
		bvh[i].play();
	}
	
	track.loadSound("track.mp3");
	track.play();
	track.setLoop(true);
	
	play_rate = play_rate_t = 1;
    
   att[0] = 1.0f;
   att[1] = -0.01f;
   att[2] = -0.00001f;
        
    ice.loadImage("images/ice.png");
    curry.loadImage("images/curry.png");
    steak.loadImage("images/steak.png");
    ice_high.loadImage("images/big_ice.png");
    curry_high.loadImage("images/big_curry.png");
    steak_high.loadImage("images/big_steak.png");
    global.loadImage("images/perfumeGlobal.png");
    
    global.setImageType(OF_IMAGE_COLOR_ALPHA);
    ice_high.setImageType(OF_IMAGE_COLOR_ALPHA);
    curry_high.setImageType(OF_IMAGE_COLOR_ALPHA);
    steak_high.setImageType(OF_IMAGE_COLOR_ALPHA);
    
    setGlobalImage(global,2,1,0);
    
    setGlobalImage(ice_high,1,1,0);
    setGlobalImage(curry_high,1,1,1);
    setGlobalImage(steak_high,1,1,2);
  
    letters.loadImage("images/aachanLetter.png");
    setGlobalImage(letters,0,1,0);
    letters.loadImage("images/nocchiLetter.png");
    setGlobalImage(letters,0,1,1);
    letters.loadImage("images/kashiyukaLetter.png");
    setGlobalImage(letters,0,1,2);
    
    ofDisableArbTex();
    receiver.setup(8000);
    
    glDisable(GL_DEPTH_TEST);

}

//--------------------------------------------------------------
void testApp::update()
{
	play_rate += (play_rate_t - play_rate) * 0.3;
	
	track.setSpeed(play_rate);
	
	float t = (track.getPosition() * 62.14);
	t = t / bvh[0].getDuration();
    
	for (int i = 0; i < 3; i++)
	{
		bvh[i].setPosition(t);
		bvh[i].update();
	}
        
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    for(int i = 0; i < 3;i++){
        meta[i].update(bvh[i]);
    }
    
    while( receiver.hasWaitingMessages() )
	{
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );
        
        if ( m.getAddress() == "/each" )
		{
            int  i = m.getArgAsInt32(8);
            if(i < 3){
            meta[i].isPointSprite = m.getArgAsInt32(0);
            meta[i].divMode = m.getArgAsInt32(1);
            meta[i].divVal = m.getArgAsFloat(2);
            meta[i].divRotateSpeedAdd = m.getArgAsFloat(3);
            meta[i].setRotateSpeed(m.getArgAsFloat(4),
                                   m.getArgAsFloat(5),
                                   m.getArgAsInt32(6));
            meta[i].setZValue(m.getArgAsFloat(7));
            }
        }
        
        if ( m.getAddress() == "/moveMode" )
		{
            int  i = m.getArgAsInt32(1);
            if(i < 3){
                meta[i].setMoveMode(m.getArgAsInt32(0));
            }
        }
        
        if ( m.getAddress() == "/reset" )
		{
            int  i = m.getArgAsInt32(0);
            if(i < 3){
                meta[i].reset();
            }
        }
        
               
        if ( m.getAddress() == "/color" )
		{
            for(int i = 0; i < 3; i++){
                meta[i].setColor(m.getArgAsFloat(0));
            }
        }
        
        if ( m.getAddress() == "/rotate" )
		{
        
                pR.set(m.getArgAsFloat(0),
                       m.getArgAsFloat(1),
                       m.getArgAsFloat(2));
            }
        
        if ( m.getAddress() == "/translate" )
		{
            pTrans.set(m.getArgAsFloat(0),
                  m.getArgAsFloat(1),
                  m.getArgAsFloat(2));
        }
        
        if ( m.getAddress() == "/imgID" )
		{
            for(int i = 0; i < 3; i++){
                meta[i].setImgID(m.getArgAsInt32(0));
                }
        }
        
        if ( m.getAddress() == "/blendMode" )
		{
            blendMode = m.getArgAsInt32(0);
        }
               
        if ( m.getAddress() == "/flash" )
		{
            isFlash = m.getArgAsInt32(0);
            flash = m.getArgAsFloat(1);
        }
    }
    
    r += (pR - r) * 0.1;
    trans += (pTrans - trans) * 0.1;

}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableAlphaBlending();
    
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofTranslate(trans.x, 150-trans.y,trans.z);
    ofRotate(r.x, 1, 0, 0);
    ofRotate(r.y, 0, 1, 0);
    ofRotate(r.z, 0, 0, 1);
        
    ofScale(1, -1, 1);
		
    if(blendMode == 0) ofEnableBlendMode(OF_BLENDMODE_ADD);
    else if(blendMode == 1) ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		
    glEnable(GL_POINT_SMOOTH);
    glPointSize(2);
    glPointParameterf(GL_POINT_SIZE_MIN, 1.0f);
    glPointParameterf(GL_POINT_SIZE_MAX, 256.0f);
    glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, att);
    
    ofPushMatrix();
    
    meta[0].draw(ice);
    meta[1].draw(curry);
    meta[2].draw(steak);
    
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
}

void testApp::setGlobalImage(ofImage &img,int imgID,int mode,int _cMeta){
    int counter = 0;
    int cJoint = 0;
    int cBody = 0;
    int cMeta = _cMeta;
    ofFloatColor color;
    unsigned char * pixels = img.getPixels();
    for(int i = 0; i < img.width; i++){
        for(int j = 0; j < img.height; j++){
            
            unsigned char thresh;
            
            if(mode == 0)thresh = pixels[(j*img.width+i)];
            else if(mode == 1){
            thresh = (pixels[(j*img.width+i)*4] +
            pixels[(j*img.width+i)*4+1] + 
            pixels[(j*img.width+i)*4+2]) / 3.0;
            }
                if(thresh > 0){
                    
                    if(mode == 1){
                              color.set(
                              pixels[(j*img.width+i)*4] / 255.0,
                              pixels[(j*img.width+i)*4+1] / 255.0,
                              pixels[(j*img.width+i)*4+2]/ 255.0,
                              pixels[(j*img.width+i)*4+3]/ 255.0);
                        meta[cMeta].globalImageSet(ofPoint(i-ofGetWidth()*0.5,j-220,0),counter,cJoint,cBody,imgID,color);
                        counter++;
                    }else{
                        meta[cMeta].globalImageSet(ofPoint(i-ofGetWidth()*0.5,j-220,0),counter,cJoint,cBody,imgID);
                        counter++;
                      
                    }
                    
                    if(counter > NUM_POINT - 1){
                        counter = 0;
                        cJoint++;
                        if(cJoint > NUM_JOINT - 1){
                            cJoint = 0;
                            cBody++;
                            
                            if(cBody > NUM_CON - 1){
                                cBody = 0;
                                cMeta++;
                                cMeta %= 3;
                            }
                        }
                    }
                }
            }
        }
}
