#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //need to use absolute path here, for the latest version of OpenFrameworks and its OpenCV addon
	if (!vid.load("faceDetection.mov")) {
		cout << "Can't load video";
	}
	else {
		vid.play();
	}
	
	if(!face_cascade.load("P:/Workspace/OpenFramework/Asg3_Q1/bin/data/haarcascade_frontalface_default.xml")){
        cout<<"Error loading face xml"<<endl;
    }
	else {
		cout << "Successfully loaded face_cascade" << endl;
	}

	if (!eye_cascade.load("P:/Workspace/OpenFramework/Asg3_Q1/bin/data/haarcascade_eye.xml")) {
		cout << "Error loading eye xml" << endl;
	}
	else {
		cout << "Successfully loaded eye_cascade" << endl;
	}

	
}

//--------------------------------------------------------------
void ofApp::update(){
	vid.update();
	vid.getCurrentFrame();

	// If the grabber indeed has fresh data,
	if (vid.isFrameNew()) {

		ofPixels pixs = vid.getPixels();
		vidImg.setFromPixels(pixs);
		vidMat = toCv(vidImg);

		// size is for minimum size
		face_cascade.detectMultiScale(vidMat, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
		}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 255, 255);
	//Original Image at the background
    drawMat(vidMat, 0, 0);

	//Draw rectangle for detected face
	for (int i = 0; i < faces.size(); i++) {

		//In each detected face, detect eyes
		eye_cascade.detectMultiScale(vidMat, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
		for (int j = 0; j < eyes.size(); j++) {
			//Only draw outline of shape
			ofNoFill();

			//draw face rectangle with eyes checking (x,y , width, height)
			//There must be eyes inside face area
			if ((faces.at(i).x < eyes.at(j).x) &&
				((faces.at(i).x + faces.at(i).width) > eyes.at(j).x) &&
				(faces.at(i).y < eyes.at(j).y) &&
				((faces.at(i).y + faces.at(i).height) > eyes.at(j).y)) {

				//rectangle
				ofDrawRectangle(faces.at(i).x, faces.at(i).y, faces.at(i).width, faces.at(i).height);
			}
		}
	}
}
