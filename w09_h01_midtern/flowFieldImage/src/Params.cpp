//
//  Params.cpp
//  flowFieldImage
//
//  Created by JohnGuo on 24/10/2017.
//
//

#include "Params.hpp"

Params param;        //Definition of global variable

void Params::setup() {
    eCenter = ofPoint( ofGetWidth() / 2, ofGetHeight() / 2 );
    eRad = 100;
    velRad = 0;
    lifeTime = 100;
    
    rotate = 0;
    force = 1000;
    spinning = 1000;
    damping = 0.05;
    flowFieldRes = 20;
    history = 0.9;
    strokeSize = 30.;
    //showFlowField.setup("Show Flow Field",false);
}
