//
//  metaController.h
//  example-bvh
//
//  Created by Kanda Ryo on 12/03/31.
//  Copyright 2012 Kwansei Gakuin. All rights reserved.
//
#ifndef META_H
#define META_H
#include "ofMain.h"
#include "myPCon.h"
#include "ofxBvh.h"
#define NUM_JOINT 28
#define NUM_CON 5
#define SUM_POINT NUM_JOINT * NUM_CON * NUM_POINT

class metaController{
    public:
    int metaID;
    int divMode;
    float divVal;
    float divRotateSpeed;
    float divRotateSpeedAdd;
    bool isPointSprite;
    ofPoint divPos[NUM_CON];
    int moveMode[NUM_CON];
    vector<myPCon>perfume[NUM_CON];
    int fallTarget;
    metaController(){
        divMode = 0;
        divVal = 0.0;
        divRotateSpeed = 0.0;
        divRotateSpeedAdd = 0.01;
        fallTarget = 0;
        for(int i = 0; i < NUM_CON; i++){
        for(int k = 0; k < NUM_JOINT; k++){
            myPCon myP(k);
            perfume[i].push_back(myP);
        }
            
        }
      }

    void draw(ofImage &img){
    for(int i = 0; i < NUM_CON;i++){
        float theta;
        if(divMode == 1) theta = ((i + 1) / (float)NUM_CON) * 6.18 + divRotateSpeed;
        int k = 0;
        ofPoint cDiv;
        cDiv.set(0,0,0);
        float x,y,z;
        
        if(divMode == 1){
            cDiv.x = cos(theta) * divVal;
            cDiv.y = 0.0;
            cDiv.z = sin(theta) * divVal;
        
            
        }else if(divMode == 2){
            cDiv.set(i*divVal*0.333,0,0);
        }
        
        divPos[i] += (cDiv - divPos[i]) * 0.1;
        
        for(vector<myPCon>::iterator conIt = perfume[i].begin(); conIt != perfume[i].end(); ++conIt){
           
            ofPushMatrix();
           
            
            ofTranslate(divPos[i]);
            
            if(isPointSprite){
                img.getTextureReference().bind();
                ofEnablePointSprites();
            }
            
            if(i == 0) conIt->draw();
            else if(divMode != 0 && i != 0) conIt->draw();
            
            if(isPointSprite){
                img.getTextureReference().unbind();
                ofDisablePointSprites();
            }
            
            ofPopMatrix();
            
            k++;
            }
        }
        divRotateSpeed += divRotateSpeedAdd;
    }
    
    void update(ofxBvh &bvh){
        for(int i = 0; i < NUM_CON;i++){
            int k = 0;
            ofPoint ufoCenter;
            for(vector<myPCon>::iterator conIt = perfume[i].begin(); conIt != perfume[i].end(); ++conIt){
                conIt->update();
                conIt->c.set(bvh.getJoint(k)->getPosition());
                
                if(k == 0) ufoCenter = conIt->c;
                
                conIt->ufoCenter = ufoCenter;
                
                k++;
                
            }
        }
    }
    
    void reset(){
        for(int i = 0; i < NUM_CON;i++){
            for(vector<myPCon>::iterator conIt = perfume[i].begin(); conIt != perfume[i].end(); ++conIt){
                if(moveMode[i] == 1 || moveMode[i] == 6){
                    conIt->reset();
                    conIt->rand();
                }
            }
        }
    }
    
    void globalImageSet(ofPoint imgPos,int currentPoint,int cJoint,int cBody,int imgID){
        perfume[cBody][cJoint].setGlobalImg(imgPos,currentPoint,imgID);
    }
    
    void globalImageSet(ofPoint imgPos,int currentPoint,int cJoint,int cBody,int imgID,ofFloatColor color){
        perfume[cBody][cJoint].setGlobalImg(imgPos,currentPoint,imgID,color);
    }
    
    void setRotateSpeed(float speed,float size,int mode){
        for(int i = 0; i < NUM_CON;i++){
            for(vector<myPCon>::iterator conIt = perfume[i].begin(); conIt != perfume[i].end(); ++conIt){
                conIt->setRotateValue(speed,size, mode);
            }
        }
    }
    
    void setColor(float alpha){
        for(int i = 0; i < NUM_CON;i++){
            for(vector<myPCon>::iterator conIt = perfume[i].begin(); conIt != perfume[i].end(); ++conIt){
                conIt->setColor(alpha);
            }
        }
    }
    
    void setZValue(float zValue){
        for(int i = 0; i < NUM_CON;i++){
            for(vector<myPCon>::iterator conIt = perfume[i].begin(); conIt != perfume[i].end(); ++conIt){
                conIt->setZValue(zValue);
            }
        }
    }
    
    void setImgID(int imgID){
        for(int i = 0; i < NUM_CON;i++){
            for(vector<myPCon>::iterator conIt = perfume[i].begin(); conIt != perfume[i].end(); ++conIt){
                conIt->setImgID(imgID);
            }
        }
    }
        
    void setGlobalAtract(ofPoint globalAtract){
        for(int i = 0; i < NUM_CON;i++){
            for(vector<myPCon>::iterator conIt = perfume[i].begin(); conIt != perfume[i].end(); ++conIt){
                conIt->setGlobalAtract(globalAtract);
            }
        }
    }
    
    void setMoveMode(int mode){
        
        if(mode == 10){
            for(int i = 0; i < NUM_CON;i++){
              moveMode[i] = (int)ofRandom(1,10);
            }
        }
        else if(mode == 11){
            for(int i = 0; i < NUM_CON;i++){
                moveMode[i] = 2;
            }
            moveMode[fallTarget] = 3;
            fallTarget++;
            fallTarget %= NUM_CON;
        }else if(mode == 12){
            for(int i = 0; i < NUM_CON;i++){
                int decide = ofRandom(0,2);
                if(decide == 0) moveMode[i] = 3;
                else if(decide == 1) moveMode[i] = 8;
            }
        }else{
            for(int i = 0; i < NUM_CON;i++){
                moveMode[i] = mode;
            }
        }
        
        for(int i = 0; i < NUM_CON;i++){
            
            for(vector<myPCon>::iterator conIt = perfume[i].begin(); conIt != perfume[i].end(); ++conIt){
                conIt->moveMode = moveMode[i];
                if(moveMode[i] == 2 || moveMode[i] == 8)conIt->setFall();
            }
        }
    }
};
#endif