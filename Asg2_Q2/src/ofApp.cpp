#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	gui.setup();
	gui.add(lowThreshold.setup("low threshold", 50, 0, 100));
	im.load("cap.jpg");


}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(255);
	ofSetColor(255, 255, 255);
	im.draw(0, 0);

	mat = toCv(im);
	cvtColor(mat, mat, CV_BGR2GRAY);
	GaussianBlur(mat, mat, 3);
	Canny(mat, mat, lowThreshold, lowThreshold * 2);
	drawMat(mat, im.getWidth(), 0);
	vector<Vec3f> circles;
	HoughCircles(mat, circles, CV_HOUGH_GRADIENT, 2, 50, lowThreshold * 2, 100, 30, 50);
	for (int i = 0; i < circles.size(); i++) {
		ofSetColor(255, 0, 0);
		ofNoFill();
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
