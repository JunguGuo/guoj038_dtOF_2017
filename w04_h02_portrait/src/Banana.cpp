#include "Banana.h"
#include "ofApp.h"

// constructor
Banana::Banana() {
    
    // inside the constructor you initialize the object's variables
    
    // random radius between 10 and 50
    radius = 40;
    bananaImg.load("banana.png");
    bananaImg.setAnchorPoint(0.5, 0.5);
    bananaImg.resize(80, 80);
    color = ofColor::black;
    
    velocity = ofVec2f::zero();
    gravity = *new ofVec2f(0,0.5);
    pos = *new ofVec2f(ofRandom(100, 900),0);
//    ofVec2f force;
}

// update position, etc.
void Banana::update() {
    
    //gravity
    ApplyForce(gravity);
    
    velocity += acceleration;
    pos +=velocity;
    
    
    ClearForce();

}


void Banana::ApplyForce (ofVec2f force){
    acceleration+= force;
}

void Banana::ClearForce(){
    acceleration = ofVec2f::zero();
}


// draw the ball
void Banana::draw() {
    ofSetColor(255,255,255);
    bananaImg.draw(pos.x, pos.y);
//    ofSetColor(color);				// set the GLOBAL color
//    ofDrawCircle(this->pos.x,this->pos.y, radius);		// and draw
    
}
