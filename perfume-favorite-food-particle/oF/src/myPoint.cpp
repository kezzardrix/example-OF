//
//  myPoint.cpp
//  example-bvh
//
//  Created by Kanda Ryo on 12/03/29.
//  Copyright 2012 Kwansei Gakuin. All rights reserved.
//

#include "myPoint.h"

myPoint::myPoint(){
}

myPoint::myPoint(int _id){
    pointID = _id;
    pos.set(ofRandom(-100,100),ofRandom(-100,100),ofRandom(-100.0,100.0));
    color.set(1.0,1.0,1.0,0.4);
    force = 0.2;
    fallV.set(cos(pointID/500.0 * 6.18) * ofRandom(0.1,0.5),ofRandom(-2.0,2.0),sin(pointID/500.0 * 6.18)*ofRandom(0.1,0.5));
    
    hankei = 10.0;
    IDZ = (pointID % 20) * 1.0;
    zValue = 0.1;
    rotateSpeed = 0.04;
    rotateSize = 0.7;
    randFric = ofRandom(0.15,0.3);//ofMap(pointID,0,500,0.1,0.2);
    localImgPos.set(ofRandom(-100,100),
                      ofRandom(-100,100),
                      ofRandom(-100,100));
    for(int i = 0; i < MAX_GLOBAL_IMAGE_NUM; i++){
        globalImgPos[i].set(ofRandomWidth()-ofGetWidth() * 0.5,
                            ofRandomHeight(),
                            0);
        imgColor[i].set(0.0,0.0,0.0,0.0);
    }
    
    globalAtract.set(0,0,0);
    
    imgID = 0;
}

void myPoint::draw(){
}

void myPoint::reset(){
    v.set(0,0,0);
}

void myPoint::fall(){
    v.y -= 1;
    pos.y += v.y;
    
    if(abs(pPosY - pos.y) >= 1.0){
    v.x += fallV.x * 0.2;
    v.z += fallV.z * 0.2;
    pos.x += v.x;
    pos.z += v.z;
    }
    
    if(pos.y <= -20 && v.y <= 0.0){
        v.y *= -0.6;
        v.x *= 0.6;
        v.z *= 0.6;
        pos.y = -20;
    }
    
     pPosY = pos.y;
}

void myPoint::move(int mode){
    if(mode == 1){
        atract(0);
        colorWhite();
    }
    else if(mode == 2){
        fall();
        colorWhite();
    }
    else if(mode == 3){
        rotate(0);
        colorWhite();
    }
    else if(mode == 4){
        tree();
        colorWhite();
    }
    else if(mode == 5){
        ufo();
        colorWhite();
    }
    else if(mode == 6){
        atract(1);
        colorWhite();
    }
    else if(mode == 7){
        returnGlobalImg(imgID);
    }
    else if(mode == 8){
        atract(2);
        colorWhite();
    }
    else if(mode == 9){
        rotate(1);
        colorWhite();
    }
    
  /*  if(controlerID == 22 || controlerID == 27){
       if(pos.y <= 0.0) pos.y =0.0;
    }*/   
}

void myPoint::colorWhite(){
    color.r += (1.0 - color.r) * 0.1; 
    color.g += (1.0 - color.g) * 0.1; 
    color.b += (1.0 - color.b) * 0.1; 
}

void myPoint::atract(int mode){
    ofPoint target;
   
    if(mode == 0)target.set(0,0,0);
    else if(mode == 1)target = center;
    else if(mode == 2)target = globalAtract;
    
    ofVec3f cVec;
    cVec = (target-pos);
    cVec.normalize();
    cVec *= force;
    v += cVec;
    v *= 0.997;
    pos += v;
}

void myPoint::rotate(int mode){
    
    if(mode)rotateMult = 4.0;
    else rotateMult = 1.0;
    
    float theta = (ofGetFrameNum() + pointID) % 618 * rotateSpeed + 0.01;
    float dia = ((pointID % 20) + 1) * hankei * rotateSize * rotateMult;
    pos.x += (cos(theta) * dia - pos.x)*0.2;
    pos.y += (sin(theta) * dia - pos.y)*0.2;
    pos.z += (IDZ*zValue-pos.z) * 0.1;
}

void myPoint::tree(){
    float theta = (ofGetFrameNum() + pointID) % 618 * rotateSpeed + 0.01;
    float dia = ((pointID % 20) + 1) * hankei * rotateSize;
    pos.x += (cos(theta) * dia - pos.x)*0.2;
    pos.y += (sin(theta) * dia - pos.y)*0.2;
    pos.z += (0 - pos.z)*0.1;
}

void myPoint::ufo(){
    float theta = (ofGetFrameNum() + pointID) % 618 * rotateSpeed + 0.01;
    float dia = ((pointID % 20) + 1) * ufoHankei * rotateSize;
    pos.x += (cos(theta) * dia - pos.x)*0.2;
    pos.y += (0 - pos.y)*0.1;
    pos.z += (sin(theta) * dia - pos.z)*0.2;
}

void myPoint::setRotateValue(float speed,float size,int mode){
    if(mode == 0)rotateSpeed = speed;
    else if(mode == 1){
        int decide = (int)ofRandom(0,2);
        if(decide == 0) rotateSpeed = speed * -1;
        else if(decide == 1)rotateSpeed = speed;
    }
    else if(mode == 2){
        rotateSpeed = ofRandom(-speed,speed);
    }
    
    rotateSize = size;
}

void myPoint::returnLocalImg(){
     pos += (localImgPos - pos) * randFric;
}

void myPoint::setGlobalImg(ofPoint imgPos,int imgID){
    if(imgID < MAX_GLOBAL_IMAGE_NUM){
        globalImgPos[imgID] = imgPos;
    }
}

void myPoint::setGlobalImg(ofPoint imgPos,int imgID,ofFloatColor color){
    if(imgID < MAX_GLOBAL_IMAGE_NUM){
        globalImgPos[imgID] = imgPos;
        imgColor[imgID] = color;
    }
}

void myPoint::returnGlobalImg(int imgID){
    if(imgID < MAX_GLOBAL_IMAGE_NUM ){
        pos += (globalImgPos[imgID] - pos) * randFric;
       
            imgColor[imgID].a = alpha;
            color.r += (imgColor[imgID].r - color.r) * 0.1; 
            color.g += (imgColor[imgID].g - color.g) * 0.1; 
            color.b += (imgColor[imgID].b - color.b) * 0.1; 
    
    }
}
