/*
 *  FileSaver.h
 *  circles particles rec border
 *
 *  Created by Nick Hardeman on 4/8/11.
 *  Copyright 2011 Arnold Worldwide. All rights reserved.
 *
 */
#pragma once
#include "ofMain.h"
#include "DrawingCircle.h"
#include "ofCairoRenderer.h"

class Secretary {
public:
	
	enum Filename {
		LINES		=	0,
		CIRCLES		=	1,
		OUTLINES	=	2,
		CIRCLES_OUTLINES	= 3,
		ALL			=	4
	};
	
	void setParticles( vector <DrawingCircle *>& $particles );
	bool fileIt( );
	bool saveAttributes();
	void renderCairo(int $mode);
	
	void clear();
	
	ofCairoRenderer cairo;
	
	ofDirectory DIR;
	vector <DrawingCircle *> particles;
	
private:
	string _dir_name;
};