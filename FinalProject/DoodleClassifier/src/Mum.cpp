//
//  Mum.cpp
//  FloralBrushArt
//
//  Created by 俊谷郭 on 12/4/17.
//

#include "Mum.hpp"
void Mum::setup(FoundSquare* _fs){
    scale = 0;
    initTime = ofGetElapsedTimef();
    state =State::appearing;
    myfs = _fs;
    pos = myfs->getCenter();
}

void Mum::update(){
    if(myfs!=nullptr)
        pos = myfs->getCenter();
    if(ofGetKeyPressed('0')){
        state = State::appearing;
        scale = 0;
        baseR = 55;
        angle = 0;
        initTime = ofGetElapsedTimef();
        epParticles.clear();
    }
    if(ofGetKeyPressed('2')){
        explode();
        //        scale = 0;
        //        baseR = 55;
        //        angle = 0;
        initTime = ofGetElapsedTimef();
    }
    
    
    switch(state){
        case State::appearing:
        {
            float endTime = initTime + appearDuration;
            float now = ofGetElapsedTimef();
            scale = ofxeasing::map_clamp(now, initTime, endTime, 0, maxScale, &ofxeasing::back::easeOut_s, 0.8);
            baseR = ofxeasing::map_clamp(now, initTime, endTime, 55, -100, &ofxeasing::back::easeOut_s, 0.8);
            if(now>endTime)
                state = State::staying;
            
        }
            break;
        case State::staying:{
            //            scale = ofMap(ofGetMouseX(),0, param.WIDTH, 0.0, 2.0);
            //            baseR = ofMap(ofGetMouseY(),0, param.HEIGHT, -100, 58);
            
            
        }
            break;
        case State::exploding:{
            if(epParticles.size()==0){
                cout<<epParticles.size()<<endl;
                state = State::dead;}
            
            for(int i = 0;i<epParticles.size();i++){
                if(!epParticles[i].isAlive)
                    epParticles.erase(epParticles.begin()+i);
                epParticles[i].update();
            }
        }
            break;
        case State::dead:
            cout<<"dead"<<endl;
            break;
    }
    
    
}

void Mum::explode(){
    int parNum = 80;
    for(int i = 0;i<parNum;i++){
        ofVec3f dir(ofRandom(-1,1),ofRandom(-1,1),0);
        dir.normalize();
        dir *= ofRandom(80*maxScale);
        
        float maxVel = 6.f;
        ofColor c(226, ofRandom(100,200), 6, ofRandom(25,80));
        ExplosionParticle p((pos+dir),c,maxVel);
        epParticles.push_back(p);
    }
    
    state = State::exploding;
}
void Mum::draw(){
    //ofNoFill();
    for(int i = 0;i<epParticles.size();i++){
        epParticles[i].draw();
    }
    
    if(state!= State::exploding && state!= State::dead){
        
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        //ofScale(2, 2);
        ofRotate(angle);
        angle+=rotateSpeed;
        //        ofDrawCircle(0, 0, 80);
        for(int j = 9; j >= 0; j--){
            ofFill();
            ofSetColor(226, ofMap(j,0,9,100,200), 6,50);
            int r = baseR + j*10;
            ofBeginShape();
            for(float i = 0; i < PI*2; i += 0.01){
                float x = (10*ofNoise(ofGetElapsedTimef())+r)*cos(k*i+j*t)*cos(i+j*t)*scale;
                
                float y = (10*ofNoise(ofGetElapsedTimef())+r)*cos(k*i+j*t)*sin(i+j*t)*scale;
                ofVertex(x, y);
            }
            ofEndShape();
        }
        
        ofPopMatrix();
        
    }
    string str = "k:"+ofToString(k)+"t:"+ofToString(t)+"baseR:"+ofToString(baseR);
    ofDrawBitmapStringHighlight(str,5,10);
    //    t += 0.002;
    //    if(t==2)
    //        t=1;
    
}



//===========

ExplosionParticle::ExplosionParticle(ofVec3f _pos, ofColor _color, float maxVel){
    pos = _pos;
    color = _color;
    //color.a = ofRandom(125,255);
    
    maxVel*=0.7;
    vel = ofVec3f(ofRandom(-maxVel,maxVel),ofRandom(-maxVel,maxVel),0);
    gra = ofVec3f(0,0,0);//gravity
    angle = ofRandom(360);
}

void ExplosionParticle::update(){
    if(!isAlive)
        return;
    vel+=gra;
    pos+=vel;
    
    //**fix this
    int a = color.a -0.01;
    color.a  = (a<=0? 0: a);
    
    if(pos.x> param.WIDTH || pos.x<0 ||pos.y>param.HEIGHT||pos.y<0 || color.a <=0){
        isAlive = false;
    }
    
}

void ExplosionParticle::draw(){
    if(!isAlive)
        return;
    ofSetColor(color);
    ofFill();
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotate(angle);
    angle+=0.5;
    ofDrawEllipse(ofPoint(0,0), size*2.5, size);
    ofPopMatrix();
    
}

