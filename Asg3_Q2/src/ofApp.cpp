#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup();

	//Green
	//H 32 97
	//S 53 255
	//V 99 255

	gui.add(minH.setup("min H", 42, 0, 180));
	gui.add(maxH.setup("max H", 63, 0, 180));
	gui.add(minS.setup("min S", 0, 0, 255));
	gui.add(maxS.setup("max S", 255, 0, 255));
	gui.add(minV.setup("min V", 201, 0, 255));
	gui.add(maxV.setup("max V", 255, 0, 255));

	vidGrabber.initGrabber(320, 240);

	//Initialize Mat for drawing purpose
	drawImg.setFromPixels(vidGrabber.getPixels());
	topMat = toCv(drawImg);

	//Create a black mat for drawing
	for (int x = 0; x < topMat.cols; x++) {
		for (int y = 0; y < topMat.rows; y++) {
			topMat.data[(x + y * topMat.cols) * 3] = 0;
			topMat.data[(x + y * topMat.cols) * 3 + 1] = 0;
			topMat.data[(x + y * topMat.cols) * 3 + 2] = 0;
		}
	}

}

//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();
	//do we have a new frame?
	if (vidGrabber.isFrameNew()) {
		im.setFromPixels(vidGrabber.getPixels());
		mat = toCv(im);
		cvtColor(mat, mat_HSV, CV_BGR2HSV);
		inRange(mat_HSV, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), mat_HSV_Threshold);
		erode(mat_HSV_Threshold, mat_HSV_Threshold, Mat());
		dilate(mat_HSV_Threshold, mat_HSV_Threshold, Mat());

		ofImage im_temp;
		ofxCvGrayscaleImage im_temp_gray;

		toOf(mat_HSV_Threshold, im_temp);

		im_temp_gray.setFromPixels(im_temp.getPixels());

		contourFinder.findContours(im_temp_gray, 5, (340 * 240) / 4, 4, false, true);
		/*detector->detect(mat_HSV_Threshold, keypoints);

		drawKeypoints(mat, keypoints, result, Scalar(255, 0, 0), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);*/
	}

	if(drawMode) {
		topMat.data[(pen_centreX + pen_centreY * topMat.cols) * 3 + 1] = 255;
	}

	finalMat = combineMat(mat, topMat);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 255, 255);
	drawMat(mat, 0, 0);
	//drawMat(topMat, 0, 0);
	for (int i = 0; i < contourFinder.nBlobs; i++) {
		ofRectangle r = contourFinder.blobs.at(i).boundingRect;

		cout << "Rectangle " << i  << ": x:" << r.x << " y:" << r.y << " width:" << r.width << " height:" << r.height << " position: " << r.position << endl;
		cout << "Rectangle " << i << ": center: (" << r.x + (r.width / 2) << "," << r.y + (r.height / 2) << ")" << endl;

		pen_centreX = r.x + (r.width / 2);
		pen_centreY = r.y + (r.height / 2);

		ofSetColor(255,0,0);
		ofNoFill();
		ofDrawRectangle(r);
	}
	ofSetColor(255, 255, 255);
	drawMat(mat_HSV_Threshold, mat.cols, 0);
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's') {
		cout << "Key /"s" detected." << endl;
		if (!drawMode) {
			drawMode = true;
			cout << "Turned on Draw mode." << endl;
		}
		else {
			drawMode = false;
			cout << "Turned off Draw mode." << endl;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

bool ofApp::isGreen(Mat mat, int x, int y) {
	if ((int(mat.data[(x + y * mat.cols) * 3 + 1])) == 255) {
		return true;
	}

	else return false;
}

Mat ofApp::combineMat(Mat backMat, Mat frontMat) {
	for (int x = 0; x < backMat.cols; x ++) {
		for (int y = 0; y < backMat.rows; y ++) {
			if (isGreen(frontMat, x, y)) {
				backMat.data[(x + y * backMat.cols) * 3] = frontMat.data[(x + y * frontMat.cols) * 3];
				backMat.data[(x + y * backMat.cols) * 3 + 1] = frontMat.data[(x + y * frontMat.cols) * 3 + 1];
				backMat.data[(x + y * backMat.cols) * 3 + 2] = frontMat.data[(x + y * frontMat.cols) * 3 + 2];
			}
		}
	}

	return backMat;
}
