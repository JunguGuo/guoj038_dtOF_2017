//
//  Ball.cpp
//  PerlinNoiseTest
//
//  Created by JohnGuo on 07/10/2017.
//
//
#include "Ball.hpp"
#include "ofMain.h"

Ball::Ball(){
}
Ball::Ball(float mass, ofVec2f pos){
    this->mass = mass;
    this->pos = pos;
}

Ball::Ball(float mass, ofVec2f pos, ofVec2f vel,ofColor color){
    this->mass = mass;
    this->pos = pos;
    this->vel = vel;
    this->color = color;
}


void Ball::update(){
    vel += acc;
    pos += vel;
    acc *= 0;
    
    //checkEdges();
}

void Ball::draw(){
    ofSetColor(color);
    ofDrawCircle(pos.x, pos.y, mass*5);
}

void Ball::applyForce(ofVec2f force){
    acc += force/mass;
}


//void Ball::checkEdges(){
//    if(pos.y >= ofGetHeight()){
//        pos.y = ofGetHeight();
//        vel *=-0.9;
//    }
//}
