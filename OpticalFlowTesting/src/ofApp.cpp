#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    myVideoGrabber.initGrabber(640, 480);
}

void ofApp::initPointsToTrack(cv::Size subPixWinSize, TermCriteria termcrit){
    
    goodFeaturesToTrack(matCamGrey, curPoints, MAX_COUNT, 0.01, 10, Mat(), 3, 0, 0.04);
    cornerSubPix(matCamGrey, curPoints, subPixWinSize, cv::Size(-1,-1),termcrit);
    
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
        Point2f dir = Point2f(curPoints.at(i).x-prePoints.at(i).x,curPoints.at(i).y-prePoints.at(i).y);
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
        if(needToInit){
            initPointsToTrack(subPixWinSize, termcrit);
            needToInit = false;
        }
        else if(!prePoints.empty()){
            trackKeyPoints(winSize);
            getDirections();
            Point2f averageDir = getAverageDirection();
            cout<<averageDir<<endl;
            //the threshold needs to be adjusted
            if(averageDir.x > 0.1 ){
                cout<<"move right"<<endl;
                
            }
            else if(averageDir.x < -0.1 ){
                cout<<"move left"<<endl;
            }
            else{
                cout<<"Nothing moving"<<endl;
            }
            
        }
        
        std::swap(curPoints, prePoints);
        cv::swap(matCamPreGrey, matCamGrey);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255,255,255);
    drawMat(matCam, 0, 0);
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
            case 'r':
                cout<<"re-initialize"<<endl;
                needToInit = true;
                break;
    }
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
    point = Point2f((float)x, (float)y);
    addRemovePt = true;
    
    if( addRemovePt && curPoints.size() < (size_t)MAX_COUNT )
    {
        vector<Point2f> tmp;
        cv::Size winSize(31,31);
        TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20, 0.03);
        tmp.push_back(point);
        cornerSubPix( matCamGrey, tmp, winSize, cv::Size(-1,-1), termcrit);
        curPoints.push_back(tmp[0]);
        addRemovePt = false;
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
