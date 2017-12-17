//
//  Lotus.cpp
//  FloralBrushArt
//
//  Created by 俊谷郭 on 12/4/17.
//

#include "Lotus.hpp"


//--------
void Lotus::setup(FoundSquare* _fs){
    //radius = _radius;
   // pos = _pos;
    petalLength = 0;
    leafSize = 0;
    initTime = ofGetElapsedTimef();
    state =State::appearing;
    color  = ofColor(242, 102, 121,125);
    lotusOffset = ofPoint(radius,radius);
    myfs = _fs;
    pos = myfs->getCenter();
}

void Lotus::update(){
       // petalLength = ofMap(ofGetMouseX(),0, param.WIDTH, 1.0, 200.0);
    if(myfs!=nullptr)
        pos = myfs->getCenter();
    
    if(ofGetKeyPressed('0')){
        state = State::appearing;
        petalLength = 0;
        leafSize = 0;
        angle = 0;
        initTime = ofGetElapsedTimef();
        color  = ofColor(242, 102, 121,125);
        
    }
    if(ofGetKeyPressed('2')){

            explode();
            initTime = ofGetElapsedTimef();
    }
    
    switch(state){
        case none:
            //
            break;
        case State::appearing:
        {
            
            float endTime = initTime + appearDuration;
            float now = ofGetElapsedTimef();
            petalLength = ofxeasing::map_clamp(now, initTime, endTime, 1, -maxPetalLengthPct*radius, &ofxeasing::sine::easeInOut);
            updatePetalMeshes(&petalMeshes);
            
            
            petalLength = ofxeasing::map_clamp(now, initTime, endTime, 1, -maxCentralLengthPct*radius, &ofxeasing::sine::easeInOut);
            updatePetalMeshes(&centralMeshes);
            
            leafSize = ofxeasing::map_clamp(now, initTime, endTime, 1,radius*maxleafSizePct, &ofxeasing::sine::easeInOut);
            
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
            //
        }
            break;
        case State::dead:
            cout<<"dead"<<endl;
            break;
    }
    
    //cout<<petalMeshes.size()<<":"<<epParticles.size()<<endl;
    
}


void Lotus::explode(){
    //fix this
    
    
    state = State::dead;
}

void Lotus::updatePetalMeshes(vector<ofMesh>* meshes){
    meshes->clear();
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
        GeneratePetal(pX, pY, angle,meshes);
        
        // increment angle based on total number of petals
        angle -= (360 / totalPetals);
    }
}


void Lotus::GeneratePetal(float startX, float startY, float angle,vector<ofMesh>* meshes ) {
    
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
    meshes->push_back(mesh);
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



void Lotus::draw() {
//    for(int i = 0;i<epParticles.size();i++){
//        epParticles[i].draw();
//    }
//
    
    if(state!= State::exploding && state!= State::dead){
        
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        ofRotate(angle);
        angle+=rotateSpeed;
        
        //draw lotus leaf
        ofColor leafColor =ofColor::greenYellow;
        leafColor.a = 150;
        ofSetColor(leafColor);
        ofFill();
        ofSetCircleResolution(30);
        ofDrawCircle(0, 0, leafSize);
        
        
        //draw lotus flower
        ofPushMatrix();
        ofTranslate(lotusOffset);
        //--------
        ofSetColor(255, 0, 0);
        // draw center ellipse of the flower
        ofNoFill();
        ofDrawEllipse(0, 0, radius*2, radius*2);
        for(ofMesh& mesh:petalMeshes){
            ofSetColor(color);
            //mesh.setColor(0, ofColor::red);
            mesh.draw();
        }
        
        for(ofMesh& mesh:centralMeshes){
            ofColor centraColor =ofColor::yellow;
            centraColor.a = 180;
            ofSetColor(centraColor);
            ofSetColor(centraColor);
            //mesh.setColor(0, ofColor::red);
            mesh.draw();
        }
        ofPopMatrix();
        
        
        
        
        ofPopMatrix();
    }
    if(state == State::exploding){
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        //ofRotate(angle);
        angle+=rotateSpeed;
        
        
        for(int i =0;i<petalMeshes.size();i++){
            //**fix this

        }
        ofPopMatrix();
    }
    
    
    string str = "petalLength:"+ ofToString(petalLength);
    ofDrawBitmapStringHighlight(str,5,10);
}


