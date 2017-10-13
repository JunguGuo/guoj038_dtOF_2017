#pragma once

#include "ofMain.h"
#include "Ball.hpp"
#include "Sun.hpp"
#include "Moon.hpp"

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
    
    Ball ball1= Ball(3., ofVec2f(100.,100.));
    
    
    Sun sun;
    Moon moon = Moon(ball1);;
    
    vector<Ball> asteroids;
    int nAsteroids = 100;
		
};
