#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

using namespace cv;
using namespace ofxCv;


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void mousePressed(int x, int y, int button);

		//bool ofApp::isGreen(Mat channel);

		ofImage imgMan;
		ofImage imgBg;

		Mat matMan;
		Mat matBg;
		
		Mat RGB[3];

		Mat matNewImage;

		bool isGreen(Mat mat, int x, int y);
		
};
