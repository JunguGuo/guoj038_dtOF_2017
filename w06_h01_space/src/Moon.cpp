//
//  Moon.cpp
//  gravitational_attraction
//
//  Created by JohnGuo on 12/10/2017.
//
//

#include "Moon.hpp"

Moon::Moon(Ball& _mother):mother(_mother){
    //this->mother = _mother;
}

void Moon::update(){
    applyForce(calculateLocalAttraction());
    vel += acc;
    pos += vel;
    acc *= 0;


}

void Moon::draw(){
    ofPushMatrix();
    ofTranslate(mother.pos.x,mother.pos.y);
    
    ofSetColor(color);
    ofDrawCircle(pos.x,pos.y,10);
    ofPopMatrix();
}

ofVec2f Moon::calculateLocalAttraction(){
    ofVec2f force = -pos;
    
    float distance = force.length();
    
    distance = ofClamp(distance, 0, 10);
    
    force.normalize();
    
    force*= (3*mass* mother.mass / (distance*distance));
    return force;
    
}

void Moon::applyForce(ofVec2f force){
    acc += force/mass;
}
