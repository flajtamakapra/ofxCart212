#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
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

		

		vector<ofImage> images;
		vector<ofImage> images2;
		vector<ofImage> images3;
		ofImage white;
		int iterator = 0;
		int currRdmFrame;

		// Texts
		ofTrueTypeFont textsReferenceTemps;
		ofTrueTypeFont textsReferenceBands;

		// Sound utilities
		ofSoundPlayer soundTrack;
		float * fftSmoothed;
		int nBandsToGet;

		// Video utilities
		ofVideoPlayer vid;

		int timer = 10;


		// openCV Bob detection
        ofxCvColorImage			colorImg;

        ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;

        ofxCvContourFinder 	contourFinder;

		int 				threshold;
		bool				bLearnBakground;

};

