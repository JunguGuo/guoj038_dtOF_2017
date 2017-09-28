#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    leftEye.pos = ofVec2f(332,280);
    leftEye.centerPos = ofVec2f(332,280);
    rightEye.pos = ofVec2f(692,280);
    rightEye.centerPos = ofVec2f(692,280);
    
    mouseCornerLeft =  ofVec2f(332-15,580);
    mouseCornerRight = ofVec2f(692+15,580);
    
    leftWind = *new ofVec2f(-windStrength,0);
    rightWind = *new ofVec2f(windStrength,0);
    testBanana = *new Banana();
}

//--------------------------------------------------------------
void ofApp::update(){
    leftEye.update();
    rightEye.update();
    
    //mouseOpeness
    ofVec2f center( ofGetWidth()/2, ofGetHeight()/2);
    
    ofVec2f mousePos(ofGetMouseX(),ofGetMouseY());
    float dist =  mousePos.distance(center);
    
    float targetMouseOpeness = ofMap(dist, 0, center.length(), 150, 15);
    
    mouseOpeness = mouseOpeness*mouseOpenessPct + (1-mouseOpenessPct)*targetMouseOpeness;
    
    
    testBanana.update();
    currentBanana.update();
    //banana
    for (int i = 0; i < bananas.size(); i++) {	// one way to loop through a whole vector
        bananas[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(251,223,87);
    ofDrawBitmapString(ofToString(mouseX)+" "+ ofToString(mouseY), 20, 20);
    
    
    ofPushMatrix();
    ofTranslate(512, 280);
    
    ofSetColor(79,71,69);                   //eyeglass belt
    ofSetRectMode( OF_RECTMODE_CENTER );
    ofDrawRectangle(0,0,1024,107);
    
    
    ofPushMatrix();
    ofTranslate(-180, 0);   //left eye
    ofSetColor(132, 134, 133);
    ofDrawCircle(0, 0, 184); //left eye white
    ofSetColor(ofColor::white);
    ofDrawCircle(0, 0, 150);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(180, 0);   //right eye
    ofSetColor(132, 134, 133);
    ofDrawCircle(0, 0, 184); //right eye white
    ofSetColor(ofColor::white);
    ofDrawCircle(0, 0, 150);
    ofPopMatrix();
    
    ofPopMatrix();
    
    leftEye.draw();
    rightEye.draw();
    
    
    ofSetLineWidth(15);
    ofSetColor(254,104,77);
//    ofDrawLine(mouseCornerLeft.x, mouseCornerLeft.y, mouseCornerRight.x, mouseCornerRight.y);
    
    
    ofDrawBezier(mouseCornerLeft.x, mouseCornerLeft.y, mouseCornerLeft.x, mouseCornerLeft.y+mouseOpeness, mouseCornerRight.x, mouseCornerRight.y+mouseOpeness, mouseCornerRight.x, mouseCornerRight.y);
    
    
    //banana
    for (int i = 0; i < bananas.size(); i++) {	// one way to loop through a whole vector
        bananas[i].draw();
    }
    
    testBanana.draw();
    currentBanana.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_LEFT){
        //apply left wind
        currentBanana.ApplyForce(leftWind);
        ; // do something
    } else if (key == OF_KEY_RIGHT){
        //apply right wind
        currentBanana.ApplyForce(rightWind);
         // do something else
    }
    
    if (key == OF_KEY_DOWN){
        //apply left wind
        Banana tempBanana;
        bananas.push_back(tempBanana);
        currentBanana = tempBanana;
        ; // do something
    }


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
