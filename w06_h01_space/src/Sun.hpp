//
//  Sun.hpp
//  Force
//
//  Created by JohnGuo on 08/10/2017.
//
//

#ifndef Sun_hpp
#define Sun_hpp

#include <stdio.h>

#endif /* Sun_hpp */

#pragma once
#include "ofMain.h"
#include "Ball.hpp"

class Sun{
public:
    ofVec2f pos = ofVec2f( ofGetWidth()/2, ofGetHeight()/2);
    float mass = 200;
    float G = 1.;
    
    //  ofColor color = ofColor::fromHex(0xADC2C4);
    int lerpAmount = 1;
    int lerpStep = 1;
    
    void update();
    void draw();
    ofVec2f calculateAttraction(Ball ball);
};
