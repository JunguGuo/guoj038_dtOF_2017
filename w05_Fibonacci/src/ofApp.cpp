#include "ofApp.h"
#include "Fibonacci.h"

//--------------------------------------------------------------
void ofApp::setup(){
   // ofSetFrameRate(30);
    ofBackground(0);
    for(int i=0; i<num; i++){
        fibo.push_back(Fibonaccii(i)) ;
    }
//    ofSetVerticalSync(true);
//    ofSetFullscreen(true);
    ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i=0; i<num; i++){
        fibo[i].update();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i=0; i<num; i++){
        fibo[i].draw();
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
