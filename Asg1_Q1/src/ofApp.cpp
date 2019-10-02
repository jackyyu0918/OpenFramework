#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	imgMan.load("running.jpg");
	imgBg.load("bg.jpg");

	matMan = toCv(imgMan);
	matBg = toCv(imgBg);

	for (int x = 0; x < matMan.cols; x++) {
		for (int y = 0; y < matMan.rows; y++) {
			if (isGreen(matMan, x, y)) {
				matMan.data[(x + y * matMan.cols) * 3] = matBg.data[(x + y * matMan.cols) * 3];
				matMan.data[(x + y * matMan.cols) * 3 + 1] = matBg.data[(x + y * matMan.cols) * 3 + 1];
				matMan.data[(x + y * matMan.cols) * 3 + 2] = matBg.data[(x + y * matMan.cols) * 3 + 2];
				//cout << "y: " << y << " x: " << x << " Green!" << endl;
			}

			//else cout << "y: " << y << " x: " << x << " Not Green!" << endl;
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	imgMan.draw(0, 0);
	drawMat(matMan, 0, imgMan.getHeight());
}

bool ofApp::isGreen(Mat mat, int x, int y) {
	if (((int(mat.data[(x + y * mat.cols) * 3]) == 57) && (int(mat.data[(x + y * mat.cols) * 3 + 2])) == 46) || (int(mat.data[(x + y * mat.cols) * 3 + 1])) > 228) {
		return true;
	}

	else return false;
}

void ofApp::mousePressed(int x, int y, int button) {
	if(button == 0) {
		cout << int(matMan.data[(x + y * matMan.cols) * 3]) << " " <<  (int(matMan.data[(x + y * matMan.cols) * 3 + 1])) << " " << (int(matMan.data[(x + y * matMan.cols) * 3 + 2])) << endl;
	}
}