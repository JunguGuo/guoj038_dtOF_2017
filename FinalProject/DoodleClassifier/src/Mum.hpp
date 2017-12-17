//
//  Mum.hpp
//  FloralBrushArt
//
//  Created by 俊谷郭 on 12/4/17.
//
#pragma once
#ifndef Mum_hpp
#define Mum_hpp

#include <stdio.h>

#endif /* Mum_hpp */
#include "ofMain.h"
#include "Params.hpp"
#include "ofxEasing.h"
#include "FoundSquare.hpp"
class ExplosionParticle{
public:
    ExplosionParticle(ofVec3f _pos, ofColor _color, float maxVel);
    void update();
    void draw();
    ofVec3f pos,vel,gra;
    //float explosionForce = 8;
    ofColor color;
    bool isAlive = true;
    float angle;
    int size = 8;
};

class Mum{
public:
    void setup(FoundSquare* _fs);
    void update();
    void draw();
    void explode();
    ofPoint pos;
    float maxScale = 1.0; // = 80 radius
    float maxBaseR = -100;
    float initTime,now,endTime,scale;
    int k = 6;
    float t = 1.6375;
    int baseR = 55;// normal 29
    
    //-------anim part---------
    enum State { none,appearing, staying,exploding,dead };
    State state = none;
    //int state = 0; //0 appear //1 stay //2 exploding  // 3 dead
    float appearDuration = 2.f;
    
    float rotateSpeed = 0.3f;
    float angle = 0;
    
    //    bool isExplode = false;
    //    bool isAlive = true;
    
    
    
    //explosion
    vector<ExplosionParticle> epParticles;
    FoundSquare* myfs = nullptr;
};


