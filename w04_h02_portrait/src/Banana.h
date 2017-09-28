// Ball.h

/* #pragma once should always be at the top of your header files
 * it prevents other headers like "ofMain.h" from being included more than once in your app
 * (note that ofMain.h is also included in ofApp.h)
 */

#pragma once
#include "ofMain.h"		// ofMain.h lets our Ball "see" openFrameworks

class Banana {
    
public:
    
    Banana();
    
    void update();
    void draw();
    
    ofImage bananaImg;
    float radius;		// size
    ofVec2f pos;			// position
    ofVec2f velocity;
    ofVec2f acceleration;

    ofColor color;
    
    float pct = 0.9;
    
    void ApplyForce(ofVec2f force);
    void ClearForce();
    
    ofVec2f gravity;
};
