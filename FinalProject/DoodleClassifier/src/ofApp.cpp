#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    param.WIDTH = ofGetWidth();
    param.HEIGHT = ofGetHeight();
    ofSetBackgroundColor(0);
//    ofEnableSmoothing();
//    ofEnableAlphaBlending();
    
    ofSetWindowShape(1600, 900);
    ofBackground(0);
    width = 750;//before: 640
    height = 480;
    
//#ifdef RELEASE
    ccv.setup(ofToDataPath("image-net-2012.sqlite3"));
//#else
//    ccv.setup(ofToDataPath("../../../../data/image-net-2012.sqlite3"));
//#endif

    cam.setDeviceID(0);
    cam.setup(width, height);
    
    bAdd.addListener(this, &ofApp::addSamplesToTrainingSetNext);
    bTrain.addListener(this, &ofApp::trainClassifier);
    bClassify.addListener(this, &ofApp::classifyNext);
    bSave.addListener(this, &ofApp::save);
    bLoad.addListener(this, &ofApp::load);
    trainingLabel.addListener(this, &ofApp::setTrainingLabel);
    
    // default settings
    oscDestination = DEFAULT_OSC_DESTINATION;
    oscAddress = DEFAULT_OSC_ADDRESS;
    oscPort = DEFAULT_OSC_PORT;
    
    // load settings from file
    ofXml xml;
    xml.load(ofToDataPath("settings_doodleclassifier.xml"));
    xml.setTo("DoodleOSC");
    oscDestination = xml.getValue("ip");
    oscPort = ofToInt(xml.getValue("port"));
    oscAddress = xml.getValue("address");
    if (xml.exists("classes") && xml.setTo("classes") && xml.exists("class[0]")) {
        xml.setTo("class[0]");
        classNames.clear();
        do {
            string newClass = xml.getValue();
            classNames.push_back(newClass);
        }
        while(xml.setToSibling());
    }

    sender.setup(oscDestination, oscPort);
    
    gui.setup();
    gui.setName("DoodleClassifier");
    ofParameterGroup gCv;
    gCv.setName("CV initial");
    gCv.add(minArea.set("Min area", 10, 1, 100));
    gCv.add(maxArea.set("Max area", 200, 1, 500));
    gCv.add(threshold.set("Threshold", 128, 0, 255));
    gCv.add(nDilate.set("Dilations", 1, 0, 8));
    gui.add(trainingLabel.set("Training Label", 0, 0, classNames.size()-1));
    gui.add(bAdd.setup("Add samples"));
    gui.add(bTrain.setup("Train"));
    gui.add(bRunning.setup("Run", false));
    gui.add(bDebugArt.setup("DebugArt", true));
    gui.add(interval.set("interval", 1.5, 0, 2));
    gui.add(bClassify.setup("Classify"));
    gui.add(bSave.setup("Save"));
    gui.add(bLoad.setup("Load"));
    gui.add(bTestRun.setup("TestRun",false));
    gui.add(gCv);
    gui.setPosition(0, 400);
    gui.loadFromFile("settings_doodleclassifier_cv.xml");
    
    fbo.allocate(width, height);
    colorImage.allocate(width, height);
    grayImage.allocate(width, height);
    isTrained = false;
    toAddSamples = false;
    toClassify = false;
    
    trainingData.setNumDimensions(4096);
    AdaBoost adaboost;
    adaboost.enableNullRejection(false);
    adaboost.setNullRejectionCoeff(3);
    pipeline.setClassifier(adaboost);
    
    LastTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if(cam.isFrameNew())
    {
        // get grayscale image and threshold
        colorImage.setFromPixels(cam.getPixels());
        grayImage.setFromColorImage(colorImage);
        for (int i=0; i<nDilate; i++) {
            grayImage.erode_3x3();
        }
        grayImage.threshold(threshold);
        //grayImage.invert();
        
        // find initial contours
        contourFinder.setMinAreaRadius(minArea);
        contourFinder.setMaxAreaRadius(maxArea);
        contourFinder.setThreshold(127);
        contourFinder.findContours(grayImage);
        contourFinder.setFindHoles(true);
        
        // draw all contour bounding boxes to FBO
        fbo.begin();
        ofClear(0, 255);
        ofFill();
        ofSetColor(255);
        for (int i=0; i<contourFinder.size(); i++) {
            //cv::Rect rect = contourFinder.getBoundingRect(i);
            //ofDrawRectangle(rect.x, rect.y, rect.width, rect.height);
            ofBeginShape();
            for (auto p : contourFinder.getContour(i)) {
                ofVertex(p.x, p.y);
            }
            ofEndShape();
        }
        fbo.end();
        ofPixels pixels;
        fbo.readToPixels(pixels);
        
        // find merged contours
        contourFinder2.setMinAreaRadius(minArea);
        contourFinder2.setMaxAreaRadius(maxArea);
        contourFinder2.setThreshold(127);
        contourFinder2.findContours(pixels);
        contourFinder2.setFindHoles(true);
        
        if (toAddSamples) {
            addSamplesToTrainingSet();
            toAddSamples = false;
        }
        else if (isTrained && (bRunning || toClassify)) {
            if(ofGetElapsedTimef() - LastTime > interval){
                classifyCurrentSamples();
                toClassify = false;
                LastTime = ofGetElapsedTimef();
            }
        }
    }
    
    //
    for(int i =0;i<mums.size();i++){
        mums[i].update();
        if(mums[i].state==Mum::State::dead){
            mums.erase(mums.begin()+i);
        }
    }
    for(int i =0;i<lotuses.size();i++){
        lotuses[i].update();
        if(lotuses[i].state==Lotus::State::dead){
            lotuses.erase(lotuses.begin()+i);
        }
    }
    for(int i =0;i<prunuses.size();i++){
        prunuses[i].update();
        if(prunuses[i].state==Prunus::State::dead){
            prunuses.erase(prunuses.begin()+i);
        }
    }


    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(70);
    ofSetColor(255);
    if(!bTestRun){
        ofPushMatrix();
        ofScale(0.75, 0.75);
        
        // original
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(0, 20);
        cam.draw(0, 0);
        ofDrawBitmapStringHighlight("original", 0, 0);
        for(FoundSquare& ss: stayingSquares){
            if(ss.label != "")
                ss.drawArt(bDebugArt);
        }
        //**fix this
        for(Mum& mum:mums)
            mum.draw();
        for(Lotus& lotus:lotuses)
            lotus.draw();
        for(Prunus& prunus:prunuses)
            prunus.draw();
        
        ofPopMatrix();
        ofPopStyle();
        
        // thresholded
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(width, 20);
        grayImage.draw(0, 0);
        ofSetColor(0, 255, 0);
        contourFinder.draw();
        ofDrawBitmapStringHighlight("thresholded", 0, 0);
        ofPopMatrix();
        ofPopStyle();
        
        // merged
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(2*width, 20);
        fbo.draw(0, 0);
        ofSetColor(0, 255, 0);
        contourFinder2.draw();
        ofDrawBitmapStringHighlight("merged", 0, 0);
        ofPopMatrix();
        ofPopStyle();
        
        ofPopMatrix();
        
        // draw tiles
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(210, 0.75*height+25);
        int nPerRow = max(5, (int) ceil(foundSquares.size()/2.0));
        ofTranslate(-ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, max(0,nPerRow-5)*226), 0);
        for (int i=0; i<foundSquares.size(); i++) {
            ofPushMatrix();
            ofTranslate(226*(i%nPerRow), 240*floor(i/nPerRow));
            foundSquares[i].draw();
            ofPopMatrix();
        }
        ofPopMatrix();
        ofPopStyle();
    }
    else{
        //ofSetColor(255);
        ofPushMatrix();
        ofScale(2, 2);
        if(showCam)
            cam.draw(0, 0);
        for(FoundSquare& fs: foundSquares){
            if(fs.label != "")
                fs.drawArt(bDebugArt);
        }
        //**fix this
        for(Mum& mum:mums)
            mum.draw();
        for(Lotus& lotus:lotuses)
            lotus.draw();
        for(Prunus& prunus:prunuses)
            prunus.draw();
        
        ofPopMatrix();
    }
    if(showGui)
        gui.draw();
    
 
}

//--------------------------------------------------------------
void ofApp::exit() {
    gui.saveToFile(ofToDataPath("settings_doodleclassifier_cv.xml"));
}

//--------------------------------------------------------------
void ofApp::gatherFoundSquares() {
    foundSquares.clear();
    for (int i=0; i<contourFinder2.size(); i++) {
        FoundSquare fs;
        fs.rect = contourFinder2.getBoundingRect(i);
        fs.area = contourFinder2.getContourArea(i);
        fs.img.setFromPixels(cam.getPixels());
        fs.img.crop(fs.rect.x, fs.rect.y, fs.rect.width, fs.rect.height);
        fs.img.resize(224, 224);
        foundSquares.push_back(fs);
        
    }
    

}

//--------------------------------------------------------------
void ofApp::addSamplesToTrainingSet() {
    ofLog(OF_LOG_NOTICE, "Adding samples...");
    gatherFoundSquares();
    for (int i=0; i<foundSquares.size(); i++) {
        foundSquares[i].label = classNames[trainingLabel];
        vector<float> encoding = ccv.encode(foundSquares[i].img, ccv.numLayers()-1);
        VectorFloat inputVector(encoding.size());
        for (int i=0; i<encoding.size(); i++) inputVector[i] = encoding[i];
        trainingData.addSample(trainingLabel, inputVector);
        ofLog(OF_LOG_NOTICE, " Added sample #"+ofToString(i)+" label="+ofToString(trainingLabel));
    }
}

//--------------------------------------------------------------
void ofApp::trainClassifier() {
    ofLog(OF_LOG_NOTICE, "Training...");
    if (pipeline.train(trainingData)){
        ofLog(OF_LOG_NOTICE, "getNumClasses: "+ofToString(pipeline.getNumClasses()));
    }
    isTrained = true;
    ofLog(OF_LOG_NOTICE, "Done training...");
}

//--------------------------------------------------------------
void ofApp::classifyCurrentSamples() {
//    ofLog(OF_LOG_NOTICE, "Classifiying on frame "+ofToString(ofGetFrameNum()));
    
    gatherFoundSquares();
    for (int i=0; i<foundSquares.size(); i++) {
        
//        float startEncode = ofGetElapsedTimef();
        
        vector<float> encoding = ccv.encode(foundSquares[i].img, ccv.numLayers()-1);
        
//        cout << "took " << ofGetElapsedTimef() - startEncode << " to encode" << endl;
        
//        float startPredict = ofGetElapsedTimef();
        
        VectorFloat inputVector(encoding.size());
        for (int i=0; i<encoding.size(); i++) inputVector[i] = encoding[i];
        if (pipeline.predict(inputVector)) {
            // gt classification
            int label = pipeline.getPredictedClassLabel();
            foundSquares[i].isPrediction = true;
            foundSquares[i].label = classNames[label];

            // send over OSC
            ofxOscMessage m;
            m.setAddress(oscAddress);
            m.addStringArg(foundSquares[i].label);
            sender.sendMessage(m, false);
            
            
        }
        
//        cout << "took " << ofGetElapsedTimef() - startPredict << " to predict" << endl;
    }
    

    
    
//    if(stayingSquares.size()==0 && foundSquares.size()>0){
//        stayingSquares = foundSquares;
//        //
//        for(FoundSquare& ss: stayingSquares){
//            ofPoint center( (ss.rect.x+ss.rect.width/2), (ss.rect.y+ss.rect.height/2));
//            ss.myMum.setup(center);
//        }
//    }
  //  else{
        //update stayingSquares
    
//    float startSquares = ofGetElapsedTimef();
    
        //keep staing squrare
        for(FoundSquare& ss: stayingSquares){
            for(FoundSquare& fs: foundSquares){
                if(fs.checked || ss.checked)
                    continue;
                
                ofPoint pfs(fs.rect.x,fs.rect.y);
                ofPoint pss(ss.rect.x,ss.rect.y);
                if(pfs.distance(pss)<30) //30 is adjustable
                {
                    //take it as same point
                    ss = fs;
                    ss.checked = true;
                    fs.checked = true;
                }
            }
        }
        
        //removing invalid squres
        for(int i=0;i<stayingSquares.size();i++){
            if(!stayingSquares[i].checked){
                for(Mum& mum: mums){
                    if(mum.myfs == &stayingSquares[i]){
                        mum.myfs = nullptr;
                        mum.explode();
                    }
                }
                for(Lotus& lotus: lotuses){
                    if(lotus.myfs == &stayingSquares[i]){
                        lotus.explode();
                        lotus.myfs = nullptr;
                    }
                }
                for(Prunus& prunus: prunuses){
                    if(prunus.myfs == &stayingSquares[i]){
                        prunus.explode();
                        prunus.myfs = nullptr;
                    }
                }


                stayingSquares.erase(stayingSquares.begin()+i);
            }
        }
        
        //add new squres
        for(int i=0;i<foundSquares.size();i++){
            if(!foundSquares[i].checked){
                //assgin flower
        
            
                stayingSquares.push_back(foundSquares[i]);
            if(foundSquares[i].label == "cross"){
                Mum mum;
                mum.setup(&stayingSquares[i]);
                mums.push_back(mum);
            }
            else if(foundSquares[i].label == "circle"){
                Lotus lotus;
                lotus.setup( &stayingSquares[i] );
                lotuses.push_back(lotus);
//                Prunus prunus;
//                prunus.setup(&stayingSquares[i], 40);
//                prunuses.push_back(prunus);
            }
            else if(foundSquares[i].label == "line"){
                    Prunus prunus;
                    prunus.setup(&stayingSquares[i], 40);
                    prunuses.push_back(prunus);
            }
                
                //foundSquares[i].checked = true;
                
            }


        }
        
        //reset flag
        for(FoundSquare& ss: stayingSquares){
            ss.checked = false;
        }
        
        //cout<<stayingSquares.size()<<endl;
    //}
    
//    cout << "took " << ofGetElapsedTimef() - startSquares << " to track squares" << endl;
    
}

//--------------------------------------------------------------
void ofApp::setTrainingLabel(int & label_) {
    trainingLabel.setName(classNames[label_]);
}

//--------------------------------------------------------------
void ofApp::save() {
    pipeline.save(ofToDataPath("doodleclassifier_model.grt"));
}

//--------------------------------------------------------------
void ofApp::load() {
    pipeline.load(ofToDataPath("doodleclassifier_model.grt"));
    isTrained = true;
}

//--------------------------------------------------------------
void ofApp::classifyNext() {
    toClassify = true;
}

//--------------------------------------------------------------
void ofApp::addSamplesToTrainingSetNext() {
    toAddSamples = true;
}


//-------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_TAB)
        showGui = !showGui;
    if(key == OF_KEY_RETURN){
        fullscreen = !fullscreen;
        ofSetFullscreen(fullscreen);
    }
    if(key == ' ')
        showCam = !showCam;
    if(key == 'r'){
        mums.clear();;
        lotuses.clear();
        prunuses.clear();
        stayingSquares.clear();

    }
    


}
void ofApp::windowResized(int w, int h){
    float x = ofGetWidth();
    param.WIDTH = x;
    float y = ofGetHeight();
    param.HEIGHT = y;
}
