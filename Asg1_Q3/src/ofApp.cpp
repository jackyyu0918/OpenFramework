#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    myVideoGrabber.initGrabber(320, 240);
}

//--------------------------------------------------------------
void ofApp::update(){
    // Ask the grabber to refresh its data.
    
	int histSize = 256;
	float range[] = { 0, 256 }; //the upper boundary is exclusive
	const float* histRange = { range };

    myVideoGrabber.update();
    
    // If the grabber indeed has fresh data,
    if (myVideoGrabber.isFrameNew()) {
        
        // Obtain a pointer to the grabber's image data.
        imgCam.setFromPixels(myVideoGrabber.getPixels());
        matCam = toCv(imgCam);

		cout << "storePixel: " << storePixel << endl;

		cvtColor(matCam, matCam, CV_BGR2GRAY);

		if (storePixel != -1) {
			for (int y = 0; y < matCam.rows; y++) {
				for (int x = 0; x < matCam.cols; x++) {
					if (int(matCam.at<uchar>(y, x)) == storePixel) {
						matCam.at<uchar>(y, x) = uchar(255 - storePixel);
					}
				}
			}
		}

		calcHist(&matCam, 1, 0, Mat(), hist, 1, &histSize, &histRange);
		normalize(hist, hist, 0, 400, NORM_MINMAX);

		for (int i = 0; i < histSize; i++) {
			histCols[i].clear();
			histCols[i].addVertex(i + 10, 768);
			histCols[i].addVertex(i + 10, 768 - cvRound(hist.at<float>(i)));
		}
		//////////////////////////////////////////////////
}
    }

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 255, 255);
    ofSetColor(255);
    drawMat(matCam, 0, 0);
	ofSetColor(0, 0, 0);

	for (int i = 0; i < 256; i++) {
		histCols[i].draw();
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
	if (button == 0) {
		cout << "X: " << x << " Y: " << y << " Intensity: " << int(matCam.at<uchar>(y, x)) << endl;
		storePixel = int(matCam.at<uchar>(y, x));
		matCam.at<uchar>(y, x) = uchar(255);
	}
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
