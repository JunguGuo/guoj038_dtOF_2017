#include "Ball.h"
#include <cmath>

//const double Pi = 3.1415926;

// constructor
Ball::Ball(float x, float y) {

	// inside the constructor you initialize the object's variables

	// random radius between 10 and 50
	radius = ofRandom(10,50);			
    preRadius = radius;
    
    dissolvedAmt = 0.0;
    
	// random color
	float red	= ofRandom(0,255);
	float green	= ofRandom(0,255);		
	float blue	= ofRandom(0,255);
	color = ofColor(red, green, blue);

	// random position in window
    this->x = x;
    this->y = y;
    
    acclerate = 1.0;
    yspeed = 0.0;

//	// random x and y speeds/directions between -10 and 10
//	dirX = ofRandom(-10,10);
//	dirY = ofRandom(-10,10);
}

// update position, etc.
void Ball::update() {
    
    yspeed += acclerate;
    
    
    
    //into the water
    if(this->y >= waterLevel && this->y < 768){
        yspeed -= yspeed*waterDamp;
        radius *= shrinkRate;
        color.a;
    }
    y+= yspeed;
    

    //color dissolve
    if(radius>0)
    dissolvedAmt = PI*( pow(preRadius, 2) -  pow(radius, 2));
    
    preRadius = radius;
    
//	x+=dirX;	// move along x by amount of dirX
//	y+=dirY;	// move along y by amount of dirY
//
//	// check for bounces at edges of window:
//
//	// check left
//	if (x <= radius) {
//		x = radius;			// set the position back to the edge of window
//		dirX = -dirX;		// and reverse direction
//	}
//	// check right
//	else if (x >= ofGetWidth() - radius) {
//		x = ofGetWidth() - radius;			// similar to above
//		dirX = -dirX;
//	}
//
//	// check top and bottom
//	if (y <= radius) {
//		y = radius;
//		dirY = -dirY;
//	}
//	else if (y >= ofGetHeight() - radius) {
//		y = ofGetHeight() - radius;
//		dirY = -dirY;
//	}
}


// draw the ball
void Ball::draw() {

	ofSetColor(color);// set the GLOBAL color
    ofFill();
	ofDrawCircle(x,y, radius);		// and draw
}
