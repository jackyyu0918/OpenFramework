#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	imgMan.load("running.jpg");
	imgBg.load("bg.jpg");
	imgMan.setImageType(OF_IMAGE_COLOR);
	imgBg.setImageType(OF_IMAGE_COLOR);

	matMan = toCv(imgMan);
	matBg = toCv(imgBg);

	split(matMan, rgb);

	for (int i = 0; i < matMan.rows; i++) {
		for (int j = 0; j < matMan.cols; j++) {
			cout << "rgb[0].data["<<  i << "]: " << rgb[0].data[i] << endl;
		}
	}


	/*for (int i = 0; i < matMan.rows * matMan.cols; i++) {
		if (matMan.data[i * 3] > 0 &&
			matMan.data[i * 3 + 1] > 0 &&
			matMan.data[i * 3 + 2] > 0) {
			matMan.data[i * 3] = 255 - matMan.data[i * 3];
			matMan.data[i * 3 + 1] = 255 - matMan.data[i * 3 + 1];
			matMan.data[i * 3 + 2] = 255 - matMan.data[i * 3 + 2];
		}
	}*/

	//matMan = isGreen(matMan);

	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	/*drawMat(rgb[0], 0, 0); //red channels
	drawMat(rgb[1], imgMan.getWidth(), 0); //green channels
	drawMat(rgb[2],0, imgMan.getHeight()); //blue channels*/
	drawMat(matMan, imgMan.getWidth(), imgMan.getHeight());
}

Mat ofApp::isGreen(Mat mat) {
	for(int i = 0; i < mat.rows * mat.cols; i++) {
		if(mat.data[i * 3] > 0 && mat.data[i * 3 + 1] > 0 && mat.data[i * 3 + 2] > 0){
			mat.data[i * 3] = 255 - mat.data[i * 3];
			mat.data[i * 3 + 1] = 255 - mat.data[i * 3 + 1];
		mat.data[i * 3 + 2] = 255 - mat.data[i * 3 + 2];
		}
	}
	return mat;
}

void ofApp::printPixel(Mat mat) {
	for (int i = 0; i < mat.rows; i++) {
		for (int j = 0; j < mat.cols; j++) {
			cout << "i: " << i << " j: " << j << " value: " << mat.at<char>(i, j) << endl;
		}
	}
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

Mat ofApp::Add(Mat m1, Mat m2) {
	return m1 + m2;
}

Mat ofApp::Subtract(Mat m1, Mat m2) {
	return m1 - m2;
}

Mat ofApp::Multiply(Mat m1, Mat m2) {
	m1.convertTo(m1, CV_32FC1);
	m2.convertTo(m1, CV_32FC1);

	Mat m3 = m1 * m2;

	m3.convertTo(m3, CV_8UC1);

	return m3;
}

Mat ofApp::Divide(Mat m1, Mat m2) {
	m1.convertTo(m1, CV_32FC1);
	m2.convertTo(m1, CV_32FC1);

	Mat m3 = m1 / m2;

	m3.convertTo(m3, CV_8UC1);

	return m3;
}


