#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	soundTrack.load("sounds/spy_short.mp3");
	soundTrack.play();
	white.load("images/7.jpg");
	for(int i=0; i < 6;i++){
		fileName = "images/" + to_string(i) + ".jpg";
		img.load(fileName);
		images.push_back(img);
	}

	textsReferenceTemps.loadFont("arial.ttf", 32);
	textsReferenceBands.loadFont("arial.ttf",8);

	// the fft needs to be smoothed out, so we create an array of floats
	// for that purpose:
	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}
	
	nBandsToGet = 3;

}

//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(0);
	// grab the fft, and put in into a "smoothed" array,
	// by taking maximums, as peaks and then smoothing downward
	float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
	for (int i = 0;i < nBandsToGet; i++){
		
		// let the smoothed value sink to zero:
		fftSmoothed[i] *= 0.10f;
		
		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
		
	}


}

//--------------------------------------------------------------
void ofApp::draw(){	
	string pos;

	ofSetColor(255);

	float alpha = ofRandom(-1, 1);
	
	// référence: Premier changement: 21.5%
	if(soundTrack.getPosition() >= 0.219 && soundTrack.getPosition() < 0.469){
		textsReferenceTemps.drawString("OK", 100, 200);
		if(iterator>=6)iterator=1;
		images[iterator++].draw(0, 0);
	}
	// référence: Premier changement: 21.5%
	if(soundTrack.getPosition() >= 0.469){
		textsReferenceTemps.drawString("OK2", 100, 200);

	}		

	// référence: à retirer: on veut pas que ça fasse "arts numérique"
	// pos = to_string(soundTrack.getPosition()*100) + "%";
	// textsReferenceTemps.drawString(pos, 100,100);

	ofSetColor(255);
	float width = (float)(5*128) / nBandsToGet;

	ofDrawCircle((ofGetWidth()/2) + fftSmoothed[0]*100*alpha, (ofGetHeight()/2) + fftSmoothed[1]*100*alpha, 1+fftSmoothed[2]*10);
	if(fftSmoothed[0] > 0.2){
		ofDrawLine(ofGetWidth()/2, 0, (ofGetWidth()/2) + fftSmoothed[0]*100*alpha, (ofGetHeight()/2) + fftSmoothed[1]*100*alpha);
	}

	textsReferenceBands.drawString(to_string(fftSmoothed[1]), 100, 300);


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
