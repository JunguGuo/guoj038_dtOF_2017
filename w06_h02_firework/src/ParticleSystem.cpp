//
//  ParticleSystem.cpp
//  ParticleSystem
//
//  Created by Tyler on 10/5/17.
//
//

#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(){
    hu = ofRandom(255);
    firework = Particle(ofRandom(ofGetWidth()),ofGetHeight(),hu,true);
	//lifespan = 10.;
}

ParticleSystem::ParticleSystem(ofVec3f _pos, ofVec3f vel,float h){
    hu = h;
    firework = Particle(_pos,vel,hu,true);
    //lifespan = 10.;
}



bool ParticleSystem::done() {
    if (firework.isDead() && particles.empty()) {
        return true;
    } else {
        return false;
    }
}


void ParticleSystem::update(){
    if(!isExploded){
        firework.applyForce(gravity);
        firework.update();
        
        if(firework.vel.y >= 0){
            isExploded = true;
            explode();
        }
    }
    
    for (int i= particles.size()-1; i>=0; i--){
        particles[i].applyForce(gravity);
        particles[i].update();
        if(particles[i].isDead()){
            //remove particles[i],but how??
            particles.erase(particles.begin()+i);
        }
    }
    
   

}

void ParticleSystem::explode(){
    for(int i =0;i<100;i++){
        particles.push_back(Particle(firework.pos.x, firework.pos.y,hu,false));
    }
    
}

void ParticleSystem::draw(){
    if(!isExploded){
        firework.draw();
    }
	for (int i=0; i<particles.size(); i++){
		particles[i].draw();
	}
}

bool ParticleSystem::dead(){
    if (isExploded && particles.empty()) {
        return true;
    } else {
        return false;
    }
}
