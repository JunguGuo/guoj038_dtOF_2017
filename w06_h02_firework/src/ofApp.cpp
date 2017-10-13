#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofBackground(0);
	
	gravity = ofVec2f(0,.2);
	
	//lastUpdateTime = ofGetElapsedTimef();
    
   // fireworks.push_back(ParticleSystem());
    ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void ofApp::update(){
//    if(ofRandom(1)<0.1)
//        fireworks.push_back(ParticleSystem());
    
	//lastUpdateTime = ofGetElapsedTimef();
    for(int i =0;i<fireworks.size();i++){
       // fireworks[i].applyForce(gravity);
        fireworks[i].update();
        if(fireworks[i].dead()){
            //remove fireworks[i]
            fireworks.erase(fireworks.begin()+i);
            
        }
    }
    
    
    if(ofGetMousePressed(0)){
        userLauncherRange =  userLauncherRange>100? 100: userLauncherRange+1;
        ofDrawBitmapStringHighlight("pressed"+ofToString(userLauncherRange), 20,20);
    }
    else{
        userLauncherRange = userLauncherRange>0.001? userLauncherRange*0.7 : 0;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0, 20);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	
//	ofBackgroundGradient(ofColor::pink, ofColor::goldenRod);
	
    for(int i =0;i<fireworks.size();i++)
        fireworks[i].draw();
    
    //draw launcher
    ofPushStyle();
    ofNoFill();
    ofSetColor(255);
    ofPoint launcher = ofPoint(ofGetWidth()/2, ofGetHeight());
    ofDrawCircle(launcher, launcherRange);
    ofSetLineWidth(3);
    ofPoint mousePos = ofPoint(ofGetMouseX(),ofGetMouseY());
    
    ofVec2f diff = mousePos - launcher;
    diff.normalize();
    diff *= launcherRange;
    ofDrawLine(launcher, launcher+diff);
    
   
    ofSetColor(ofColor::fromHsb(hu, 255, 255));
    diff.normalize();
    launchVel = diff*userLauncherRange;
    launchPos = launcher+launchVel;
    ofDrawLine(launcher, launchPos);
    ofPopStyle();
    
    
    
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	fireworks.push_back( ParticleSystem(launchPos,launchVel*0.2,hu));	// construct new particle system

    
    

}

void ofApp::mousePressed(int x, int y, int button){
    
     hu =ofRandom(255);
}

