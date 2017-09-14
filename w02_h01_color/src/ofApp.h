#pragma once

#include "ofMain.h"
#include "Ball.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		vector<Ball> balls;		// a vector of type Ball
								// vectors are like arrays of variable size
    int waterLevel;
    int waterArea = (768-waterLevel)*1024*0.4;
    
    float rT =0;
    float gT =0;
    float bT =0;
    float aT =0;
		
    
};
