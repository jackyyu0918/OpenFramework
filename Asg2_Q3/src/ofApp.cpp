#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    gui.add(lowThreshold.setup("low threshold", 89, 0, 100));
    im.load("testing3.jpg");
    im.setImageType(OF_IMAGE_COLOR);
    mat = toCv(im);
	dupMat = toCv(im);
    cvtColor(mat, mat, CV_BGR2GRAY);//only if you load a RGB image
    GaussianBlur(mat, mat, 3);

	//Current column
	currentCol = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(255, 255, 255);
	Canny(mat, edgeResult, lowThreshold, lowThreshold * 2);
	im.draw(0, 0);
	drawMat(edgeResult, im.getWidth(), 0);

	for (int y = 0; y < edgeResult.rows; y++) {
		if ((int)edgeResult.at<uchar>(y, currentCol) == 255) {
			cout << "Hello: " << y << " " << currentCol << endl;
			ofSetColor(255, 255, 255);
			ofDrawCircle(currentCol, y, 5);
			break;
		}
	}

	if (currentCol < edgeResult.cols-1) {
		currentCol++;
	}

    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (button == 0) {
		cout << "Pressed: " << "x: " << x  << " y: " << y << endl;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

bool ofApp::foundLine(Mat mat, int x, int y) {
	return mat.at<uchar>(x, y) == 255 ? true : false;
}