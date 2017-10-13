//
//  Particle.cpp
//  ParticleSystem
//
//  Created by Tyler on 10/5/17.
//
//

#include "Particle.hpp"

Particle::Particle()
{
	lifespan = 3.; // seconds
}

Particle::Particle(float x, float y,float h, bool isFireWork)
{
    hu = h;
	pos = ofVec3f(x, y);
    if(isFireWork){
        vel = ofVec3f(0, ofRandom(-20,-10));}
    else{
        vel = ofVec3f(ofRandom(-1,1),ofRandom(-1,1));
        vel*=ofRandom(2,8);
    }
	lifespan = 255.;
    seed = isFireWork;
}

Particle::Particle(ofVec3f _pos,ofVec3f vel,float h , bool isFireWork)
{
    hu = h;
    pos = _pos;
    if(isFireWork){
        this->vel = vel;}
    else{
        vel = ofVec3f(ofRandom(-1,1),ofRandom(-1,1));
        vel*=ofRandom(2,8);
    }
    lifespan = 255.;
    seed = isFireWork;
}

void Particle::applyForce(ofVec3f force){
	acc += force;
}

void Particle::update(){ // how much time has passed since last frame?
	vel += acc;
	pos += vel;
    if (!seed) {
        lifespan -= 5.0;
        vel*=(0.95);
    }
	acc *= 0;
	

}

bool Particle::explode(){
    if (seed && vel.y > 0) {
        lifespan = 0;
        return true;
    }
    return false;
}

void Particle::draw(){
    
	ofPushStyle();
    ofColor color = ofColor::fromHsb(hu, 255, 255);
    if(!seed){
    
    lifespan = ofClamp(lifespan, 0, 255);
    color.a = lifespan;
    
	//float hue = ofMap(lifespan, 0., 3., 0, 255);
	//ofSetColor(ofColor::fromHsb(hue,hue,hue));
    ofSetColor(color);
        ofDrawCircle(pos, 2);
    }
    else{
        ofSetColor(color);
        ofDrawCircle(pos, 5);
    }
	ofPopStyle();
}

bool Particle::isDead() {
    if (lifespan < 0.0) {
        return true;
    } else {
        return false;
    }
}

