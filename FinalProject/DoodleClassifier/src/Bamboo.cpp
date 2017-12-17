//
//  Bamboo.cpp
//  FloralBrushArt
//
//  Created by 俊谷郭 on 12/4/17.
//

#include "Bamboo.hpp"
void Bamboo::setup(ofPoint _pos){
     int num = ofRandom(2,5);
    pos = _pos;
    color.setHex(0x5CA76C);
    color.a = 125;
    scale = 0.3;
    for(int i=0;i<num;i++){
        //-------------
        float _radius = ofRandom(60.0);
        float _angle = ofRandom(-45.0,45.0);
        //float _scale = ofRandom(0.3,1.0);
        
        int x = _radius*cos(ofDegToRad(_angle));
        int y = _radius*sin(ofDegToRad(_angle));
//        ofPushMatrix();
//        ofTranslate(x, y);
//        ofRotate(_angle);
//        ofScale(_scale, _scale);
        GeneratePetal(x, y, _angle);
    }
}

void Bamboo::update(){
   // pos = ofPoint(ofGetMouseX(),ofGetMouseY());
}
//void Bamboo::updatePetalMeshes(){
//    petalMeshes.clear();
//    float pX = 0.0;
//    float pY = 0.0;
//    int diameter = radius * 2;
//    int centerX = 0;
//    int centerY = 0;
//    //    if (verbose) {
//    //        // if true draw center point
//    //        ofSetColor(255, 255, 0);
//    //        ofDrawEllipse(centerX, centerY, controlPointDiameter, controlPointDiameter);
//    //    }
//
//
//
//    // reset starting angle to 0 degrees
//    float angle = 0.0;
//
//    // draw petals around the center ellipse of the flower
//    for (int c = 0; c < totalPetals; c++)  {
//
//        // calculate starting point
//        pX = centerX + cos(ofDegToRad(angle)) * radius;
//        pY = centerY + sin(ofDegToRad(angle)) * radius;
//
//        // call drawPetal function to calculate control points and set bezierVertices
//        GeneratePetal(pX, pY, angle);
//
//        // increment angle based on total number of petals
//        angle -= (360 / totalPetals);
//    }
//}


void Bamboo::GeneratePetal(float startX, float startY, float angle) {
    
    // set offset for control points
    float bezierDiff = petalLength / 3;
    
    // set angle for start's control points
    float startAngleTop = angle - 90;
    float startAngleBottom = angle + 90;
    
    // set angle for end's control points
    float endAngleTop = angle - 135;
    float endAngleBottom = angle + 135;
    
    // calculate start's top control point
    float startAngleTopX = startX + cos(ofDegToRad(startAngleTop))*bezierDiff;
    float startAngleTopY = startY + sin(ofDegToRad(startAngleTop))*(bezierDiff/4);
    
    // calculate start's bottom control point
    float startAngleBottomX = startX + cos(ofDegToRad(startAngleBottom))*bezierDiff;
    float startAngleBottomY = startY + sin(ofDegToRad(startAngleBottom))*(bezierDiff/4);
    
    // calculate end point
    float endX = startX + cos(ofDegToRad(angle))*petalLength;
    float endY = startY + sin(ofDegToRad(angle))*petalLength;
    
    // calculate end's top control point
    float endAngleTopX = endX + cos(ofDegToRad(endAngleTop))*bezierDiff;
    float endAngleTopY = endY + sin(ofDegToRad(endAngleTop))*(bezierDiff/4);
    
    // calculate end's bottom control point
    float endAngleBottomX = endX + cos(ofDegToRad(endAngleBottom))*bezierDiff;
    float endAngleBottomY = endY + sin(ofDegToRad(endAngleBottom))*(bezierDiff/4);
    
    

    
    
    ofPath path;
    path.moveTo(startX,startY);
    path.bezierTo(startAngleTopX, startAngleTopY, endAngleTopX, endAngleTopY, endX, endY);
    path.bezierTo(endAngleBottomX, endAngleBottomY, startAngleBottomX, startAngleBottomY, startX, startY);
    //ofMesh& mesh = path.getTessellation(); // get reference to path's mesh
    // or make a copy:
    ofMesh mesh = path.getTessellation();
    petalMeshes.push_back(mesh);

  
    //------coloring------
    //    int verNum = mesh.getNumVertices();
    //    vector<ofFloatColor> colors;
    //    for(int i=0;i<verNum;i++)
    //    {
    //        colors.push_back(ofFloatColor(i*0.1,0.5,0,1));
    //    }
    //    mesh.addColors(colors);
    //---------------------
    
    
    
    
    
}


void Bamboo::draw(){
    
    
   
    
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofScale(scale, scale);
    for(int i =0;i<petalMeshes.size();i++){
        ofRotate(sin(ofGetElapsedTimef()+i*1000)*25);
        ofSetColor(color);
        petalMeshes[i].draw();
        
    }
    ofPopMatrix();
    
}
//void Bamboo::drawLeaf(float startX, float startY, float angle, float scale){
//    // set offset for control points
//    float bezierDiff = petalLength / 3;
//
//    // set angle for start's control points
//    float startAngleTop = angle - 90;
//    float startAngleBottom = angle + 90;
//
//    // set angle for end's control points
//    float endAngleTop = angle - 135;
//    float endAngleBottom = angle + 135;
//
//    // calculate start's top control point
//    float startAngleTopX = startX + cos(ofDegToRad(startAngleTop))*bezierDiff;
//    float startAngleTopY = startY + sin(ofDegToRad(startAngleTop))*(bezierDiff/4);
//
//    // calculate start's bottom control point
//    float startAngleBottomX = startX + cos(ofDegToRad(startAngleBottom))*bezierDiff;
//    float startAngleBottomY = startY + sin(ofDegToRad(startAngleBottom))*(bezierDiff/4);
//
//    // calculate end point
//    float endX = startX + cos(ofDegToRad(angle))*petalLength;
//    float endY = startY + sin(ofDegToRad(angle))*petalLength;
//
//    // calculate end's top control point
//    float endAngleTopX = endX + cos(ofDegToRad(endAngleTop))*bezierDiff;
//    float endAngleTopY = endY + sin(ofDegToRad(endAngleTop))*(bezierDiff/4);
//
//    // calculate end's bottom control point
//    float endAngleBottomX = endX + cos(ofDegToRad(endAngleBottom))*bezierDiff;
//    float endAngleBottomY = endY + sin(ofDegToRad(endAngleBottom))*(bezierDiff/4);
//
//
//
//    // draw petal shape with points and control points
//    ofPushMatrix();
//    ofScale(scale,scale);
//    //    ofBeginShape();
//    //    ofVertex(startX, startY);
//    //    ofBezierVertex(startAngleTopX, startAngleTopY, endAngleTopX, endAngleTopY, endX, endY);
//    //    ofBezierVertex(endAngleBottomX, endAngleBottomY, startAngleBottomX, startAngleBottomY, startX, startY);
//    //    ofEndShape();
//    ofPath path;
//    path.moveTo(startX,startY);
//    path.bezierTo(startAngleTopX, startAngleTopY, endAngleTopX, endAngleTopY, endX, endY);
//    path.bezierTo(endAngleBottomX, endAngleBottomY, startAngleBottomX, startAngleBottomY, startX, startY);
//    //ofMesh& mesh = path.getTessellation(); // get reference to path's mesh
//    // or make a copy:
//    ofMesh mesh = path.getTessellation();
//    //mesh.setColor(0, ofColor::red);
//    mesh.draw();
//    ofPopMatrix();
//}

