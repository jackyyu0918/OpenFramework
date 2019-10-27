#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	myVideoGrabber.initGrabber(320, 240);
    gui.setup();
    gui.add(lowThreshold.setup("low threshold", 50, 0, 100));
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
	// Ask the grabber to refresh its data.
	myVideoGrabber.update();

	// If the grabber indeed has fresh data,
	if (myVideoGrabber.isFrameNew()) {

		// Obtain a pointer to the grabber's image data.
		imgCam.setFromPixels(myVideoGrabber.getPixels());
		matRealCam = toCv(imgCam);
		matCam = toCv(imgCam);
		cvtColor(matCam, matCam, CV_BGR2GRAY);

		GaussianBlur(matCam, matCam, 3);
		Canny(matCam, matCam, lowThreshold, lowThreshold * 2);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofSetColor(255, 255, 255);
	drawMat(matRealCam,0,0);
    
    vector<Vec3f> circles;
    HoughCircles(matCam, circles, CV_HOUGH_GRADIENT, 2, 50, lowThreshold*2, 100, 30, 50);
    for(int i = 0; i < circles.size(); i++){
        ofSetColor(255, 0, 0);
        ofNoFill();
        ofDrawCircle(circles[i][0], circles[i][1], circles[i][2]);
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
