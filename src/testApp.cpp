#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {	
	//ofSetWindowPosition(1500, 30);
	ofBackground(255, 255, 255);	
	//ofSetFrameRate(30);
	
	//if(!image.loadImage("rdLogo.jpg")) {
	if(!image.loadImage("openFrameworks_circle_600.jpg")) {
		cout << "could not load image " << endl;
	}
	image.setImageType( OF_IMAGE_COLOR );
	
	//colors.push_back( ofColor(250, 250, 250) );
	colors.push_back( ofColor(0, 0, 0) );
	
	// r & d logo //
	//colors.push_back( ofColor(213, 64, 59) );
	//colors.push_back( ofColor(232, 223, 85) );
	//colors.push_back( ofColor(82, 157, 96) );
	//colors.push_back( ofColor(1, 119, 195) );
	//colors.push_back( ofColor(69, 71, 125) );
	
	
	for (int i = 0; i < colors.size(); i++) {
		//thread.setup(1, image, colors[0], 20, 2.f );
		//thread.start();
		packerThreads.push_back( new CirclePacker() );
		packerThreads[packerThreads.size()-1]->setup(i, image, colors[i], 15, 3.f );
		packerThreads[packerThreads.size()-1]->start();
	}
	
	
	
}

//--------------------------------------------------------------
void testApp::update() {
	// sort all the particle
	
}

//--------------------------------------------------------------
void testApp::draw() {
	ofSetColor(255, 255, 255);
	//image.draw(0, 0, 0);
	ofSetColor(0,0,0);
	
	float scale = ((float)ofGetWidth()-220.f) / (float)image.width;
	scale = 1.4f;
	float yoffset = image.height+20;
	yoffset = 20;
	
	for(int i = 0; i < colors.size(); i++) {
		ofSetColor(colors[i]);
		for(int j = 0; j < packerThreads[i]->circles.size(); j++) {
			ofCircle(packerThreads[i]->circles[j].loc.x*scale, packerThreads[i]->circles[j].loc.y*scale +yoffset, packerThreads[i]->circles[j].radius*scale);
		}
	}
	
	
	ofSetLineWidth(1.f);
	ofSetColor(50, 50, 50);
	ofNoFill();
	for(int i = 0; i < colors.size(); i++) {
		//ofSetColor(colors[i]);
		for(int j = 0; j < packerThreads[i]->circles.size(); j++) {
			ofCircle(packerThreads[i]->circles[j].loc.x*scale, packerThreads[i]->circles[j].loc.y*scale +yoffset, packerThreads[i]->circles[j].radius*scale);
		}
	}
	ofFill();
    
    ofSetColor(0, 0, 0);
    stringstream ss;
    for(int i = 0; i < packerThreads.size(); i++ ) {
        ss << "Thread: "<<i<<" status: "<< (packerThreads[i]->isComplete()==true?"DONE!!":"WORKING") << " num circles: " << packerThreads[i]->getNumCircles()<< " elapsed time: " << packerThreads[i]->getElapsedTimeF() << endl;
    }
    ofDrawBitmapString(ss.str().c_str(), 20, 20 );
	
}

//--------------------------------------------------------------
void testApp::exit() {
	for (int i = 0; i < particles.size(); i++) {
		delete particles[i];
		particles[i] = NULL;
	}
	particles.clear();
    
    for(int i = 0; i < packerThreads.size(); i++ ) {
        packerThreads[i]->stop();
        delete packerThreads[i];
        packerThreads[i] = NULL;
    }
    packerThreads.clear();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	if (key == ' ') {
		for (int i = 0; i < particles.size(); i++) {
			delete particles[i];
			particles[i] = NULL;
		}
		particles.clear();
		
		int index = 0;
		for(int i = 0; i < colors.size(); i++) {
			for(int j = 0; j < packerThreads[i]->circles.size(); j++) {
				particles.push_back( new DrawingCircle() );
				index	= particles.size()-1;
				particles[index]->loc.x			= packerThreads[i]->circles[j].loc.x;
				particles[index]->loc.y			= packerThreads[i]->circles[j].loc.y;
				particles[index]->radius		= packerThreads[i]->circles[j].radius;
				particles[index]->circleColor	= colors[i];
				particles[index]->lineColor		= ofColor(50, 50, 50);
			}
		}
		secretary.clear();
		secretary.setParticles( particles );
		secretary.fileIt();
	} 
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
	
}

//------------- -------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
