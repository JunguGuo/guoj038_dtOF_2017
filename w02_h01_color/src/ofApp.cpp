#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0);
    waterLevel = 500;

	int numBalls = 30;

	// fill our vector
//	for (int i = 0; i < numBalls; i++) {		// loop 30 times
//
//		Ball tempBall;					// create a temporary ball
//		balls.push_back(tempBall);		// copy the temporary ball into the balls vector
//										// (push_back() adds the ball to the end of the vector, increasing the vector's size by 1)
//	}

}

//--------------------------------------------------------------
void ofApp::update(){

	// update each ball in our vector
	for (int i = 0; i < balls.size(); i++) {	// one way to loop through a whole vector

		balls[i].update();	// we can access an individual ball by its "index" number in the vector
							// e.g. balls[0] is the first ball in the vector, balls[1] is the second ball, etc.
									// (note that vectors always start at 0, not 1!!)
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofFill();
    
    ofSetColor(255);
    ofDrawRectangle(0, waterLevel, 1024, 768);



	for (int i = 0; i < balls.size(); i++) {

		balls[i].draw();
        
        if(balls[i].y>waterLevel && balls[i].y<768){
        //calculate waterColor
        this->rT += balls[i].color.r ;
        
        this->gT += balls[i].color.g ;

        this->bT += balls[i].color.b ;
        
            this->aT += 1; //need fixing
        }
        

        
	}
    ofSetColor(255); // Set the drawing color to white
    ofSetLineWidth(2);
    ofDrawLine(0, waterLevel, 1024, waterLevel); // Line from (700, 50) to (700, 150)
    
    
    
    
    ofFill();
    
    ofColor myColor = ofColor(this->rT*1.5,this->gT*1.5,this->bT*1.5,this->aT*1.5);
    ofSetColor(myColor);
    ofLogWarning("Hello") << myColor;
    ofDrawRectangle(0, waterLevel, 1024, 768);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
//    waterLevel = y;

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    Ball tempBall((float)x,(float)y);
    balls.push_back(tempBall);
    

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
