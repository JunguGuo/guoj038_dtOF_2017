#include "ofApp.h"
#include "Params.hpp"

void ofApp::setup(){
    // settings

    ofSetFrameRate( 60 );	//Set screen frame rate
    
    //Allocate drawing buffer
    int w = ofGetWidth();
    int h = ofGetHeight();
    fbo.allocate( w, h, GL_RGB32F_ARB );
    
    //Fill buffer with white color
    fbo.begin();
    ofBackground(255, 255, 255);
    fbo.end();
    
    //Set up parameters
    param.setup();		//Global parameters
    bornRate = 5000;
    bornCount = 0;
    time0 = ofGetElapsedTimef();

	
	//ofBackground(255);
	//ofSetBackgroundAuto(false);
	
	image.load("image.jpg");	// image.jpg is in "bin/data/" folder
	
	// create the flow field at image size, 20 px resolution
	flowField = FlowField(image.getWidth(), image.getHeight(), param.flowFieldRes);
	
	// initialize the flows per the image brightness values
	
    //flowField.initFromImage(image, 0.1);
    flowField.initRandom(0.1);

	
    
  
    //GUI
    interf.setup();
    interf.addSlider( "rate", &bornRate, 0, 5000 );
    interf.addSlider( "lifeTime", &param.lifeTime, 0, 100 );
    interf.addSlider( "history", &param.history, 0, 1 );
    
//    interf.addSlider( "eRad", &param.eRad, 0, 800 );
//    interf.addSlider( "velRad", &param.velRad, 0, 400 );
//    interf.addSlider( "rotate", &param.rotate, -500, 500 );
//    interf.addSlider( "spinning", &param.spinning, -1000, 1000 );
//    interf.addSlider( "force", &param.force, -1000, 1000 );
    interf.addSlider( "damping", &param.damping, 0, 0.1 );
    interf.addSlider( "flowFieldRes", &param.flowFieldRes, 15, 100 );
    interf.addSlider( "strokeSize", &param.strokeSize, 10, 100 );
    
    drawInterface = true;
    oxGui.setup( "Parameters", "settings.xml" );
    oxGui.add(DrawField.setup("Draw Field",false));
    //oxGui.add(DrawField.setup("RainMode",false));
    
    // make a bunch of particles
    for (int i=0; i<bornRate; i++){
        
        Particle p;
        p.pos.x = ofRandom(0, ofGetWidth());
        p.pos.y = ofRandom(0, ofGetHeight());
        
        particles.push_back(p);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
   
    //Compute dt
    float time = ofGetElapsedTimef();
    float dt = ofClamp( time - time0, 0, 0.1 );
    time0 = time;
    

    //update particles
	for (int i=0; i<particles.size(); i++)
	{
		// get the force at the particle position
        ofVec3f force = flowField.getForceAt(particles[i].pos);
		
		particles[i].applyForce(force);
		particles[i].applyDamping(param.damping);
		particles[i].update(dt);
        
        if ( !particles[i].live ) {
            particles.erase( particles.begin() + i );
        }
	}
    
    if(particles.size()==0){
        // make a bunch of particles
        for (int i=0; i<bornRate; i++){
            
            Particle p;
            p.pos.x = ofRandom(0, ofGetWidth());
            p.pos.y = ofRandom(0, ofGetHeight());
            
            particles.push_back(p);
        }}
    
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground( 255, 255, 255 );
    
    //----------------
    //1. Drawing to buffer
    fbo.begin();
    
    //Draw semi-transparent white rectangle
    //to slightly clearing a buffer (depends on history value)
    
    ofEnableAlphaBlending();         //Enable transparency
    
    float alpha = (1-param.history) * 255;
    ofSetColor( 255, 255, 255, alpha );
    ofFill();
    //ofDrawRectangle( 0, 0, ofGetWidth(), ofGetHeight() );
    image.draw(0, 0, ofGetWidth(), ofGetHeight());
       //Disable transparency
    
    //Draw the particles
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    for (int i=0; i<particles.size(); i++)
    {
        particles[i].draw();
    }
      ofDisableAlphaBlending();   
    if(DrawField){
        flowField.draw(10*param.flowFieldRes);
    }
    
    fbo.end();
    
    
    //----------------
    //2. Draw buffer on the screen
    ofSetColor( 255, 255, 255 );
    fbo.draw( 0, 0 );
    
    
    //----------------
    //4. brushOutline
    ofNoFill();
    ofSetColor(200, 200, 200);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), param.strokeSize);
    


    //----------------
    //3. GUI
    if ( drawInterface ) {
        //Draw text
        ofSetColor( 0, 0, 0 );
        ofDrawBitmapString( "Keys: Enter-hide/show GUI, Space-screenshot, 1,2,...,9-load preset, Shift+1,2,...9-save preset", 20, 20 );
//        ofDrawBitmapString( "Particles: " + ofToString( p.size() ), 20, 40 );
        
        string label =	"press ' ' : reset particle positions \n";
        label +=			"'UP'/'DN' : damping = " + ofToString(param.damping);
        ofDrawBitmapStringHighlight(label, 20,40);

        
        //Draw sliders
        interf.draw();
        // draw the text labels
        

    }
    
    oxGui.draw();
    
}
//--------------------------------------------------------------
//----------------------  testApp again  -----------------------
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if ( key == OF_KEY_TAB  ) {	//Hide/show GUI
        drawInterface = !drawInterface;
    }
    
    if ( key == OF_KEY_RETURN ) {		//Grab the screen image to file
        ofImage image;
        image.grabScreen( 0, 0, ofGetWidth(), ofGetHeight() );
        
        //Select random file name
        int n = ofRandom( 0, 1000 );
        string fileName = "screen" + ofToString( n ) + ".png";
        
        image.saveImage( fileName );
    }
    
    //Load presets
    if ( key == '1' ) { interf.load( 1 ); }
    if ( key == '2' ) { interf.load( 2 ); }
    if ( key == '3' ) { interf.load( 3 ); }
    if ( key == '4' ) { interf.load( 4 ); }
    if ( key == '5' ) { interf.load( 5 ); }
    if ( key == '6' ) { interf.load( 6 ); }
    if ( key == '7' ) { interf.load( 7 ); }
    if ( key == '8' ) { interf.load( 8 ); }
    if ( key == '9' ) { interf.load( 9 ); }
    
    //Save presets
    if ( key == '!' ) { interf.save( 1 ); }
    if ( key == '@' ) { interf.save( 2 ); }
    if ( key == '#' ) { interf.save( 3 ); }
    if ( key == '$' ) { interf.save( 4 ); }
    if ( key == '%' ) { interf.save( 5 ); }
    if ( key == '^' ) { interf.save( 6 ); }
    if ( key == '&' ) { interf.save( 7 ); }
    if ( key == '*' ) { interf.save( 8 ); }
    if ( key == '(' ) { interf.save( 9 ); }
}



//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if (key == ' ')
    {
        particles.clear();
		// clear background
		ofBackground(255);
        // create the flow field at image size, 20 px resolution
        flowField = FlowField(image.getWidth(), image.getHeight(), param.flowFieldRes);
        
        // initialize the flows per the image brightness values
       
        //flowField.initFromImage(image, 0.1);
        flowField.initRandom(0.1);
        

	}
//	else if (key == 'f' || key == 'F')
//	{
//		// 'F' toggle field draw
//		bDrawField = !bDrawField;
//	}

    
    
    
	
	// adjust damping using up, down arrows

//	else if (key == OF_KEY_UP)
//	{
//		damping += 0.01;
//	}
//	else if (key == OF_KEY_DOWN)
//	{
//		damping -= 0.01;
//		if (damping < 0) damping = 0;
//	}

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if ( drawInterface ) {
        interf.mouseDragged( x, y );
    }
    
    //stroke change flow field
    for (int i=0; i<flowField.field.size(); i++)
    {
        ofPoint mousePos(ofGetMouseX(),ofGetMouseY());
        ofVec3f diff = mousePos - flowField.getForcePos(i);
        //ofVec3f diff = mousePos - preMousePos;
        if( diff.length() < param.strokeSize){
            //inside stroke range
            //float angle = atan2(diff.y,diff.x);
                        ofVec3f dir = mousePos - preMousePos;
            //float angle = atan2(dir.y,dir.x);
            flowField.changeForceAngle(i, dir);

        }
    }
    
    preMousePos = ofPoint(ofGetMouseX(),ofGetMouseY());
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if ( drawInterface ) {
        interf.mousePressed( x, y );
    }
    preMousePos = ofPoint(ofGetMouseX(),ofGetMouseY());
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    interf.mouseReleased( x, y );
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
