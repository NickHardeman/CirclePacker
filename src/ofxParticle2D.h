/*
 *  Particle.h
 *  openFrameworks
 *
 *  Created by Nick Hardeman on 11/22/09.
 *
 */

#ifndef _OFX_PARTICLE_2D_
#define _OFX_PARTICLE_2D_

#include "ofMain.h"
#include "ofVec2f.h"

class ofxParticle2D {
public:
	ofVec2f loc;
	ofVec2f vel;
	ofVec2f acc;
	
	float	radius;
	int		ID;
	
	ofxParticle2D(){};
	ofxParticle2D(float $x, float $y){loc.set($x,$y);};
	
	virtual ~ofxParticle2D(){};
	
	
private:
};

#endif