
#pragma once
#include "ofMain.h"
#include "Params.hpp"
class Particle {
	
public:

	Particle();
	~Particle(){}
	
	Particle(ofVec3f _pos, ofVec3f _vel);
	
	void applyForce(ofVec3f force);
	void applyDamping(float strength);
	
	void update(float dt);
	void draw();
	
    ofVec3f pos, vel, acc;
    int size;
    ofColor color;
    float time, lifeTime;
    bool live;
		
};
