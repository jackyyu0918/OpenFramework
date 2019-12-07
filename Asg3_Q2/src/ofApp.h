#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

using namespace cv;
using namespace ofxCv;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		bool isGreen(Mat mat, int x, int y);
		Mat combineMat(Mat backMat, Mat frontMat);

		ofVideoGrabber vidGrabber;
		ofImage im;
		Mat mat;

		Mat mat_HSV;

		Mat mat_HSV_Threshold;

		ofxPanel gui;
		ofxIntSlider minH;
		ofxIntSlider maxH;
		ofxIntSlider minS;
		ofxIntSlider maxS;
		ofxIntSlider minV;
		ofxIntSlider maxV;

		Mat result;

		ofxCvContourFinder contourFinder;

		//Drawing mode
		ofImage drawImg;
		Mat topMat;
		Mat finalMat;

		bool drawMode = false;
		
		int pen_centreX;
		int pen_centreY;
};