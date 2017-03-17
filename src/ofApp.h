#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxVideoRecorder.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <cmath>

using namespace std;


class ofApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void loopPictureSet(vector<ofImage> &imgSet, int action);
		void flashPictures(ofImage img);
		int randomFromSound(int, int);
		

		vector<ofImage> images;
		vector<ofImage> images2;
		vector<ofImage> silouhettes;
		vector<ofImage> squareLegs;

		ofImage white, flashImg, redLight, intro1, intro2;
		int iterator = 0;
		int currRdmFrame, it;
		int down = 255;

		// Texts
		ofTrueTypeFont textsReferenceTemps;
		ofTrueTypeFont textsReferenceBands;

		// Sound utilities
		ofSoundPlayer soundTrack;
		float * fftSmoothed;
		int nBandsToGet;

		// Video utilities
		ofVideoPlayer vid;
		int alphaLines = 255;
		int timer = 10;


		// openCV Blob detection
        ofxCvColorImage			colorImg;

        ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;

        ofxCvContourFinder 	contourFinder;

		int 				threshold;
		bool				bLearnBakground;

};

