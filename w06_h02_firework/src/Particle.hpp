//
//  Particle.hpp
//  ParticleSystem
//
//  Created by Tyler on 10/5/17.
//
//

#pragma once
#include "ofMain.h"

class Particle {
	public:

	Particle();
	~Particle(){}
	
	Particle(ofVec3f _pos, ofVec3f vel,float h , bool isFireWork);
    Particle(float x, float y,float h,bool isFireWork);
	
	void applyForce(ofVec3f force);
	
	void update(); // timeDiff = time elapsed since last frame in seconds
	void draw();
    bool isDead();
    bool explode();
	ofVec3f pos, vel, acc;
    bool seed = false;
	float lifespan;	// seconds
    float hu;
};
