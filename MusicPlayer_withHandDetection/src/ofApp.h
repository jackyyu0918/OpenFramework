#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"

using namespace ofxCv;
using namespace cv;

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void playNextSong();
	void playPreviousSong();
	void clearDirections();
	void autoTrack();
	void initPointsToTrack(cv::Size subPixWinSize, TermCriteria termcrit);
	void trackKeyPoints(cv::Size winSize);
	void getDirections();
	Point2f getAverageDirection();

	ofVideoGrabber myVideoGrabber;
	ofImage imgCam;
	Mat matCam;

	Mat matCamGrey;
	Mat matCamPreGrey;

	Mat mask;

	vector<Point2f> prePoints;
	vector<Point2f> curPoints;

	vector<ofPolyline> tracks;

	vector<Point2f> directions;

	Point2f point;
	bool addRemovePt = false;

	int MAX_COUNT = 500;
	bool needToInit = false;

	int threshold_counting;

	CascadeClassifier leftHand_cascade; //the instance of face detector
	CascadeClassifier eye_cascade; //the instance of eye detector
	std::vector<cv::Rect> leftHands; // a vector to store the detected faces
	std::vector<cv::Rect> eyes; // a vector to store the detected eyes, for solving false-positive

	String status;

	ofSoundPlayer musicPlayer;
	vector<string> musicPathList;
	int currentMusicNumber = -1;

	bool isLeftHandDetected = false;
	bool selectionDone = false;
	
	Point2f prevAverageDir;
	int directions_threshold;
	int threshold_count;

	string currentMode = "Song selection mode: swap left/right";

	//volume mode
	Mat mat_HSV;

	Mat mat_HSV_Threshold;

	ofxPanel gui;
	ofxIntSlider minH;
	ofxIntSlider maxH;
	ofxIntSlider minS;
	ofxIntSlider maxS;
	ofxIntSlider minV;
	ofxIntSlider maxV;

	ofxCvContourFinder contourFinder;

	int pen_centreX;
	int pen_centreY;

	float volumeResult;
};
