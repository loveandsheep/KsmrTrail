//
//  KsmrTrail.h
//  KsmrTailTest
//
//  Created by Ovis aries on 2014/10/23.
//
//

#ifndef __KsmrTailTest__KsmrTrail__
#define __KsmrTailTest__KsmrTrail__

#include "ofMain.h"

#define NUM_VERTS 20

class KsmrTrail{
public:
	void setup(ofVec3f pos);
	void update(ofVec3f target);
	void draw();

	void setWidth(float w);
	void setColor(ofFloatColor c);

	void resetPosition(ofVec3f pos);

	ofVec3f head_acc[NUM_VERTS];
	ofVec3f head_vec[NUM_VERTS];
	ofVec3f head[NUM_VERTS];

	float width;
	float coef_x;
	float coef_y;

	float tail_atten;
	float tail_accVel;

	ofFloatColor col;
};

#endif /* defined(__KsmrTailTest__KsmrTrail__) */
