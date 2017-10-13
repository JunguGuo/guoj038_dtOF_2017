//
//  Ball.hpp
//  PerlinNoiseTest
//
//  Created by JohnGuo on 07/10/2017.
//
//
#pragma once
#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#endif /* Ball_hpp */

#include "ofMain.h"
class Ball{
public:
    Ball();
    Ball(float mass, ofVec2f pos);
    Ball(float mass, ofVec2f pos, ofVec2f vel,ofColor color);
    ofVec2f pos;
    //int size = 5;
    ofColor color = ofColor::fromHex(0x3ED1C3);
    
    ofVec2f vel = ofVec2f(2,1);
    ofVec2f acc = ofVec2f::zero();
    float mass = 1.;
    
    void update();
    void draw();
    void applyForce(ofVec2f force);
    //void checkEdges();

};
