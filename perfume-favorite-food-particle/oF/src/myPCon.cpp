//
//  myPCon.cpp
//  example-bvh
//
//  Created by Kanda Ryo on 12/03/29.
//  Copyright 2012 Kwansei Gakuin. All rights reserved.
//

#include "myPCon.h"
#define smoothStep 10.0
#define NUM_JOINT 28

myPCon::myPCon(int _id){
    
    controlerID = _id;
    
    hankei = 6.0;
    
    for(int i = 0; i < NUM_POINT;i++){
        myPoint p(i);
        if(controlerID == 0)p.hankei = 1; // head
        else if(controlerID == 4)p.hankei = 0.7;  //neck
        else if(controlerID == 7)p.hankei = 0.7;  //hip
        else if(controlerID == 12)p.hankei = 1; //right-hand
        else if(controlerID == 17)p.hankei = 1; //left-hand
        else if(controlerID == 22)p.hankei = 1; //right-leg
        else if(controlerID == 27)p.hankei = 1; //left-leg
        else p.hankei = 0.4;

        p.ufoHankei = (NUM_JOINT - controlerID) * 0.4;
        p.controlerID = controlerID;
        mp.push_back(p);
        color[i].set(1.0,1.0,1.0,0.15);
        verts[i].set(0,0,0);
    }
    
    vbo.setVertexData(verts, NUM_POINT, GL_DYNAMIC_DRAW);
    vbo.setColorData(color, NUM_POINT, GL_DYNAMIC_DRAW);
    
    c.set(ofGetWidth()*0.5,ofGetHeight()*0.5);
    moveMode = 1;
    
    fallMode = false;
    centerMove = true;
    
    armsY = 200;
    
    ofDisableArbTex();
}

void myPCon::draw(){
   
        vbo.bind();
        vbo.setVertexData(verts, NUM_POINT, GL_DYNAMIC_DRAW);
        vbo.setColorData(color, NUM_POINT, GL_DYNAMIC_DRAW);
        vbo.draw(GL_POINTS, 0,NUM_POINT);
        vbo.unbind();

}

void myPCon::rand(){
    for(vector<myPoint>::iterator partIt = mp.begin(); partIt != mp.end(); ++partIt){
        partIt->pos.x += ofRandom(-10,10);
        partIt->pos.y += ofRandom(-10,10);
    }
}

void myPCon::update(){
    int i = 0;
    
    for(vector<myPoint>::iterator partIt = mp.begin(); partIt != mp.end(); ++partIt){
        
  
        
        if(moveMode == 1 || moveMode == 6){
            if(smoothGate)partIt->center += (c - partIt->center) * (1 / smoothStep);
            else partIt->center = c;
            
        }
        else if(moveMode == 2){ 
            partIt->center.set(0,0,0);
     
        }
        else if(moveMode == 3){
            if(smoothGate)partIt->center += (c - partIt->center) * (1 / smoothStep);
            else partIt->center = c;
            
        }
        else if(moveMode == 4){
            partIt->center += (ofPoint(c.x,controlerID*10,c.z) - partIt->center) * (1 / smoothStep);

            smoothReset();
        } 
        else if(moveMode == 5){
            partIt->center += (ofPoint(ufoCenter.x,controlerID*10,ufoCenter.z) - partIt->center) * (1 / smoothStep);
        
            smoothReset();
        }
        else if(moveMode == 7){
            partIt->center.set(0,0,0);
            smoothReset();
          
        }
        else if(moveMode == 8){
            partIt->center.set(0,0,0);
            smoothGate = true;
            smoothCounter = 0;
        }else if(moveMode == 9){
            partIt->center += (ofPoint(0,armsY,0) - partIt->center) * (1 / smoothStep);
            smoothReset();
        }
        
        verts[i].set(partIt->pos+partIt->center);
        color[i].set(partIt->color);
        
        partIt->move(moveMode);
        i++;
    }
    
    if(moveMode == 1 || moveMode == 3) smoothCheck();
    
}

void myPCon::reset(){
    for(vector<myPoint>::iterator partIt = mp.begin(); partIt != mp.end(); ++partIt){
        partIt->reset();
    }
}

void myPCon::setFall(){
    int i = 0;
    for(vector<myPoint>::iterator partIt = mp.begin(); partIt != mp.end(); ++partIt){
        partIt->pos += partIt->center;
        i++;
    }
    smoothReset();
}

void myPCon::smoothReset(){
    smoothGate = true;
    smoothCounter = 0;
}

void myPCon::smoothCheck(){
    if(smoothGate){
        smoothCounter++;
        if(smoothCounter > smoothStep*3+controlerID){
            smoothGate = false;
        }
    }
}

void myPCon::setRotateValue(float speed,float size,int mode){
    for(vector<myPoint>::iterator partIt = mp.begin(); partIt != mp.end(); ++partIt){
        partIt->setRotateValue(speed,size,mode);
    }
}

void myPCon::setColor(float alpha){
    for(vector<myPoint>::iterator partIt = mp.begin(); partIt != mp.end(); ++partIt){
        partIt->alpha = alpha;
        partIt->color.a = alpha;
    }
}

void myPCon::setImg(ofImage &img){
    
    int counter = 0;
   
        unsigned char * pixels = img.getPixels();
        for(int i = 0; i < img.width; i++){
            for(int j = 0; j < img.height; j++){
                if(counter < NUM_POINT){
                    if(pixels[j*img.width+i] > 0){
                        mp[counter].localImgPos.set(i,j,0);
                        counter++;
                    }
                }
            }
        }
}

void myPCon::setGlobalImg(ofPoint imgPos,int current,int imgID){
    mp[current].setGlobalImg(imgPos,imgID);
}

void myPCon::setImgID(int imgID){
    for(vector<myPoint>::iterator partIt = mp.begin(); partIt != mp.end(); ++partIt){
        partIt->imgID = imgID;
    }
}

void myPCon::setGlobalImg(ofPoint imgPos,int current,int imgID,ofFloatColor color){
    mp[current].setGlobalImg(imgPos,imgID,color);
}

void myPCon::setZValue(float zValue){
    for(vector<myPoint>::iterator partIt = mp.begin(); partIt != mp.end(); ++partIt){
        partIt->zValue = zValue;
    }
}

void myPCon::setGlobalAtract(ofPoint globalAtract){
    for(vector<myPoint>::iterator partIt = mp.begin(); partIt != mp.end(); ++partIt){
        partIt->globalAtract = globalAtract;
        
    }
}