#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

using namespace ofxCv;
using namespace cv;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y)
		void gotMessage(ofMessage msg);;
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
    
    ofVideoGrabber myVideoGrabber;
    ofImage imgCam;
    Mat matCam;
	int storePixel = -1;

	Mat hist;

	Mat histImage;

	ofPolyline histogram;

	ofPolyline histCols[256];
    
    
};
