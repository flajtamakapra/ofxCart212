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
		img.load("images/2ndgroup-" + to_string(i) + ".JPG");
		images2.push_back(img);
	}
	for(int i=1; i <= 8;i++){
		img.load("images/silouhette-" + to_string(i) + ".JPG");
		silouhettes.push_back(img);
	}
	for(int i=1; i <= 9;i++){
		img.load("images/squareandlegs-" + to_string(i) + ".JPG");
		squareLegs.push_back(img);
	}
	
	
	flashImg.load("images/2ndgroup-61.JPG");
	redLight.load("images/redlight-1.JPG");
	intro1.load("images/intro-1.JPG");
	intro2.load("images/intro-2.JPG");


	colorImg.allocate(1080,720);
    grayImage.allocate(1080,720);
    grayBg.allocate(1080,720);
    grayDiff.allocate(1080,720);
	grayBg = images[65].getPixels();



    bLearnBakground = true;
    threshold = 10;
    it=0;

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
	nBandsToGet = 120;
	// ***************************************************************//



}


//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(0);
	// vid.update();


	if(soundTrack.getPosition() >= 0.219 && soundTrack.getPosition() < 0.4){loopPictureSet(images, 1);}

	if(soundTrack.getPosition() >= 0.4 && soundTrack.getPosition() < 0.469){loopPictureSet(images2, 1);}

	// grab the fft, and put in into a "smoothed" array,
	// by taking maximums, as peaks and then smoothing downward
	float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
	
	for (int i = 0;i < nBandsToGet; i++){
		
		// let the smoothed value sink to zero:
		fftSmoothed[i] *= 0.45f;
		
		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
		
	}
	if(timer--<=0)timer=2;
	
	

}

//--------------------------------------------------------------
void ofApp::draw(){	
	string pos;
	int x1, x2, y1, y2;
	x1 = x2 = ofMap(ofGetElapsedTimef(), 0, 55, 0, 200, true);
	y1 = 100;
	y2 = (-y1);

	float alpha = ofRandom(-5, 5);

	// Premier tier
	if(soundTrack.getPosition() < 0.219){
		int genAlpha = ofRandom(0, 50)+randomFromSound(0,20);
		ofDrawLine(x1,y1,x2,y2);
		ofSetColor(255,255,200,genAlpha);
		intro2.draw(0,0);
	}


	// Deuxième tier
	if(soundTrack.getPosition() >= 0.219 && soundTrack.getPosition() < 0.42){
		int genAlpha = randomFromSound(0,200);
		ofSetColor(255,255,255,genAlpha);
		loopPictureSet(squareLegs,2);
	}
	if(soundTrack.getPosition() >= 0.4 && soundTrack.getPosition() < 0.469){
		int genAlpha = randomFromSound(0,200);
		ofSetColor(255,255,255,genAlpha);
		if(++iterator%2==0)loopPictureSet(images2, 2);
		else loopPictureSet(images,2);
	}


	// troisieme tier
	if(soundTrack.getPosition() >= 0.469){
		int genAlpha = ofRandom(0, 50)+randomFromSound(0,20);
		ofDrawLine(x1,y1,x2,y2);
		ofSetColor(255,255,200,genAlpha);
		intro2.draw(0,0);

	}		

	// pré-conclusion
	if(soundTrack.getPosition() >= 0.635){
		int genAlpha = randomFromSound(0,255);
		ofSetColor(255,255,255,genAlpha);
		if(it>=images.size())
			{
				loopPictureSet(images,2);
				loopPictureSet(images,1);
				flashPictures(flashImg);
			}

		else 
			{
				images[it].draw(0,0);
				loopPictureSet(images, 1);
			}
		if(!timer)it++;

	}		

	// Tout
	for(int i=0;i<=nBandsToGet;i+=3){
		int clr = fftSmoothed[i]*100000;
		ofSetColor(255,255,255,clr);
		ofDrawCircle(randomFromSound(0, ofGetWidth()) + fftSmoothed[i+0]*10000+alpha + ofRandom(0,100), ofGetHeight()/2 + fftSmoothed[i+1]*10000*alpha, 1+fftSmoothed[i+2]*30);
		if(fftSmoothed[i] > 0.20 && soundTrack.getPosition() < 0.469){
			int genAlpha = randomFromSound(0, 30);
			ofSetColor(255,255,255,genAlpha);
			squareLegs[randomFromSound(0,7)].draw(0,0);

		}
		if(fftSmoothed[i] > 0.55) {
			int genAlpha = randomFromSound(0,200);
			redLight.draw(0,0);
		}
	}

}
//--------------------------------------------------------------
// Loop fonctions
// in: vector<ofImage>: set to loop
// in: action (1: update, 2: draw)
void ofApp::loopPictureSet(vector<ofImage> &imgSet, int action){
	currRdmFrame = ofRandom(floor(0),floor(imgSet.size()));
	switch(action) {
		case 1:

			colorImg.setFromPixels(imgSet[currRdmFrame].getPixels());

			grayImage = colorImg;

		    // take the abs value of the difference between background and incoming and then threshold:
		    grayDiff.absDiff(grayBg, grayImage);
		    grayDiff.threshold(threshold);


			// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
			// also, find holes is set to true so we will get interior contours as well....
			contourFinder.findContours(grayDiff, 200, 50000, 10, true);	// find holes

			break;
		case 2:
			imgSet[currRdmFrame].draw(0, 0);
			ofSetColor(255);
			for(int j=0;j<contourFinder.nBlobs;j++){
				float tempsX = contourFinder.blobs[j].boundingRect.getCenter().x;
				float tempsY = contourFinder.blobs[j].boundingRect.getCenter().y;
				
				if(tempsY<=500){
					ofDrawCircle(tempsX, tempsY, ofRandom(1,3));
					ofSetColor(randomFromSound(0, 255));
					ofDrawLine(ofGetWidth()/2, 0, tempsX, tempsY);
					
				}
			}
			//contourFinder.draw();
			break;
		}

}
//--------------------------------------------------------------
void ofApp::flashPictures(ofImage flshImg){
	int genAlpha = randomFromSound(100,255);
	if((int)ofRandom(0,100)%2==0){
		ofSetColor(255,255,255,genAlpha);		
		flshImg.draw(0,0);
	}
}

//--------------------------------------------------------------
// So it's all about the sound
int ofApp::randomFromSound(int min, int max){
	float total=0;
	for(int i=0;i<nBandsToGet;i++){
		if(total<fftSmoothed[i])
		{
			total=fftSmoothed[i];
		}
	}
	return ofMap(total,0,0.80000001,min,max,true);
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
