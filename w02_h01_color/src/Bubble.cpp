#include "Bubble.h"

// constructor
Bubble::Bubble(float x, float y) {
    // random radius between 10 and 50
    radius = ofRandom(10,50);
    
    // random color
    float red	= ofRandom(0,255);
    float green	= ofRandom(0,255);
    float blue	= ofRandom(0,255);
    color = ofColor(red, green, blue);
    
    // random position in window
    this->x = x;
    this->y = y;
    
    
    

}

// update position, etc.
void Bubble::update() {
    
    float xMove = sin(ofGetElapsedTimeMillis());
    x+=xMove;
    
    yspeed += acclerate;
    y+= yspeed;
    
    radius +=0.1;
    
    

}


// draw the ball
void Bubble::draw() {
    if(y<=this->waterLevel){
    ofSetColor(255);
    ofNoFill();
    ofSetLineWidth(1);
        ofDrawCircle(x,y, radius);
    }

}
