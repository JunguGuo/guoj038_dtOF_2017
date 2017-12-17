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
    gravity = 1;
    WIDTH = ofGetWidth();
    HEIGHT = ofGetHeight();
}
