//
//  myPoint.h
//  example-bvh
//
//  Created by Kanda Ryo on 12/03/29.
//  Copyright 2012 Kwansei Gakuin. All rights reserved.
//
#ifndef MY_POINT_H
#define MY_POINT_H
#include "ofMain.h"
#define MAX_GLOBAL_IMAGE_NUM 3

class myPoint{
    public:
        myPoint(int _id);
        myPoint();
        ofVec3f pos;
        ofPoint fallV;
        ofPoint center;
        ofPoint localImgPos;
        ofPoint globalImgPos[MAX_GLOBAL_IMAGE_NUM];
        ofFloatColor color;
        ofFloatColor imgColor[MAX_GLOBAL_IMAGE_NUM];
        float alpha;
        ofPoint globalAtract;
        ofVec3f v;
        int pointID;
        int controlerID;
        int imgID;
        void draw();
        void move(int mode);
        void atract(int mode);
        void reset();
        void fall();
        void rotate(int mode);
        void ufo();
        void tree();
        void setRotateValue(float speed,float size,int mode);
        void returnLocalImg();
        void setGlobalImg(ofPoint imgPos,int imgID);
        void setGlobalImg(ofPoint imgPos,int imgID,ofFloatColor color);
        void returnGlobalImg(int imgID);
    void colorWhite();
        float force;
        float hankei;
        float IDZ;//rotate時のz軸重なり過ぎ病を防いだりもする
        float zValue;
        float rotateSpeed;
        float rotateSize;
        float ufoHankei;
        float randFric;
        float pPosY;
        float rotateMult;
};
#endif