#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(24);
	// Loading images.
	ofImage img;
	for(int i=1; i <= 66;i++){
		img.load("images/1stgroup-" + to_string(i) + ".JPG");
		images.push_back(img);
	}
	for(int i=1; i <= 61;i++){
		img.load("images/1stgroup-" + to_string(i) + ".JPG");
		images2.push_back(img);
	}
	colorImg.allocate(1080,720);
    grayImage.allocate(1080,720);
    grayBg.allocate(1080,720);
    grayDiff.allocate(1080,720);
	grayBg = images[65].getPixels();



    bLearnBakground = true;
    threshold = 10;

	// Loading soundtrack
	soundTrack.load("sounds/spy_short.mp3");
	soundTrack.play();

	// *****************************************************************
	// the fft needs to be smoothed out, so we create an array of floats
	// for that purpose:
	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}	
	nBandsToGet = 3;
	// ***************************************************************//

}

//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(0);
	// vid.update();


	if(soundTrack.getPosition() >= 0.219 && soundTrack.getPosition() < 0.3){loopPictureSet(images, 1);}

	if(soundTrack.getPosition() >= 0.301 && soundTrack.getPosition() < 0.469){loopPictureSet(images, 1);}

	// grab the fft, and put in into a "smoothed" array,
	// by taking maximums, as peaks and then smoothing downward
	float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
	for (int i = 0;i < nBandsToGet; i++){
		
		// let the smoothed value sink to zero:
		fftSmoothed[i] *= 0.01f;
		
		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
		
	}
	if(timer--<=0)timer=2;

	
	

}

//--------------------------------------------------------------
void ofApp::draw(){	
	string pos;

	ofSetColor(255);

	float alpha = ofRandom(-1, 1);

	// référence: Premier changement: 21.5%
	if(soundTrack.getPosition() >= 0.219 && soundTrack.getPosition() < 0.3){loopPictureSet(images, 2);}
	if(soundTrack.getPosition() >= 0.301 && soundTrack.getPosition() < 0.469){loopPictureSet(images, 2);}
	if(soundTrack.getPosition() >= 0.469){}		

	ofSetColor(255);
	float width = (float)(5*128) / nBandsToGet;

	ofDrawCircle((ofGetWidth()/2) + fftSmoothed[0]*100*alpha, (ofGetHeight()/2) + fftSmoothed[1]*100*alpha, 1+fftSmoothed[2]*10);
	if(fftSmoothed[0] > 0.25){
		images[ofRandom(60,65)].draw(0,0);
		ofDrawLine(ofGetWidth()/2, 0, (ofGetWidth()/2) + fftSmoothed[0]*100*alpha, (ofGetHeight()/2) + fftSmoothed[1]*100*alpha);
	}

}
//--------------------------------------------------------------
// Loop fonctions
// in: vector<ofImage>: set to loop
// in: action (1: update, 2: draw)
void ofApp::loopPictureSet(vector<ofImage> &imgSet, int action){
	switch(action) {
		case 1:
			currRdmFrame = ofRandom(floor(0),floor(65));

			colorImg.setFromPixels(imgSet[currRdmFrame].getPixels());

			grayImage = colorImg;

		    // take the abs value of the difference between background and incoming and then threshold:
		    grayDiff.absDiff(grayBg, grayImage);
		    grayDiff.threshold(threshold);


			// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
			// also, find holes is set to true so we will get interior contours as well....
			contourFinder.findContours(grayDiff, 20, (1080*720)/3, 10, true);	// find holes

			break;
		case 2:
			images[currRdmFrame].draw(0, 0);
			ofSetColor(255);
			for(int j=0;j<contourFinder.nBlobs;j++){
				float tempsX = contourFinder.blobs[j].boundingRect.getCenter().x;
				float tempsY = contourFinder.blobs[j].boundingRect.getCenter().y;
				
				if(tempsY<=500){
					ofDrawCircle(tempsX, tempsY, ofRandom(1,3));
					ofSetColor(ofRandom(0, 255));
					ofDrawLine(ofGetWidth()/8, 0, tempsX, tempsY);
					
				}
			}
			contourFinder.draw();
			break;
		}

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
