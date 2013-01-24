/*
 *  CirclePacker.cpp
 *  CirclePacking
 *
 *  Created by Nick Hardeman on 4/11/11.
 *  Copyright 2011 Arnold Worldwide. All rights reserved.
 *
 */

#include "CirclePacker.h"

CirclePacker::CirclePacker() {
	_pixels			= NULL;	
	_bAlreadyHit	= NULL;
	_bSetup			= false;
}

CirclePacker::~CirclePacker() {
	destroy();
}

void CirclePacker::setup( int $_id, ofImage& $image, ofColor $targetColor, int $colorRange, float $minRadius ) {
	_iw					= $image.width;
	_ih					= $image.height;
	_id					= $_id;
	init();
	_pixels				= $image.getPixels();
	_targetColor		= $targetColor;
	_colorRange			= $colorRange;
	_minRadius			= $minRadius;
	_bSetup				= true;
}

void CirclePacker::init() {
	clear();
	_bAlreadyHit		= new bool[_iw * _ih];
	for (int i = 0; i < (_iw * _ih); i++) {
		_bAlreadyHit[i] = false;
	}
	_bFoundAllCircles	= false;
	_maxRad				= -1;
	count				= 0;
}

void CirclePacker::clear() {
	if(_bAlreadyHit != NULL) { delete [] _bAlreadyHit; _bAlreadyHit = NULL;}
	if(_pixels != NULL) {delete [] _pixels; _pixels = NULL; }
}

int CirclePacker::getNumCircles() {
    return count;
}

int CirclePacker::isComplete() {
    return _bFoundAllCircles;
}

float CirclePacker::getElapsedTimeF() {
    return (_completeTime - _startTime);
}

void CirclePacker::threadedFunction() {
	while( isThreadRunning() != 0 ){
		if( lock() ){
			_update();
			//cout << count << endl;
			//count++;
			unlock();
			ofSleepMillis( 30 );
		}
	}
}

void CirclePacker::start() {
    _startTime = _completeTime = ofGetElapsedTimef();
	startThread(true, true);   // blocking, verbose
}

void CirclePacker::stop() {
	stopThread();
}

void CirclePacker::_update() {
	if(_bSetup && !_bFoundAllCircles) {
        _completeTime = ofGetElapsedTimef();
		if(_getNextCircleForColorRGB()) {
			if(verbose) cout << "["<<_id<<"] " << "maxRad is " << circles[circles.size()-1].radius << " count: " << count <<  endl;
		} else {
			_bFoundAllCircles = true;
			int temp = _id;
			if(verbose) cout << "["<<_id<<"] " << "FOUND ALL THE CIRCLES!!" <<  endl;
			stop();
            _completeTime = ofGetElapsedTimef();
			//ofNotifyEvent(CirclePackerEvent, temp, this);
		}
	}
}


bool CirclePacker::_getNextCircleForColorRGB( ) {
	float _x, _y;
	bool bFoundCircle		= false;
	
	float theta = TWO_PI / 360.f;
	float angle = 0.f;
	float currRad = 0.f;
	float nx, ny;
	int ni, pixIndex, bHitIndex;
	
	for (int x = 1; x < _iw-1; x++) {
		for (int y = 1; y < _ih-1; y++) {
			bHitIndex	= ((y * _iw) + x);
			pixIndex	= bHitIndex * 3;
			
			bool bColorInRange = isColorInRange(_pixels[pixIndex], _pixels[pixIndex+1], _pixels[pixIndex+2], 
												_targetColor.r, _targetColor.g, _targetColor.b, _colorRange);
			
			if ( bColorInRange && _bAlreadyHit[bHitIndex] == false ) {
				//cout << "we made it into the pixels " << endl;
				theta = TWO_PI / 360.f;
				angle = 0.f;
				currRad = 0.f;
				int b = 1;
				while (b >= 1) {
					currRad += 1.f;
					for (int j = 0; j < 360; j++) {
						nx = round(cos(angle) * currRad) + x;
						ny = round(sin(angle) * currRad) + y;
						
						ni = ( ny * _iw) + nx;
						
						bool bBadPixel = false;
						if(!isColorInRange(_pixels[ni*3], _pixels[ni*3+1], _pixels[ni*3+2], 
										   _targetColor.r, _targetColor.g, _targetColor.b, _colorRange)) {
							bBadPixel = true;
						}
						if (_bAlreadyHit[ni] == true) bBadPixel = true;
						
						if (bBadPixel) {
							b = 0;
							currRad -= 1.f;
							break;
						}
						
						angle += theta;
					}
					angle	= 0;
				}
				if(currRad >= _maxRad && currRad >= _minRadius) {
					_x = x;
					_y = y;
					_maxRad = currRad;
					bFoundCircle = true;
				}
			}
		}
	}
	// now let's set its pixels as hit so we don't hit them anymore //
	if(bFoundCircle) {
		theta = TWO_PI / 360.f;
		angle = 0.f;
		currRad = 0.f;
		
		for(int ri = 0; ri < _maxRad-1; ri++) {
			currRad += 1.f;
			for (int j = 0; j < 360; j++) {
				nx = round(cos(angle) * currRad) + _x;
				ny = round(sin(angle) * currRad) + _y;
				
				ni = ( ny * _iw) + nx;
				_bAlreadyHit[ni] = true;
				
				angle += theta;
			}
			angle	= 0;
		}
		ofxParticle2D circle;
		circle.loc.x	= _x;
		circle.loc.y	= _y;
		circle.radius	= _maxRad;
		circles.push_back( circle );
		_maxRad = -1;
	}
	
	count++;
	
	return bFoundCircle;
}

bool CirclePacker::isColorInRange(int $pr, int $pg, int $pb, int $tr, int $tg, int $tb, int $padding) {
	int rDiff, gDiff, bDiff;
	rDiff		= $pr - $tr;
	rDiff		= abs(rDiff);
	gDiff		= $pg - $tg;
	gDiff		= abs(gDiff);
	bDiff		= $pb - $tb;
	bDiff		= abs(bDiff);
	
	if(rDiff <= $padding) {
		if(gDiff <= $padding) {
			if(bDiff <= $padding) {
				return true;
			}
		}
	}
	
	return false;
}


void CirclePacker::destroy() {
	stopThread(true);
	_bSetup		= false;
	clear();
}