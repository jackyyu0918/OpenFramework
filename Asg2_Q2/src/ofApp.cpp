#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	gui.setup();
	gui.add(lowThreshold.setup("low threshold", 50, 0, 100));
	myVideoGrabber.initGrabber(320, 240);


}

//--------------------------------------------------------------
void ofApp::update() {
	// Ask the grabber to refresh its data.
	myVideoGrabber.update();

	// If the grabber indeed has fresh data,
	if (myVideoGrabber.isFrameNew()) {

		// Obtain a pointer to the grabber's image data.
		imgCam.setFromPixels(myVideoGrabber.getPixels());
		matCam = toCv(imgCam);
		matRealCam = toCv(imgCam);
		cvtColor(matCam, matCam, CV_BGR2GRAY);
		GaussianBlur(matCam, matCam, 3);
		Canny(matCam, matCam, lowThreshold, lowThreshold * 2);
		//HoughCircles(matCam, circles, CV_HOUGH_GRADIENT, 2, 50, lowThreshold * 2, 100, 30, 50);
		HoughCircles(matCam, circles, CV_HOUGH_GRADIENT, 2, 50, lowThreshold * 2, 100, 30, 50);
	}

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(255, 255, 255);
	ofSetColor(255);
	drawMat(matRealCam, 0, 0);
	drawMat(matCam, imgCam.getWidth(), 0);
	for (int i = 0; i < circles.size(); i++) {
		ofSetColor(255, 255, 255);
		ofDrawCircle(circles[i][0], circles[i][1], circles[i][2]);
	}

	for (int i = 0; i < circles.size()/2; i++) {
		ofSetColor(0, 50, 0);
		ofDrawCircle(circles[i][0], circles[i][1], circles[i][2]);
	}
	gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
