#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::InitPortrait(){
    int w = image.getWidth();
    int h = image.getHeight();
    for (int x=0; x<w; x+=spacing) {
        for (int y=0; y<h; y+=spacing) {
            ofColor c = image.getColor(x, y);
            float b = c.getBrightness();
            float h = c.getHue();
            float s = c.getSaturation();
            
            Sphere sp(ofVec3f(ofMap(x, 0, 800, -800,800),ofMap(y, 0, 800, 800,-800),b),size,c);
            spheres.push_back(sp);
        }
    }
    
}
void ofApp::setup(){
    ofSetFrameRate(60);
    image.load("stars44.jpg");
    image.resize(800, 800);
    
    //gui
    gui.setup( "Parameters", "settings.xml" );
    gui.add( spacing.setup( "spacing", 15, 10, 50 ) );
    gui.add( size.setup( "size", 14.5, 5, 20 ) );
    
    // setup lights
    
    ofSetSmoothLighting(true);        // nicer lighting rendering
    
    
    // setup point light
    
    light.setPointLight();
    
    light.setPosition(0, 0, 1200);
    light.setDiffuseColor( ofColor::white );
    
    light.setAttenuation(.6);    // adjust the light throw
    
    light2.setPointLight();
    
    light2.setPosition(0, 0, -800);
    light2.setDiffuseColor( ofColor::white );
    
    light2.setAttenuation(.7);
    
    InitPortrait();

    
//    easyCam.setAutoDistance(false);
//    easyCam.setTarget(ofVec3f(300,300,300));
//    easyCam.setDistance(500);
    
    ofHideCursor();

}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i=0;i<spheres.size();i++){
        spheres[i].update();
    }

    
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    
    ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
//    ofBackgroundGradient( ofColor( 255 ), ofColor( 128 ) );
    
    easyCam.begin();
        ofPushMatrix();
         // turn on lighting globally
    ofEnableDepthTest();    // render objects in order of depth
  ofEnableLighting(); 
    light.enable();            // enable our lights
    light2.enable();
    
    //ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    for (int i=0;i<spheres.size();i++){
        spheres[i].draw();
    }
        ofPopMatrix();
    light.disable();
    ofDisableLighting();


    easyCam.end();
    
    
    ofDisableDepthTest();
    
    ofDrawAxis(100);
    if(showGui)
    gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
        if (key == 'r') {
            spheres.clear();
            InitPortrait();
        }
    if (key == 's') {
        showGui = !showGui;
    }
    if (key == OF_KEY_RETURN) {
        ofToggleFullscreen();
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
