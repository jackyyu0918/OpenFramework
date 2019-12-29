#include "ofApp.h"
#include <cmath>

//--------------------------------------------------------------
void ofApp::setup() {
	myVideoGrabber.initGrabber(320, 240);
	//myVideoGrabber.initGrabber(640, 480);

	if (!leftHand_cascade.load("P:/Workspace/OpenFramework/MusicPlayer_withHandDetection/bin/data/lpalm.xml")) {
		cout << "Error loading leftHand_cascade" << endl;
	}
	else {
		cout << "Successfully loaded left hand xml" << endl;
	}

	//Music player section
	string path = "P:/Workspace/OpenFramework/MiniProject/bin/data/song";

	for (const auto& entry : filesystem::directory_iterator::directory_iterator(path)) {
		cout << "Adding: " << entry.path().string() << endl;
		musicPathList.push_back(entry.path().string());
	}
	cout <<"MusicPathList size: " << musicPathList.size() << endl;

	//Volume section
	gui.setup();

	//Green
	//H 32 97
	//S 53 255
	//V 99 255

	gui.add(minH.setup("min H", 42, 0, 180));
	gui.add(maxH.setup("max H", 63, 0, 180));
	gui.add(minS.setup("min S", 100, 0, 255));
	gui.add(maxS.setup("max S", 255, 0, 255));
	gui.add(minV.setup("min V", 80, 0, 255));
	gui.add(maxV.setup("max V", 255, 0, 255));
}

void ofApp::initPointsToTrack(cv::Size subPixWinSize, TermCriteria termcrit) {

	// size is for minimum size
		leftHand_cascade.detectMultiScale(matCam, leftHands, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

	//Draw rectangle for detected face
	for (int i = 0; i < leftHands.size(); i++) {

				Rect roi(leftHands.at(i).x, leftHands.at(i).y, leftHands.at(i).width, leftHands.at(i).height);
				mask = Mat::zeros(matCamGrey.size(), CV_8UC1);
				mask(roi).setTo(255);
			
	}

	goodFeaturesToTrack(matCamGrey, curPoints, MAX_COUNT, 0.01, 10, mask, 3, 0, 0.04);
	mask.setTo(0);
	cornerSubPix(matCamGrey, curPoints, subPixWinSize, cv::Size(-1, -1), termcrit);

}

void ofApp::trackKeyPoints(cv::Size winSize) {

	vector<uchar> status;
	vector<float> err;
	if (matCamPreGrey.empty()) {
		matCamGrey.copyTo(matCamPreGrey);
	}
	calcOpticalFlowPyrLK(matCamPreGrey, matCamGrey, prePoints, curPoints, status, err, winSize);

}

void ofApp::getDirections() {
	for (int i = 0; i < curPoints.size(); i++) {
		Point2f dir = Point2f(curPoints.at(i).x - prePoints.at(i).x, curPoints.at(i).y - prePoints.at(i).y);
		directions.push_back(dir);
	}
}

Point2f ofApp::getAverageDirection() {
	Point2f averageDir(0, 0);
	for (int i = 0; i < directions.size(); i++) {
		averageDir.x += directions.at(i).x;
		averageDir.y += directions.at(i).y;
	}
	if (directions.size() != 0) {
		averageDir.x /= directions.size();
		averageDir.y /= directions.size();
	}
	return averageDir;
}


//--------------------------------------------------------------
void ofApp::update() {
	myVideoGrabber.update();

	TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
	cv::Size subPixWinSize(10, 10), winSize(31, 31);

	// If the grabber indeed has fresh data,
	if (myVideoGrabber.isFrameNew()) {
		// Obtain a pointer to the grabber's image data.
		imgCam.setFromPixels(myVideoGrabber.getPixels());
		matCam = toCv(imgCam);
		cvtColor(matCam, matCamGrey, CV_BGR2GRAY);
		cvtColor(matCam, mat_HSV, CV_BGR2HSV);

		//Song selection mode
		autoTrack();

		if (needToInit) {
			initPointsToTrack(subPixWinSize, termcrit);
			needToInit = false;
		}
		else if (!prePoints.empty()) {
			trackKeyPoints(winSize);
			getDirections();
			Point2f averageDir = getAverageDirection();
			cout << "averageDir.x: " << averageDir.x << endl;

			if (averageDir.x > 0.3){
			//if ((((averageDir.x - (prevAverageDir.x)) / (prevAverageDir.x))) > 1) {
				//cout << "move left" << endl;
				status = "left";
				//Play previous song
				if (currentMusicNumber > 0) {
					playPreviousSong();
				}
				else {
					cout << "No Previous Song." << endl;
				}

				
				//clear point
				prePoints.clear();
				curPoints.clear();
				clearDirections();

				//reset status
				isLeftHandDetected = false;
				
			}
			else if (averageDir.x < -0.25) {
			//else if ((((averageDir.x - (prevAverageDir.x)) / (prevAverageDir.x))) < -1){
				cout << "move right" << endl;
				status = "right";
				cout << "currentMusicNumber: " << currentMusicNumber << endl;
				if (currentMusicNumber < int(musicPathList.size() - 1)) {
					playNextSong();
				}
				else {
					cout << "Already reach the end of playlist." << endl;
				}

				
				//clear point
				prePoints.clear();
				curPoints.clear();
				clearDirections();

				//reset status
				isLeftHandDetected = false;
			}
			else {
				//cout << "nothing";
			}
		}

		std::swap(curPoints, prePoints);
		cv::swap(matCamPreGrey, matCamGrey);

		//volume control mode
		inRange(mat_HSV, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), mat_HSV_Threshold);
		erode(mat_HSV_Threshold, mat_HSV_Threshold, Mat());
		dilate(mat_HSV_Threshold, mat_HSV_Threshold, Mat());
	
		ofImage im_temp;
		ofxCvGrayscaleImage im_temp_gray;

		toOf(mat_HSV_Threshold, im_temp);

		im_temp_gray.setFromPixels(im_temp.getPixels());

		contourFinder.findContours(im_temp_gray, 5, (340 * 240) / 4, 4, false, true);
	
		//cout << "pen_centreX: " << pen_centreX << endl;
		//cout << "pen_centreY: " << pen_centreY << endl;
		//cout << "Relative Y: " << pen_centreY / matCam.rows << endl;
		//cout << "matCam.rows: " << matCam.rows << endl;

		volumeResult = abs((matCam.rows - pen_centreY) / float(matCam.rows));
		//cout << "volumeResult: " << volumeResult << endl;
		
		musicPlayer.setVolume(volumeResult);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	//song selection mode
	ofSetColor(255, 255, 255);
	drawMat(matCam, 0, 0);

	//Music message section
	ofDrawBitmapString(currentMode , 0, 20);
	ofDrawBitmapString("Current music: ", 0, 40);
	if (currentMusicNumber == -1) {
		ofDrawBitmapString("No music is playing now.", 0, 60);
	}
	else {
		ofDrawBitmapString(musicPathList[currentMusicNumber], -423, 60);
	}
	string currentVolume = "Volume: " + to_string(volumeResult * 100) + "%";
	ofDrawBitmapString(currentVolume, 0, 80);
	if (!prePoints.empty()) {
		for (int i = 0; i < curPoints.size(); i++)
		{
			ofSetColor(0, 255, 0);
			ofDrawCircle(curPoints[i].x, curPoints[i].y, 3);
			ofSetColor(255, 0, 0);
			ofDrawLine(prePoints[i].x, prePoints[i].y, curPoints[i].x, curPoints[i].y);
		}
	}

	//volume mode
	for (int i = 0; i < contourFinder.nBlobs; i++) {
		ofRectangle r = contourFinder.blobs.at(i).boundingRect;\

		pen_centreX = r.x + (r.width / 2);
		pen_centreY = r.y + (r.height / 2);

		ofSetColor(255, 0, 0);
		ofNoFill();
		ofDrawRectangle(r);
	}
	ofSetColor(255, 255, 255);
	drawMat(mat_HSV_Threshold, matCam.cols, 0);
	gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	switch (key) {
	case 'c':
		cout << "clear points" << endl;
		prePoints.clear();
		curPoints.clear();
		clearDirections();
		autoTrack();
		break;
	case 'r':
		cout << "re-initialize" << endl;
		needToInit = true;
		prePoints.clear();
		curPoints.clear();
		clearDirections();
		break;
	}
}

void ofApp::playNextSong() {
	currentMusicNumber++;
	musicPlayer.load(musicPathList[currentMusicNumber]);
	musicPlayer.setVolume(0.1);
	musicPlayer.play();

	cout << "playNextSong" << endl;
}

void ofApp::playPreviousSong() {
	currentMusicNumber--;
	musicPlayer.load(musicPathList[currentMusicNumber]);
	musicPlayer.play();

	cout << "playPreviousSong" << endl;
}

void ofApp::clearDirections() {
	directions.clear();
}

void ofApp::autoTrack() {
	if (!isLeftHandDetected) {
		leftHand_cascade.detectMultiScale(matCam, leftHands, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
		if (!leftHands.empty()) {
			needToInit = true;
			isLeftHandDetected = true;
		}

	}
}