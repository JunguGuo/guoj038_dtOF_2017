#pragma once
#include "ofMain.h"	
#include "ofMain.h"		// ofMain.h lets our Ball "see" openFrameworks


class Bubble {
    
public:		// other classes can access the following functions & variables:
    
    Bubble(float x, float y);				// "constructor" function - required for every class
    // this is automatically called whenever we create a new ball
    
    void update();
    void draw();
    
    //ofVec2f refPos;
    float waterLevel = 500.0;
    float yspeed = 0.0;
    float acclerate = -0.1;
    float waterDamp = 0.2 ;
    float shrinkRate = 0.98;
    float radius = 0;		// size
    float x, y;			// position
    float dirX, dirY;	// "direction" (a.k.a. velocity or speed)
    
    ofColor color;
    
};
