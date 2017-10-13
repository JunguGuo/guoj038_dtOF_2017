#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofSetBackgroundAuto(false);
    ofBackground(ofColor::fromHex(0x0D2131));
   // moon = Moon(ball1);
    
//    for(int i=0;i<nAsteroids;i++){
//        ofVec2f randomDiff = ofVec2f(ofRandom(-20,20),ofRandom(-20,20));
//        ofVec2f temp = randomDiff;
//        temp.set(50);
//        
//        randomDiff = temp + randomDiff;
//        //cout<<randomDiff<<endl;
//        ofVec2f vel = randomDiff.perpendicular();
//        vel.normalize();
//        vel*= ofRandom(3);
//        
//        asteroids.push_back(Ball(1,sun.pos+randomDiff,vel, ofColor::fromHex(0xABCAD7)));
//    }
    asteroids.push_back(Ball(1,ofVec2f(ofGetWidth()/2,50),ofVec2f(-2,0), ofColor::fromHex(0xABCAD7)));
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //ofVec2f gravity(0, 0.1*ball1.mass);
    //ball1.applyForce(gravity);
    
    ball1.applyForce(( sun.calculateAttraction(ball1)));
    ball1.update();
    
    moon.update();
    
    for(int i = 0;i<asteroids.size();i++){
        asteroids[i].applyForce(( sun.calculateAttraction(asteroids[i])));
        asteroids[i].update();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

   // ofBackground(127);
    ball1.draw();
    
    sun.draw();
    
    moon.draw();
    
        for(int i = 0;i<asteroids.size();i++){
            asteroids[i].draw();
        }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
