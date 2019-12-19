#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    myVideoGrabber.initGrabber(640, 480);

	if (!face_cascade.load("P:/Workspace/OpenFramework/Asg3_Q1/bin/data/haarcascade_frontalface_default.xml")) {
		cout << "Error loading face xml" << endl;
	}
	else {
		cout << "Successfully loaded face_cascade" << endl;
	}
}

void ofApp::initPointsToTrack(cv::Size subPixWinSize, TermCriteria termcrit){
    
	//Determine strong corners and store it in 2nd parameter
    goodFeaturesToTrack(matMask, curPoints, MAX_COUNT, 0.01, 10, Mat(), 3, 0, 0.04);
    
	//Refine corner locations
	cornerSubPix(matMask, curPoints, subPixWinSize, cv::Size(-1,-1),termcrit);

	/*
	
	//Determine strong corners and store it in 2nd parameter
    goodFeaturesToTrack(matCamGrey, curPoints, MAX_COUNT, 0.01, 10, Mat(), 3, 0, 0.04);
    
	//Refine corner locations
	cornerSubPix(matCamGrey, curPoints, subPixWinSize, cv::Size(-1,-1),termcrit);

	*/
    
}

void ofApp::trackKeyPoints(cv::Size winSize){
    
    vector<uchar> status;
    vector<float> err;
    if(matCamPreGrey.empty()){
        matCamGrey.copyTo(matCamPreGrey);
    }
    calcOpticalFlowPyrLK(matCamPreGrey, matCamGrey, prePoints, curPoints, status, err, winSize);
}

void ofApp::getDirections(){
    for(int i = 0; i < curPoints.size(); i++){
        Point2f dir = Point2f(curPoints.at(i).x - prePoints.at(i).x,curPoints.at(i).y - prePoints.at(i).y);
        directions.push_back(dir);
    }
}

Point2f ofApp::getAverageDirection(){
    Point2f averageDir(0,0);
    for(int i = 0; i < directions.size(); i++){
        averageDir.x += directions.at(i).x;
        averageDir.y += directions.at(i).y;
    }
    if(directions.size()!=0){
        averageDir.x /= directions.size();
        averageDir.y /= directions.size();
    }
    return averageDir;
}


//--------------------------------------------------------------
void ofApp::update(){
    myVideoGrabber.update();
    
    TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20, 0.03);
    cv::Size subPixWinSize(10,10),winSize(31,31);
    
    // If the grabber indeed has fresh data,
	if (myVideoGrabber.isFrameNew()) {
		// Obtain a pointer to the grabber's image data.
		imgCam.setFromPixels(myVideoGrabber.getPixels());
		matCam = toCv(imgCam);
		cvtColor(matCam, matCamGrey, CV_BGR2GRAY);

		//needToInit is true when press 'r'
        
		if (needToInit) {
			for (int y = 0; y < matMask.rows; y++) {
				for (int x = 0; x < matMask.cols; x++) {
					//if (!(x > faces.at(0).x && x < faces.at(0).width && y > faces.at(0).y && y < faces.at(0).height)) {
					if (!(x > faces.at(0).x
						&& x < faces.at(0).x + faces.at(0).width
						&& y > faces.at(0).y
						&& y < faces.at(0).y + faces.at(0).height))
					{

						matMask.at<uchar>(y, x) = 0;
					}
				}
			}

		
			//Size subPixWinSize(10,10)
			//termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20, 0.03)
            initPointsToTrack(subPixWinSize, termcrit);
            needToInit = false;
        }
        
		else if(!prePoints.empty()){
			//cout << "previous point is not empty!!!!! :-)" << endl;
            trackKeyPoints(winSize);
            getDirections();
            Point2f averageDir = getAverageDirection();
            cout<<averageDir<<endl;
            //the threshold needs to be adjusted

			/*
            if(averageDir.x > 0.1 ){
				if (averageDir.y < -0.1) {
					cout << "move up right" << endl;
				}
				else if (averageDir.y > 0.1) {
					cout << "move down right" << endl;
				}
				else {
					cout << "move right" << endl;
				}
            }
            else if(averageDir.x < -0.1 ){
				if (averageDir.y < -0.1) {
					cout << "move up left" << endl;
				}
				else if (averageDir.y > 0.1) {
					cout << "move down left" << endl;
				}
				else {
					cout << "move left" << endl;
				}
            }
            else{
				if (averageDir.y < -0.1) {
					cout << "move up" << endl;
				}
				else if (averageDir.y > 0.1) {
					cout << "move down" << endl;
				}
				else {
					cout << "Nothing moving" << endl;
				}
            }
			*/

			if (averageDir.x > 0.1 || averageDir.x < -0.1) {
				cout << "Shaking" << endl;
				status = "Shaking";
			}
			
			else {
				if (averageDir.y < -0.03 || averageDir.y > 0.03) {
					cout << "Nodding" << endl;
					status = "Nodding";
				}
				else {
					cout << "Nothing moving" << endl;
					status = "No action";
				}
			}
		}
		else {
			//cout << "previous point is empty :-P" << endl;
		}
		
		
        
        std::swap(curPoints, prePoints);
        cv::swap(matCamPreGrey, matCamGrey);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255,255,255);
	drawMat(matCam, 0, 0);
	ofDrawBitmapString("Current status: ", 10, 10);
	ofDrawBitmapString(status, 10, 20);

    if(!prePoints.empty()){
        for(int i = 0; i < curPoints.size(); i++ )
        {
            ofSetColor(0,255,0);
            ofDrawCircle(curPoints[i].x, curPoints[i].y, 3);
            ofSetColor(255,0,0);
            ofDrawLine(prePoints[i].x, prePoints[i].y, curPoints[i].x, curPoints[i].y);
        }
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
            case 'c':
                cout<<"clear points"<<endl;
                prePoints.clear();
                curPoints.clear();
                break;
            case 's':
                cout<<"re-initialize"<<endl;

				//steal from S button
				cout << "Start face detection" << endl;

				//start face detection
				face_cascade.detectMultiScale(matCam, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(150, 150));

				if (!faces.empty()) {
					cout << "We found out face!" << endl;
				}
				matMask = matCamGrey;
				testing = true;



                needToInit = true;
				break;

				// at this point the face information is stored
    }
}
