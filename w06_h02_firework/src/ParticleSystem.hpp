//
//  ParticleSystem.hpp
//  ParticleSystem
//
//  Created by Tyler on 10/5/17.
//
//

#pragma once
#include "ofMain.h"
#include "Particle.hpp"

class ParticleSystem {
public:
	
    ParticleSystem();
	
	ParticleSystem(ofVec3f _pos, ofVec3f vel, float h);
    
	void update();
	void draw();
    bool dead();
    bool done();
    void explode();
	vector<Particle> particles;
    
    Particle firework;
    
	ofVec3f pos;
    float hu;
	
	float lifespan;
    bool isExploded = false;
    
    ofVec2f gravity = ofVec2f(0,0.2);
	
};
