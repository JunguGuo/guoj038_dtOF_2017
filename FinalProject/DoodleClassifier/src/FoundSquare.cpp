//
//  FoundSquare.cpp
//  DoodleClassifier
//
//  Created by 俊谷郭 on 12/5/17.
//

#include "FoundSquare.hpp"


//--------------------------------------------------------------
void FoundSquare::draw() {
    img.draw(0, 0);
    string labelStr = "no class";
    labelStr = (isPrediction?"predicted: ":"assigned: ")+label;
    ofDrawBitmapStringHighlight(labelStr, 4, img.getHeight()-22);
    ofDrawBitmapStringHighlight("{"+ofToString(rect.x)+","+ofToString(rect.y)+","+ofToString(rect.width)+","+ofToString(rect.height)+"}, area="+ofToString(area), 4, img.getHeight()-5);
}
//-----------------
void FoundSquare::drawArt(bool bDebugArt) {
    
    //    ofPushStyle();
    //    ofSetColor(ofColor::blue);
    //    ofPoint center( (rect.x+rect.width)/2, (rect.y+rect.height)/2);
    //    ofDrawCircle( center,rect.width/2);
    //    ofPopStyle();
    
    
    if(label=="circle"){
        if(bDebugArt){
            ofPushStyle();
            ofSetColor(ofColor::blue);
            ofPoint center( (rect.x+rect.width/2), (rect.y+rect.height/2));
            ofDrawCircle( center,rect.width/2);
            ofPopStyle();}
    }
    
    else if(label=="cross"){
        if(bDebugArt){
            ofPushStyle();
            ofSetColor(ofColor::red);
            ofDrawRectangle(rect.x, rect.y, rect.width, rect.height);
            //cout<<"bbbb"<<rect.x<<endl;
            ofPopStyle();}
        
    }
    
}

//========

ofPoint& FoundSquare::getCenter() {
    ofPoint center((rect.x+rect.width/2), (rect.y+rect.height/2));
    return center;
}
