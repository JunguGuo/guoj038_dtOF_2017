//
//  Prunus.cpp
//  FloralBrushArt
//
//  Created by 俊谷郭 on 12/4/17.
//

#include "Prunus.hpp"


//--------
void Prunus::setup(FoundSquare* _fs, float _radius){
    radius = _radius;
    //pos = _pos;
    petalLength = 0;
    initTime = ofGetElapsedTimef();
    state =State::appearing;
    color  = ofColor(242, 102, 121,125);
    myfs = _fs;
    pos = myfs->getCenter();
}

void Prunus::update(){
    
    if(myfs!=nullptr)
    pos = myfs->getCenter();
    
//    petalLength = ofMap(ofGetMouseX(),0, param.WIDTH, 1.0, 200.0);
    if(ofGetKeyPressed('0')){
        state = State::appearing;
        petalLength = 0;
        angle = 0;
        initTime = ofGetElapsedTimef();
        color  = ofColor(242, 102, 121,125);
        epParticles.clear();
    }
    if(ofGetKeyPressed('2')){
        if(epParticles.size()==0){
            explode();
            initTime = ofGetElapsedTimef();}
    }
    
    switch(state){
        case none:
            //
            break;
        case State::appearing:
        {
            updatePetalMeshes();
            float endTime = initTime + appearDuration;
            float now = ofGetElapsedTimef();
            petalLength = ofxeasing::map_clamp(now, initTime, endTime, 0, -maxPetalLengthPct*radius, &ofxeasing::back::easeOut_s, 0.8);
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
            if(epParticles.size()==0)
                state = State::dead;

            for(int i = 0;i<epParticles.size();i++){
                if(!epParticles[i].isAlive ||color.a<=0){
                    epParticles.erase(epParticles.begin()+i);
                    petalMeshes.erase(petalMeshes.begin()+i);
                    
                }
                epParticles[i].update();
            }
        }
            break;
        case State::dead:
            cout<<"dead"<<endl;
            break;
    }

    //cout<<petalMeshes.size()<<":"<<epParticles.size()<<endl;
    
}
void Prunus::explode(){
    //cout<<"exlode"<<endl;
    int parNum = totalPetals;
    for(int i = 0;i<parNum;i++){
        
        float maxVel = 6.f;
        ofColor c(226, ofRandom(100,200), 6, ofRandom(25,80));
        PrunusExplosionParticle p(pos,c,maxVel);
        //p((pos+dir),c,maxVel);
        epParticles.push_back(p);
    }

    
    state = State::exploding;
}

void Prunus::updatePetalMeshes(){
    petalMeshes.clear();
    float pX = 0.0;
    float pY = 0.0;
    int diameter = radius * 2;
    int centerX = 0;
    int centerY = 0;
    //    if (verbose) {
    //        // if true draw center point
    //        ofSetColor(255, 255, 0);
    //        ofDrawEllipse(centerX, centerY, controlPointDiameter, controlPointDiameter);
    //    }
    
 
    
    // reset starting angle to 0 degrees
    float angle = 0.0;
    
    // draw petals around the center ellipse of the flower
    for (int c = 0; c < totalPetals; c++)  {
        
        // calculate starting point
        pX = centerX + cos(ofDegToRad(angle)) * radius;
        pY = centerY + sin(ofDegToRad(angle)) * radius;
        
        // call drawPetal function to calculate control points and set bezierVertices
        GeneratePetal(pX, pY, angle);
        
        // increment angle based on total number of petals
        angle -= (360 / totalPetals);
    }
}

void Prunus::GeneratePetal(float startX, float startY, float angle) {
    
    // set offset for control points
    float bezierDiff = petalLength / ratio;
    
    // set angle for start's control points
    //    float startAngleTop = angle - 45;
    //    float startAngleBottom = angle + 45;
    float startAngleTop = angle - 90;
    float startAngleBottom = angle + 90;
    
    // set angle for end's control points
    float endAngleTop = angle - 135;
    float endAngleBottom = angle + 135;
    
    // calculate start's top control point
    float startAngleTopX = startX + cos(ofDegToRad(startAngleTop))*bezierDiff;
    float startAngleTopY = startY + sin(ofDegToRad(startAngleTop))*bezierDiff;
    
    // calculate start's bottom control point
    float startAngleBottomX = startX + cos(ofDegToRad(startAngleBottom))*bezierDiff;
    float startAngleBottomY = startY + sin(ofDegToRad(startAngleBottom))*bezierDiff;
    
    // calculate end point
    float endX = startX + cos(ofDegToRad(angle))*petalLength;
    float endY = startY + sin(ofDegToRad(angle))*petalLength;
    
    // calculate end's top control point
    float endAngleTopX = endX + cos(ofDegToRad(endAngleTop))*bezierDiff;
    float endAngleTopY = endY + sin(ofDegToRad(endAngleTop))*bezierDiff;
    
    // calculate end's bottom control point
    float endAngleBottomX = endX + cos(ofDegToRad(endAngleBottom))*bezierDiff;
    float endAngleBottomY = endY + sin(ofDegToRad(endAngleBottom))*bezierDiff;
    
    //-------------
    ofPath path;
    path.moveTo(startX,startY);
    path.bezierTo(startAngleTopX, startAngleTopY, endAngleTopX, endAngleTopY, endX, endY);
    path.bezierTo(endAngleBottomX, endAngleBottomY, startAngleBottomX, startAngleBottomY, startX, startY);
    //ofMesh& mesh = path.getTessellation(); // get reference to path's mesh
    // or make a copy:
    ofMesh mesh = path.getTessellation();
    petalMeshes.push_back(mesh);
    //------coloring------
    //    int verNum = mesh.getNumVertices();
    //    vector<ofFloatColor> colors;
    //    for(int i=0;i<verNum;i++)
    //    {
    //        colors.push_back(ofFloatColor(i*0.1,0.5,0,1));
    //    }
    //    mesh.addColors(colors);
    //---------------------
    
    
    
    
    
}


void Prunus::draw() {
    //    for(ofMesh& mesh:petalMeshes){
    //        ofSetColor(242, 102, 121,125);
    //        //mesh.setColor(0, ofColor::red);
    //        mesh.draw();
    //        //cout<<mesh.getVertices().size()<<endl;
    //
    //    }
    
    for(int i = 0;i<epParticles.size();i++){
        epParticles[i].draw();
    }
    
    
    if(state!= State::exploding && state!= State::dead){
        
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        ofRotate(angle);
        angle+=rotateSpeed;
        
        
        //--------
        //ofSetColor(255, 0, 0);
        // draw center ellipse of the flower
        ofNoFill();
        //ofDrawEllipse(0, 0, radius*2, radius*2);
        for(ofMesh& mesh:petalMeshes){
            ofSetColor(242, 102, 121,125);
            //mesh.setColor(0, ofColor::red);
            mesh.draw();
        }
        
        
        ofPopMatrix();
    }
    if(state == State::exploding){
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        //ofRotate(angle);
        angle+=rotateSpeed;
        
        int a = color.a -0.02;
        color.a  = (a<=0? 0: a);
        //cout<<a<<endl;
        
        for(int i =0;i<petalMeshes.size();i++){
            //**fix this
            
            
            ofSetColor(color);
            //ofSetColor(242, 102, 121,125);
            //mesh.setColor(0, ofColor::red);
            ofPushMatrix();
            
            ofTranslate(epParticles[i].pos.x, epParticles[i].pos.y);
            petalMeshes[i].draw();
            ofPopMatrix();
        }
        ofPopMatrix();
    }
    
    
    string str = "petalLength:"+ ofToString(petalLength);
    ofDrawBitmapStringHighlight(str,5,10);
}




//===========

PrunusExplosionParticle::PrunusExplosionParticle(ofVec3f _basePos, ofColor _color, float maxVel){
    pos = ofPoint(0,0);
    basePos = _basePos;
    color = _color;
    //color.a = ofRandom(125,255);
    
    maxVel*=0.3;
    vel = ofVec3f(ofRandom(-maxVel,maxVel),ofRandom(-maxVel,maxVel),0);
    
    //in case vel is randomized to 0
    if(vel.length()<=0.05){
        vel.normalize();
        vel*=0.15;
    }
    
    gra = ofVec3f(0,0,0);//gravity
    angle = ofRandom(360);
}

void PrunusExplosionParticle::update(){
    if(!isAlive)
        return;
    vel+=gra;
    pos+=vel;
    

    //cout<<a<<endl;
    
    if(pos.x+basePos.x> param.WIDTH || pos.x+basePos.x<0 ||pos.y+basePos.y>param.HEIGHT||pos.y+basePos.y<0 /*|| color.a <=0*/){
        isAlive = false;
    }
    
}

void PrunusExplosionParticle::draw(){
    if(!isAlive)
        return;
    ofSetColor(ofColor::white);
    ofFill();

    ofDrawEllipse(basePos+pos, size, size);
    
}


