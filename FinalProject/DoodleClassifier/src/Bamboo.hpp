//
//  Bamboo.hpp
//  FloralBrushArt
//
//  Created by 俊谷郭 on 12/4/17.
//
#pragma once
#ifndef Bamboo_hpp
#define Bamboo_hpp

#include <stdio.h>

#endif /* Bamboo_hpp */
#include "ofMain.h"

class Bamboo{
public:
    void setup(ofPoint _pos);
    void update();
    void draw();
    
    
//    void drawLeaf(float startX, float startY, float angle,float scale = 1);
    void GeneratePetal(float startX, float startY, float angle);
   // void updatePetalMeshes();
    void drawFlower();
    
    ofPoint pos;
    ofColor color; 
    float scale;
    float petalLength = 300;
    vector<ofMesh> petalMeshes;
};

