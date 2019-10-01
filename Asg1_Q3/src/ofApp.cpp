#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	imgMan.load("running.jpg");
	matMan = toCv(imgMan);

	imgBg.load("bg.jpg");
	matBg = toCv(imgBg);

	split(matMan, rgb);

	for (int i = 0; i < matMan.cols; i++) {
		for (int j = 0; j < matMan.rows; j++) {
			cout << "int(matMan.at<Vec3b>(j, i)[0]): " << int(matMan.at<Vec3b>(j, i)[0]) << endl;
			cout << "int(matMan.at<Vec3b>(j, i)[1]): " << int(matMan.at<Vec3b>(j, i)[1]) << endl;
			cout << "int(matMan.at<Vec3b>(j, i)[2]): " << int(matMan.at<Vec3b>(j, i)[2]) << endl;

			if (int(matMan.at<Vec3b>(j, i)[0]) == 57 && int(matMan.at<Vec3b>(j, i)[1]) == 255 && int(matMan.at<Vec3b>(j, i)[2]) == 46) {
				matMan.at<Vec3b>(j, i)[0] = 0;

			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	drawMat(matMan, 0, 0);
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
