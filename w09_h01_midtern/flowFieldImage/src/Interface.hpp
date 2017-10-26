//
//  Interface.hpp
//  flowFieldImage
//
//  Created by JohnGuo on 25/10/2017.
//
//
#pragma once
#ifndef Interface_hpp
#define Interface_hpp

#include <stdio.h>

#endif /* Interface_hpp */
#include "ofMain.h"

//------------ GUI --------------
//Slider class
class Slider {
public:
    string title;		//Title
    ofRectangle rect;	//Rectangle for drawing
    float *value;       //Pointer to value which the slider changes
    float minV, maxV;   //Minimum and maximum values
};


//Interface class, which manages sliders
class Interface {
public:
    void setup();
    void addSlider( string title, float *value, float minV, float maxV );
    void draw();
    
    void save( int index );		//Save preset
    void load( int index );		//Load preset
    
    void mousePressed( int x, int y );
    void mouseDragged( int x, int y );
    void mouseReleased (int x, int y );
    
    vector<Slider> slider;	//Array of sliders
    
    int selected;			//Index of selected slider
};
//-------------------------------

