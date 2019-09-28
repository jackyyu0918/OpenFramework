#pragma once

#include "ofMain.h"

#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "OfxGui.h"

using namespace cv;
using namespace ofxCv;

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		Mat Add(Mat m1, Mat m2);
		Mat Subtract(Mat m1, Mat m2);
		Mat Multiply(Mat m1, Mat m2);
		Mat Divide(Mat m1, Mat m2);

		Mat isGreen(Mat mat);
		void printPixel(Mat mat);
		
		ofImage imgMan;
		ofImage imgBg;

		Mat matMan;
		Mat matBg;
		Mat rgb[3];

};
