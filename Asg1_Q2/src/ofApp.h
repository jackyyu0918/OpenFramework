#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

using namespace ofxCv;
using namespace cv;

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void mousePressed(int x, int y, int button);

	ofImage imgLena;
	Mat matLena;
	Mat matNewLena;

	ofImage imgCircuit;
	Mat matCircuit;
	Mat matNewCircuit;
};
