/*
 *  DrawingCircle.h
 *  circles face
 *
 *  Created by Nick Hardeman on 4/11/11.
 *  Copyright 2011 Arnold Worldwide. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"
#include "ofxParticle2D.h"

class DrawingCircle : public ofxParticle2D {
public:
	ofColor	circleColor;
	ofColor lineColor;
};