
#include "Particle.hpp"

Particle::Particle()
{
    time = 0;
    lifeTime = param.lifeTime;
    live = true;
    size = ofRandom(1,4);
    float alpha = ofMap(size,1,4,20,100);
    color = ofColor(0,alpha);
    
}

Particle::Particle(ofVec3f _pos, ofVec3f _vel)
{
	pos = _pos;
	vel = _vel;
    
    time = 0;
    lifeTime = param.lifeTime;
    live = true;
    size = ofRandom(1,4);
}

void Particle::applyForce(ofVec3f force)
{
	acc += force;
}

void Particle::applyDamping(float strength)
{
	acc -= vel.getNormalized() * strength;
}

void Particle::update(float dt)
{
	vel += acc;
	pos += vel;
	acc *= 0;
    
    //Update time and check if particle should die
    time += dt;
    if ( time >= lifeTime ) {
        live = false;   //Particle is now considered as died
    }
    
//    if(pos.y>ofGetHeight()){
//       // pos.y = ofRandom(0,200);
//        pos.y = ofRandom(0,ofGetHeight());
//        pos.x = ofRandom(0,ofGetWidth());
//        vel *= 0;
//    }
    
}

void Particle::draw(){
    if(live){
        ofFill();
        ofSetColor(color);
        ofDrawCircle(pos, size);
    }
}

