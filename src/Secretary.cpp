/*
 *  FileSaver.cpp
 *  circles particles rec border
 *
 *  Created by Nick Hardeman on 4/8/11.
 *  Copyright 2011 Arnold Worldwide. All rights reserved.
 *
 */

#include "Secretary.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <unistd.h>
#include <sstream>
#include <iostream>
#include <fstream>

void Secretary::setParticles( vector <DrawingCircle *>& $particles ) {
	particles	= $particles;
}

bool Secretary::fileIt() {
	int nImages = DIR.listDir("renders/");
	if (nImages < 0) nImages = 0;
	
	string str = ofToString(nImages);
	
	if (str.size() < 2) {
		str = "0"+str;
	}
	str = "_"+str;
	
	_dir_name = "../../../data/renders/render"+str;
	
	cout << _dir_name << endl;
	
	int status = mkdir( (char * )_dir_name.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	//if (status <= 0) return false;
	
	saveAttributes();
	renderCairo( Secretary::ALL );
	renderCairo( Secretary::LINES );
	renderCairo( Secretary::CIRCLES );
	renderCairo( Secretary::CIRCLES_OUTLINES );
	
	clear();
	
	return true;
}

// make sure to call setPoints before calling this function //
bool Secretary::saveAttributes() {
	cout << "saving attributes" << endl;
	string file_name = _dir_name+"/attributes.txt";
	
	string date_string = ofToString(ofGetMonth()) + "/" + ofToString(ofGetDay()) + "/"+ofToString(ofGetYear());
	
	int total_pts = particles.size();
	
	ofstream myfile (file_name.c_str());
	if (myfile.is_open()) {
		myfile << "Date Rendered : "+date_string+".\n";
		myfile << "Total Points : "+ofToString(total_pts)+".\n";
		
		myfile.close();
	} else { cout << "Unable to open file"; return false;}
	
	return true;
}

void Secretary::renderCairo(int $mode) {
	string filename = "connected";
	
	if($mode == Secretary::ALL) {
		filename	= "all";
	} else if ($mode == Secretary::LINES) {
		filename	= "lines";
	} else if ($mode == Secretary::CIRCLES) {
		filename	= "circles";
	} else if ($mode == Secretary::OUTLINES) {
		filename	= "outlines";
	} else if ($mode == CIRCLES_OUTLINES) {
		filename	= "circles_outlines";
	}
	
	float tarRad	= 3.f;
	ofColor	col(150, 150, 150);
	
	string title = _dir_name+"/"+filename+".pdf";
	cairo.setup(title, ofCairoRenderer::PDF, false, false);
	cairo.background( 100, 100, 100 );
	cairo.setFillMode(OF_FILLED);
	
	cairo.setLineWidth(.8f);
	
	if($mode == Secretary::LINES) {
		for (int i = 0; i < particles.size()-1; i++) {
			//cairo.drawCircle(particles[i]->loc.x, particles[i]->loc.y, 0, particles[i]->radius);
			cairo.setColor(particles[i]->circleColor);
			cairo.drawLine(particles[i]->loc.x, particles[i]->loc.y, 0.f, particles[i+1]->loc.x, particles[i+1]->loc.y, 0.f);
		}
	}
	
	if($mode == Secretary::CIRCLES || $mode == Secretary::ALL) {
		for (int i = 0; i < particles.size(); i++) {
			cairo.setColor(particles[i]->circleColor);
			cairo.drawCircle(particles[i]->loc.x, particles[i]->loc.y, 0, particles[i]->radius);
		}
	}
	
	cairo.setFillMode(OF_OUTLINE);
	cairo.setLineWidth(1.f);
	if($mode == Secretary::OUTLINES || $mode == Secretary::CIRCLES_OUTLINES || $mode == Secretary::ALL) {
		for (int i = 0; i < particles.size(); i++) {
			cairo.setColor(particles[i]->lineColor);
			cairo.drawCircle(particles[i]->loc.x, particles[i]->loc.y, 0, particles[i]->radius);
		}
	}
	cairo.setFillMode(OF_FILLED);
	
	cairo.close();
	
}

void Secretary::clear() {
	particles.clear();
}



