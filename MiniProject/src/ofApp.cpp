#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	myVideoGrabber.initGrabber(320, 240);
	matCam = Mat::zeros(cv::Size(1, 1), CV_8UC1);

	//Haar Cascade detection section
	if (!left_hand_cascade.load("P:/Workspace/OpenFramework/MiniProject/bin/data/lpalm.xml")) {
		cout << "Error loading left hand detector" << endl;
	}
	else {
		cout << "left hand xml loaded successfully." << endl;
	}

	if (!right_hand_cascade.load("P:/Workspace/OpenFramework/MiniProject/bin/data/rpalm.xml")) {
		cout << "Error loading" << endl;
	}
	else {
		cout << "right hand xml loaded successfully." << endl;
	}

	//Music player section
	string path = "P:/Workspace/OpenFramework/MiniProject/bin/data/song";
	
	for (const auto& entry : filesystem::directory_iterator::directory_iterator(path)) {
		cout << "Adding: " << entry.path().string() << endl;
		musicPathList.push_back(entry.path().string());
	}
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
		//cvtColor(matCam, matCam, CV_BGR2GRAY);
	}
	
	//Hand detection
	left_hand_cascade.detectMultiScale(matCam, rightHands, 1.1, 1, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(0, 0));
	//right_hand_cascade.detectMultiScale(matCam, rightHands, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(1, 1));

	/*
	//left hand is not existing
	if (leftHands.empty()) {
		if (musicSelecting == true) {
			musicSelecting = false;

			//next song
			if (leftHand_starting_x > leftHands[0].x + (leftHands[0].width / 2)) {
				currentMusicNumber++;
				musicPlayer.load(musicPathList[currentMusicNumber]);
				musicPlayer.setVolume(0.1);
				musicPlayer.play();
			}
			//previous song
			else {
				currentMusicNumber--;
				musicPlayer.load(musicPathList[currentMusicNumber]);
				musicPlayer.setVolume(0.1);
				musicPlayer.play();
			}

			
		}
	}

	//left hand is detected
	else {
		if (musicSelecting == false) {
			musicSelecting = true;

			//record the starting point of left hand
			leftHand_starting_x = leftHands[0].x + (leftHands[0].width / 2);
		}
	}
	*/
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(255, 255, 255);
	ofSetColor(255);
	drawMat(matCam, 0, 0);
	

	//Hand detection box drawing
	for (int i = 0; i < leftHands.size(); i++) {
		ofNoFill();
		ofDrawRectangle(leftHands.at(i).x, leftHands.at(i).y, leftHands.at(i).width, leftHands.at(i).height);
	}

	for (int i = 0; i < rightHands.size(); i++) {
		ofNoFill();
		ofDrawRectangle(rightHands.at(i).x, rightHands.at(i).y, rightHands.at(i).width, rightHands.at(i).height);
	}
	
	//Music message section
	ofDrawBitmapString("Current music: ", 0, 20);
	if (currentMusicNumber == -1) {
		ofDrawBitmapString("No music is playing now" , 0, 40);
	}
	else {
		ofDrawBitmapString(musicPathList[currentMusicNumber], -423, 40);
	}

	//Tracking point 
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 's':
		currentMusicNumber++;
		musicPlayer.load(musicPathList[currentMusicNumber]);
		musicPlayer.setVolume(0.1);
		musicPlayer.play();
	case 'n':
		currentMusicNumber++;
		musicPlayer.load(musicPathList[currentMusicNumber]);
		musicPlayer.setVolume(0.1);
		musicPlayer.play();
	case 'b':
		currentMusicNumber--;
		musicPlayer.load(musicPathList[currentMusicNumber]);
		musicPlayer.setVolume(0.1);
		musicPlayer.play();
	default:
		break;
	}
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