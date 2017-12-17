//
//  Prunus.hpp
//  FloralBrushArt
//
//  Created by 俊谷郭 on 12/4/17.
//
#pragma once
#ifndef Prunus_hpp
#define Prunus_hpp

#include <stdio.h>

#endif /* Prunus_hpp */
#include "ofMain.h"
#include "Params.hpp"
#include "ofxEasing.h"
#include "FoundSquare.hpp"
class PrunusExplosionParticle {
public:
    PrunusExplosionParticle(ofVec3f _basePos, ofColor _color, float maxVel);
    void update();
    void draw();
    ofVec3f pos,vel,gra;
    //float explosionForce = 8;
    ofColor color;
    bool isAlive = true;
    float angle;
    int size = 8;
    ofPoint basePos;
};

class Prunus{
public:
    void setup(FoundSquare* _fs, float _radius);
    void update();
    void draw();
    void explode();
    
    ofPoint pos;
    float size;
    int k = 6;
    float t = 1;
    //int baseR = 29;
    ofColor color;
    
    void GeneratePetal(float startX, float startY, float angle);
    void updatePetalMeshes();
    void drawFlower() ;
    Boolean verbose = false;       // set verbose to false to remove points and control points
    int radius = 20;              // sets the center radius of the flower, radius determine the size of the flower
    int totalPetals = 8;
    
    float petalLength = 200;
    float maxPetalLengthPct = 0.9; // animating paramamer, when fully grow hits maximu,
    float ratio = 2.0;
    int controlPointDiameter = 5;
    
    vector<ofMesh> petalMeshes;
    
    //-------anim part---------
    enum State { none,appearing, staying,exploding,dead };
    State state = none;
    //int state = 0; //0 appear //1 stay //2 exploding  // 3 dead
    float appearDuration = 2.f;
    
    float rotateSpeed = 0.3f;
    float angle = 0;
    float initTime;
    //    bool isExplode = false;
    //    bool isAlive = true;

    //particles
    vector<PrunusExplosionParticle> epParticles;
    FoundSquare* myfs = nullptr;
};



