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
    float gravity;
    float WIDTH;
    float HEIGHT;
};

extern Params param; //Declaration of a global variable
