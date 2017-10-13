//
//  Moon.hpp
//  gravitational_attraction
//
//  Created by JohnGuo on 12/10/2017.
//
//
#pragma once
#ifndef Moon_hpp
#define Moon_hpp

#include <stdio.h>

#endif /* Moon_hpp */
#include "ofMain.h"
#include "Ball.hpp"

class Moon{
public:
    Moon(Ball& _mother);
    ofVec2f pos = ofVec2f(10,10);
    ofVec2f acc = ofVec2f::zero();;
    ofVec2f vel = ofVec2f(3,1);
    ofColor color = ofColor::fromHex(0xF2DEBA);
    Ball& mother;
    float mass = 1;
    int size = 10;

    
    void update();
    void draw();
    ofVec2f calculateLocalAttraction();
    void applyForce(ofVec2f force);


};
