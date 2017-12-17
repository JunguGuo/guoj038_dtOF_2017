//
//  Lotus.hpp
//  FloralBrushArt
//
//  Created by 俊谷郭 on 12/4/17.
//
#pragma once
#ifndef Lotus_hpp
#define Lotus_hpp

#include <stdio.h>

#endif /* Lotus_hpp */
#include "ofMain.h"
#include "Params.hpp"
#include "ofxEasing.h"
#include "FoundSquare.hpp"
class Lotus{
public:
    void setup(FoundSquare* _fs);
    void update();
    void draw();
    void explode();
    
    
    ofPoint pos;
    float size;
    int k = 6;
    float t = 1;
    int baseR = 29;
    ofColor color;
    
    void GeneratePetal(float startX, float startY, float angle,vector<ofMesh>* meshes);
    void updatePetalMeshes(vector<ofMesh>* meshes);
    //void drawPetal(float startX, float startY, float angle);
    void drawFlower() ;
    Boolean verbose = false;       // set verbose to false to remove points and control points
    int radius = 20;              // sets the center radius of the flower,determine the general size of the flower
    int totalPetals = 8;
    float petalLength;
     float maxPetalLengthPct = 6; // animating paramamer, when fully grow hits maximu,
    float maxCentralLengthPct = 0.7;
    float ratio = 2.0;
    int controlPointDiameter = 5;
    
    vector<ofMesh> petalMeshes;
    vector<ofMesh> centralMeshes;
    //-------anim part---------
    enum State { none,appearing, staying,exploding,dead };
    State state = none;
    //int state = 0; //0 appear //1 stay //2 exploding  // 3 dead
    float appearDuration = 3.f;
    
    float rotateSpeed = 0.3f;
    float angle = 0;
    float initTime;
    
    ofPoint lotusOffset;
    float maxleafSizePct = 5;
    float leafSize;
    
    
    FoundSquare* myfs = nullptr;
};

