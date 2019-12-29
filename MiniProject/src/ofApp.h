#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

#include <string>
#include <iostream>
#include <filesystem>

using namespace ofxCv;
using namespace cv;

class ofApp : public ofBaseApp {

public:
	void setup();
	void initPointsToTrack(cv::Size subPixWinSize, TermCriteria termcrit);
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

	ofVideoGrabber myVideoGrabber;
	ofImage imgCam;
	Mat matCam;

	CascadeClassifier right_hand_cascade; //the instance of hand detector
	std::vector<cv::Rect> rightHands; // a vector to store the detected hands

	CascadeClassifier left_hand_cascade; //the instance of hand detector
	std::vector<cv::Rect> leftHands; // a vector to store the detected hands

	ofSoundPlayer musicPlayer;
	vector<string> musicPathList;
	//vector<string> musicNameList;
	int currentMusicNumber = -1;

	//Music progress control
	//bool musicStart = false;
	bool musicSelecting = false;
	int leftHand_starting_x;

	//tracking point
	Mat matCamGrey;
	Mat matCamPreGrey;

	void initPointsToTrack(cv::Size subPixWinSize, TermCriteria termcrit);
	void trackKeyPoints(cv::Size winSize);
	void getDirections();
	Point2f getAverageDirection();

	//
	Mat mask;

	vector<Point2f> prePoints;
	vector<Point2f> curPoints;

	vector<ofPolyline> tracks;

	vector<Point2f> directions;

	Point2f point;
	Point2f prevAverageDir;
	bool addRemovePt = false;

	int MAX_COUNT = 500;
	bool needToInit = false;

	int directions_thresholdVal;
	int threshold_counting;
};
