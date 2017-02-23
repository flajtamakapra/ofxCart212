#pragma once

#include "ofMain.h"
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
		

		vector<ofImage> images;
		ofImage img;
		ofImage white;
		int iterator = 0;
		string fileName;

		// Texts
		ofTrueTypeFont textsReferenceTemps;
		ofTrueTypeFont textsReferenceBands;

		// Sound utilities
		ofSoundPlayer soundTrack;
		float * fftSmoothed;
		int nBandsToGet;

		int timer = 10;

};

