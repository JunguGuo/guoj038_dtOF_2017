//
//  Sun.cpp
//  Force
//
//  Created by JohnGuo on 08/10/2017.
//
//

#include "Sun.hpp"

void Sun::update(){
    
}

void Sun::draw(){
    ofPushStyle();
   
    //draw glow
    ofColor glowColor = ofColor::fromHex(0x3E544C);
    const ofColor targetColor = ofColor::fromHex(0xF7DB6A);
    
    glowColor = glowColor.lerp(targetColor, lerpAmount/100.0);
   // cout<<lerpAmount<<" "<<lerpStep<<endl;
    if(lerpAmount>99 || lerpAmount<1)
        lerpStep*=-1;
    lerpAmount+=lerpStep;
    
    //ofColor glowColor(color);
    int glowResolution = 30;
    glowColor.a = 255.0/glowResolution;
    ofSetColor( glowColor );
    for(int i = glowResolution;i>0;i--){
        ofDrawCircle(pos.x, pos.y, 35+i*2);
    }
    
    ofSetCircleResolution(50);
    ofSetColor(ofColor::fromHex(0xF7C43B));
    ofDrawCircle(pos.x, pos.y, 50);
    ofSetColor(ofColor::fromHex(0xF6D85C));
    ofDrawCircle(pos.x, pos.y, 50*0.8);
    ofSetColor(ofColor::fromHex(0xF7E17A));
    ofDrawCircle(pos.x, pos.y, 50*0.6);

    
    ofPopStyle();
    
}

ofVec2f Sun::calculateAttraction(Ball ball){
    ofVec2f force = pos - ball.pos;
    
    float distance = force.length();
    
    distance = ofClamp(distance, 0, 25);
    
    force.normalize();
    
    force*= (G * mass* ball.mass / (distance*distance));
    return force;

}
