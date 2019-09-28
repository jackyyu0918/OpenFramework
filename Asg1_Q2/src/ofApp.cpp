#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
	imgLena.load("Lena.jpg");
	matLena = toCv(imgLena);

	imgCircuit.load("circuit.tif");
	matCircuit = toCv(imgCircuit);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	/*
	Q2.1a)
	Lena

	imgLena.draw(0,0);

	boxFilter(matLena, matNewLena, -1, Size(3, 3));
	drawMat(matNewLena, imgLena.getWidth(), 0);

	boxFilter(matLena, matNewLena, -1, Size(5, 5));
	drawMat(matNewLena, imgLena.getWidth()*2, 0);

	boxFilter(matLena, matNewLena, -1, Size(7, 7));
	drawMat(matNewLena, 0, imgLena.getHeight());

	boxFilter(matLena, matNewLena, -1, Size(9, 9));
	drawMat(matNewLena, imgLena.getWidth(), imgLena.getHeight());

	boxFilter(matLena, matNewLena, -1, Size(11, 11));
	drawMat(matNewLena, imgLena.getWidth()*2, imgLena.getHeight());
	*/

	/*
	Q2.1b)
	Circuit

	imgCircuit.draw(0, 0);

	boxFilter(matCircuit, matCircuit, -1, Size(3, 3));
	drawMat(matCircuit, imgCircuit.getWidth(), 0);

	boxFilter(matLena, matNewLena, -1, Size(5, 5));
	drawMat(matCircuit, imgCircuit.getWidth()*2, 0);

	boxFilter(matLena, matNewLena, -1, Size(7, 7));
	drawMat(matCircuit, 0, imgCircuit.getHeight());

	boxFilter(matLena, matNewLena, -1, Size(9, 9));
	drawMat(matCircuit, imgCircuit.getWidth(), imgCircuit.getHeight());

	boxFilter(matLena, matNewLena, -1, Size(11, 11));
	drawMat(matCircuit, imgCircuit.getWidth()*2, imgCircuit.getHeight());
	*/

	/*
	Q2.2a)
	Lena
	imgLena.draw(0, 0);

	GaussianBlur(matLena, matNewLena, Size(3, 3), 4,4);
	drawMat(matNewLena, imgLena.getWidth(), 0);

	GaussianBlur(matLena, matNewLena, Size(3, 3),  5,5);
	drawMat(matNewLena, imgLena.getWidth() * 2, 0);

	GaussianBlur(matLena, matNewLena, Size(3, 3), 6,6);
	drawMat(matNewLena, 0, imgLena.getHeight());

	GaussianBlur(matLena, matNewLena, Size(3, 3), 7,7);
	drawMat(matNewLena, imgLena.getWidth(), imgLena.getHeight());

	GaussianBlur(matLena, matNewLena, Size(3, 3), 8,8);
	drawMat(matNewLena, imgLena.getWidth() * 2, imgLena.getHeight());

	GaussianBlur(matLena, matNewLena, Size(3, 3), 9,9);
	drawMat(matNewLena, 0, imgLena.getHeight()*2);

	GaussianBlur(matLena, matNewLena, Size(3, 3), 10,10);
	drawMat(matNewLena, imgLena.getWidth(), imgLena.getHeight()*2);
	*/

	/*
	Q2.3a)
	Lena

	imgLena.draw(0, 0);

	medianBlur(matLena, matNewLena, 3);
	drawMat(matNewLena, imgLena.getWidth(), 0);

	medianBlur(matLena, matNewLena, 5);
	drawMat(matNewLena, imgLena.getWidth() * 2, 0);

	medianBlur(matLena, matNewLena, 7);
	drawMat(matNewLena, 0, imgLena.getHeight());

	medianBlur(matLena, matNewLena, 9);
	drawMat(matNewLena, imgLena.getWidth(), imgLena.getHeight());

	medianBlur(matLena, matNewLena, 11);
	drawMat(matNewLena, imgLena.getWidth() * 2, imgLena.getHeight());
	*/

	/*
	Q2.3b)
	Circuit

	imgCircuit.draw(0, 0);

	medianBlur(matCircuit, matNewCircuit, 3);
	drawMat(matNewCircuit, imgCircuit.getWidth(), 0);

	medianBlur(matCircuit, matNewCircuit, 5);
	drawMat(matNewCircuit, imgCircuit.getWidth() * 2, 0);

	medianBlur(matCircuit, matNewCircuit, 7);
	drawMat(matNewCircuit, 0, imgCircuit.getHeight());

	medianBlur(matCircuit, matNewCircuit, 9);
	drawMat(matNewCircuit, imgCircuit.getWidth(), imgCircuit.getHeight());

	medianBlur(matCircuit, matNewCircuit, 11);
	drawMat(matNewCircuit, imgCircuit.getWidth() * 2, imgCircuit.getHeight());
	*/
}