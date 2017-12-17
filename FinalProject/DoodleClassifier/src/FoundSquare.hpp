//
//  FoundSquare.hpp
//  DoodleClassifier
//
//  Created by 俊谷郭 on 12/5/17.
//
#pragma once
#ifndef FoundSquare_hpp
#define FoundSquare_hpp

#include <stdio.h>

#endif /* FoundSquare_hpp */
#include "ofMain.h"
#include "ofxCv.h"
//#include "ofxCcv.h"
//#include "Mum.hpp"

using namespace cv;
struct FoundSquare {
    ofImage img;
    string label;
    bool isPrediction = false;
    cv::Rect rect;
    float area;
    void draw();
    void drawArt(bool bDebugArt);
    ofPoint& getCenter();
    bool checked = false;
   // Mum myMum;
};
