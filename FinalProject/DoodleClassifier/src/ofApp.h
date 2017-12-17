#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxGrt.h"
#include "ofxCcv.h"
#include "ofxOsc.h"

#include "Params.hpp"
#include "Mum.hpp"
#include "Lotus.hpp"
#include "Bamboo.hpp"
#include "Prunus.hpp"
#include "FoundSquare.hpp"
using namespace ofxCv;
using namespace cv;

//#define RELEASE


// where to send osc messages by default
#define DEFAULT_OSC_DESTINATION "localhost"
#define DEFAULT_OSC_ADDRESS "/classification"
#define DEFAULT_OSC_PORT 5000





class ofApp : public ofBaseApp
{
public:

    // default class names if none found in settings_doodleclassifier.xml
    vector<string> classNames =
    {
        "circle",
        "cross",
        "fork",
        "line",
        "dots"
    };
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void windowResized(int w, int h);
    void setTrainingLabel(int & label_);
    void addSamplesToTrainingSet();
    void gatherFoundSquares();
    void trainClassifier();
    void classifyCurrentSamples();
    
    void addSamplesToTrainingSetNext();
    void classifyNext();
    
    void save();
    void load();
    
    int width, height;
    
    ofVideoGrabber cam;
    ContourFinder contourFinder, contourFinder2;
    ofFbo fbo;
    ofxCvGrayscaleImage grayImage;
    ofxCvColorImage colorImage;
    
    ofxOscSender sender;
    string oscDestination, oscAddress;
    int oscPort;
    
    ofxPanel gui;
    ofxToggle bRunning,bTestRun,bDebugArt;
    ofxButton bAdd, bTrain, bClassify, bSave, bLoad;
    ofParameter<float> minArea, maxArea, threshold,interval;
    ofParameter<int> nDilate;
    ofParameter<int> trainingLabel;
    
    vector<FoundSquare> foundSquares;
    vector<FoundSquare> stayingSquares;
    
    ClassificationData trainingData;
    GestureRecognitionPipeline pipeline;
    ofxCcv ccv;
    bool isTrained, toAddSamples, toClassify;
    
    bool showGui = true;
    bool showCam= true;
    bool fullscreen= false;
    float LastTime = 0.0;
    //float interval = 1.5;
    
    vector<Mum> mums;
    vector<Lotus> lotuses;
    vector<Prunus> prunuses;
};
