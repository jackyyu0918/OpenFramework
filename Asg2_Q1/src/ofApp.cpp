#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    gui.add(lowThresholdEdge.setup("Edge Threshold", 50, 0, 100));
    vid.load("Car.mp4");
    vid.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    vid.update();
    vid.getCurrentFrame();
    if(vid.isFrameNew()){
        ofPixels pixs = vid.getPixels();
        vidFrame.setFromPixels(pixs);
        vidFrameMat = toCv(vidFrame);
        cvtColor(vidFrameMat, vidFrameMatGray, CV_BGR2GRAY);
        GaussianBlur(vidFrameMatGray, vidFrameMatGray, 3);
        Canny(vidFrameMatGray, vidFrameMatEdge, lowThresholdEdge, lowThresholdEdge*3);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255,255,255);
    drawMat(vidFrameMatEdge, 0, 0);
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
