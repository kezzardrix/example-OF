//
//  myPCon.h
//  example-bvh
//
//  Created by Kanda Ryo on 12/03/29.
//  Copyright 2012 Kwansei Gakuin. All rights reserved.
//
#ifndef MY_PCON_H
#define MY_PCON_H
#include "ofMain.h"
#include "myPoint.h"

#define NUM_POINT 500

class myPCon{
public:
    myPCon(int _id);
    void draw();
    void update();
    void reset();
    void rand();
    void setFall();
    void smoothCheck();
    void setRotateValue(float speed,float size,int mode);
    void setImg(ofImage &img);
    void setGlobalImg(ofPoint imgPos,int current,int imgID);
    void setGlobalImg(ofPoint imgPos,int current,int imgID,ofFloatColor color);
    void setImgID(int imgID);
    void returnGlobalImg(int imgID);
    void setZValue(float zValue);
    void setColor(float alpha);
    void setGlobalAtract(ofPoint globalAtract);
    void smoothReset();
    int moveMode;
    ofVbo		vbo;
	ofVec3f		verts[NUM_POINT];
	ofFloatColor		color[NUM_POINT];
    ofPoint c;
    ofPoint preC;
    vector<myPoint> mp;
    bool fallMode;
    bool smoothGate;
    int smoothCounter;
    int controlerID;
    float hankei;
    ofPoint t;
    ofPoint ufoCenter;
    bool centerMove;
    float armsY;
};
#endif