//
//  Sphere.cpp
//  HubbleMesh
//
//  Created by 俊谷郭 on 11/9/17.
//

#include "Sphere.hpp"


Sphere::Sphere(ofVec3f _pos,float _size,ofColor _color){
    pos = _pos;
    tmpos = _pos;
    size = _size;
    color = _color;
    sphere.setRadius(size);
    sphere.setPosition(tmpos);
    
}

void Sphere::update(){
    tmpos.z = ((sin(ofGetElapsedTimef())+1))*pos.z*2;

//    tmpos.x = ofMap(sin(ofGetElapsedTimef()), -1, 1, pos.x, pos.x*6);
//    tmpos.y = ofMap(sin(ofGetElapsedTimef()), -1, 1, pos.y, pos.y*6);

    sphere.setPosition(tmpos);
}

void Sphere::draw(){
    ofSetColor(color);
    sphere.draw();
}
