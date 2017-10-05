//
//  Fibonacci.cpp
//  wk05_Fibonacci
//
//  Created by JohnGuo on 05/10/2017.
//
//

#include "Fibonacci.h"
#include  "ofApp.h"
#include <cmath>

float radians (float d) {
    return d * M_PI / 180;
}

Fibonaccii::Fibonaccii(int id){
    this->id = id;
    r = id;
    t = radians(137.5 * id);
    
    ofColor c = ofColor::fromHsb(87+id, 32*(255/100), 90*(255/100));

}

void Fibonaccii::update(){
    //
    //t += sin(0.00001*ofGetElapsedTimeMillis());
    
    t += ofMap(ofGetMouseY(),0,ofGetHeight(),-ofGetHeight()/2,ofGetHeight()/2)*0.0001;
    
    r += ofMap(ofGetMouseX(),0,ofGetWidth(),-ofGetWidth()*0.1,ofGetWidth()*0.1)*0.1;
    
    // c = color(123+id*map(mouseX, 0 ,width, 0 , 2), 32, 90);
    pos = ofVec2f(r * cos(t)+(ofGetWidth()/2),r * sin(t)+(ofGetHeight()/2));
    //c = color((noise( hue(c))*noiseScale )*255,saturation(c),brightness(c));
}

void Fibonaccii::draw(){
    ofSetLineWidth(0);
    ofFill();
  
    if(ofGetKeyPressed('b')){
        ofSetColor(ofColor::fromHsb(10+id*0.6, 82, 230, ofMap(size,3,250,10,255)));
        if(id<250)
            ofDrawCircle(pos.x,pos.y,id,id);
        
        ofSetColor(ofColor::fromHsb(87+id*0.3, 82, 230));
        
        ofDrawCircle(pos.x,pos.y,size,size);

        
    }
    if ( ofGetKeyPressed('a'))
    {
        ofSetColor(ofColor::fromHsb(10+id*0.6, 82, 230, ofMap(size,3,250,10,255)));
        if(id<250)
            ofDrawCircle(pos.x,pos.y,id,id);
    }
    else{
        ofSetColor(ofColor::fromHsb(87+id*0.3, 82, 230));
        
        ofDrawCircle(pos.x,pos.y,size,size);
    }
}
