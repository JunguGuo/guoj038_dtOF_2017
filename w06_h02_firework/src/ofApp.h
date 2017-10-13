#pragma once

#include "ofMain.h"
#include "ParticleSystem.hpp"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void mouseReleased(int x, int y, int button);
    void mousePressed(int x, int y, int button);
	//vector<ParticleSystem> systems;
	ofVec3f gravity;
    
//    Particle firework = Particle(ofRandom(ofGetWidth()),ofGetHeight(),100);
	
    
	float lastUpdateTime;	// track frame-by-frame time diff
    
    vector<ParticleSystem> fireworks;
    
    float launcherRange = 100.f;
    float userLauncherRange = 0.f;
    ofVec3f launchPos;
    ofVec3f launchVel;
    float hu;
};
