#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"


using namespace ofxCv;
using namespace cv;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
    
    void initPointsToTrack(cv::Size subPixWinSize, TermCriteria termcrit);
    void trackKeyPoints(cv::Size winSize);
    
    void getDirections();
    Point2f getAverageDirection();
    
    ofVideoGrabber myVideoGrabber;
    ofImage imgCam;
    Mat matCam;
    Mat matCamGrey;
    Mat matCamPreGrey;

	Mat matMask;
    
    Mat gray;
    Mat prevGray;
    vector<Point2f> prePoints;
    vector<Point2f> curPoints;
    
    vector<Point2f> directions;
    
    cv::Point2f point;
    bool addRemovePt = false;
    
    int MAX_COUNT = 500;
    bool needToInit = false;
    
	CascadeClassifier face_cascade; //the instance of face detector
	std::vector<cv::Rect> faces; // a vector to store the detected faces

	bool testing = false;

	String status;
};
