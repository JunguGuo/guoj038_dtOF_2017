#include "Eye.h"
#include "ofApp.h"

// constructor
Eye::Eye() {
    
    // inside the constructor you initialize the object's variables
    
    // random radius between 10 and 50
    radius = 30;
    rangeRadius = 150-15;

    color = ofColor::black;
    
    // random position in window
//    x = ofRandom(radius, ofGetWidth()  - radius);
//    y = ofRandom(radius, ofGetHeight() - radius);
    

}

// update position, etc.
void Eye::update() {
    
    ofVec2f mousePos (ofGetMouseX(),ofGetMouseY());
    
    ofVec2f dstPos;
    if((mousePos - centerPos).length()<rangeRadius)
        dstPos = mousePos;
    else{
        dstPos =  (mousePos - centerPos).normalize()*rangeRadius + centerPos;}
    
    pos = pos*pct+ (1-pct)*dstPos;
    
    
//    x+=dirX;	// move along x by amount of dirX
//    y+=dirY;	// move along y by amount of dirY
//    
//    // check for bounces at edges of window:
//    
//    // check left
//    if (x <= radius) {
//        x = radius;			// set the position back to the edge of window
//        dirX = -dirX;		// and reverse direction
//    }
//    // check right
//    else if (x >= ofGetWidth() - radius) {
//        x = ofGetWidth() - radius;			// similar to above
//        dirX = -dirX;
//    }
//    
//    // check top and bottom
//    if (y <= radius) {
//        y = radius;
//        dirY = -dirY;
//    }
//    else if (y >= ofGetHeight() - radius) {
//        y = ofGetHeight() - radius;
//        dirY = -dirY;
//    }
}


// draw the ball
void Eye::draw() {
    
    ofSetColor(color);				// set the GLOBAL color
    ofDrawCircle(this->pos.x,this->pos.y, radius);		// and draw
}
