/*
 *  CirclePacker.h
 *  CirclePacking
 *
 *  Created by Nick Hardeman on 4/11/11.
 *  Copyright 2011 Arnold Worldwide. All rights reserved.
 *
 */
#pragma once
#include "ofMain.h"
#include "ofxParticle2D.h"

class CirclePacker : public ofThread {
public:
	//ofEvent<int> CirclePackerEvent;
	CirclePacker();
	~CirclePacker();
	void init();
	void clear();
	
	void setup( int $_id, ofImage& $image, ofColor $targetColor, int $colorRange, float $minRadius );
	
	void start();
	void stop();
	void threadedFunction();
    
    int getNumCircles();
    int isComplete();
    float getElapsedTimeF();
	
	bool isColorInRange(int $pr, int $pg, int $pb, int $tr, int $tg, int $tb, int $padding);
	
	void destroy();
	
	int count;
	vector <ofxParticle2D> circles;
	
private:
	
	void _update();
	bool _getNextCircleForColorRGB();
	
	unsigned char* _pixels;
	ofColor	_targetColor;
	int _colorRange;
	float _minRadius;
	
	int _id;
    
    float _startTime, _completeTime;
	
	
	bool _bFoundAllCircles;
	bool _bSetup;
	int _iw, _ih;
	bool* _bAlreadyHit;
	float	_maxRad; // store the largest radius of the circle //
	
};