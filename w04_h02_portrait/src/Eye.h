// Ball.h

/* #pragma once should always be at the top of your header files
 * it prevents other headers like "ofMain.h" from being included more than once in your app
 * (note that ofMain.h is also included in ofApp.h)
 */

#pragma once
#include "ofMain.h"		// ofMain.h lets our Ball "see" openFrameworks

class Eye {
    
public:
    
    Eye();
    
    void update();
    void draw();
    
    float radius;		// size
    ofVec2f pos;			// position
    ofVec2f centerPos;			// position
    float dirX, dirY;	// "direction" (a.k.a. velocity or speed)
    
    float rangeRadius; // the area in which the eyeball move
    ofColor color;
    
    float pct = 0.9;
    
};
