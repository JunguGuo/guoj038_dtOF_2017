#pragma once
#include "ofMain.h"

class Fibonaccii{
public:
    Fibonaccii(int id);
    void update();
    void draw();
private:
    int id;
    float r;
    float t;
    ofVec2f pos;
    int size = 3;
    ofColor c;
    
};
