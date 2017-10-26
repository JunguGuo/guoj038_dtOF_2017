#pragma once

#include "ofMain.h"
#include "FlowField.hpp"
#include "Particle.hpp"
#include "Interface.hpp"
#include "ofxGui.h"
class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
    
    //GUI
    Interface interf;
    bool drawInterface;
   
    float time0;          //Time value for computing dt
    
    float bornRate;       //Particles born rate per second
    float bornCount;      //Integrated number of particles to born
    ofxPanel oxGui;
    
    void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	FlowField flowField;
	vector<Particle> particles;
	
	bool bDrawTrails;
	ofxToggle DrawField;
	bool bDrawImage;
	
	//float damping;
	
    ofPoint preMousePos;
	ofImage image;
    ofFbo fbo;
};
