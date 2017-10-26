//
//  Params.hpp
//  flowFieldImage
//
//  Created by JohnGuo on 24/10/2017.
//
//
#pragma once
#ifndef Params_hpp
#define Params_hpp

#include <stdio.h>

#endif /* Params_hpp */
#include "ofMain.h"
#include "ofxGui.h"

//Control parameters class
class Params {
public:
    void setup();
    ofPoint eCenter;    //Emitter center
    float eRad;         //Emitter radius
    float velRad;       //Initial velocity limit
    float lifeTime;     //Lifetime in seconds
    
    float rotate;   //Direction rotation speed in angles per second
    
    float force;       //Attraction/repulsion force inside emitter
    float spinning;    //Spinning force inside emitter
    float damping;    //Friction, in the range [0, 1]
    float flowFieldRes;
    float history;        //Control parameter for trails
    float strokeSize;
    
    //ofxToggle showFlowField;
};

extern Params param; //Declaration of a global variable
