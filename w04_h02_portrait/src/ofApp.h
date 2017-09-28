#pragma once

#include "ofMain.h"
#include "Eye.h"
#include"Banana.h"
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
    
        Eye leftEye,rightEye;
    
    ofVec2f mouseCornerLeft;
    ofVec2f mouseCornerRight;
    float mouseOpeness = 0; // 0 -100
    float mouseOpenessPct = 0.9;
    
    
    vector<Banana> bananas;
    ofVec2f leftWind;
    ofVec2f rightWind;
    float windStrength = 1;
    Banana currentBanana;
    
    Banana testBanana;
};
