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

	//do Canny here
	Canny(mat, edgeResult, lowThreshold, lowThreshold * 2);

	//Current column
	startCol = 0;
	endCol = 0;
	for (int curCol = 0; curCol < edgeResult.cols && foundTarget == false; curCol++) {
		for (int y = 0; y < edgeResult.rows; y++) {
			if ((int)edgeResult.at<uchar>(y, curCol) == 255) {
				foundFirst = true;
				startCol = curCol;
				foundTarget = true;
				break;
			}
		}
	}

	for (int curCol = startCol; curCol < edgeResult.cols; curCol++) {
		for (int y = 0; y < edgeResult.rows; y++) {
			if ((int)edgeResult.at<uchar>(y, curCol) == 255) {
				endCol = curCol;
				foundWhite = true;
				break;
			}
		}

		if (foundWhite == false) {
			break;
		}
	}

	currentCol = startCol;

	cout << "S col: " << startCol << " E col: " << endCol << endl;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (currentCol == endCol) { orientation = true; }
	if (currentCol == startCol) { orientation = false; }

	if (orientation == false){
		if (currentCol < endCol) {
			currentCol++;
		}
	} else {
		if (currentCol > startCol) {
			currentCol--;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(255, 255, 255);
	im.draw(0, 0);
	drawMat(edgeResult, im.getWidth(), 0);

	for (int y = 0; y < edgeResult.rows; y++) {
		if ((int)edgeResult.at<uchar>(y, currentCol) == 255) {
			ofSetColor(255, 255, 255);
			ofDrawCircle(currentCol, y, 8);
			break;
		}
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