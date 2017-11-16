//
//  Sphere.hpp
//  HubbleMesh
//
//  Created by 俊谷郭 on 11/9/17.
//
#pragma once
#ifndef Sphere_hpp
#define Sphere_hpp

#include <stdio.h>

#endif /* Ball_hpp */
#include "ofMain.h"
class Sphere{
public:
    Sphere(ofVec3f _pos,float _size,ofColor _color);
    void update();
    void draw();
    ofVec3f pos,tmpos,vel,acc;
    float size;
    ofColor color;
    ofSpherePrimitive sphere;
    
};
