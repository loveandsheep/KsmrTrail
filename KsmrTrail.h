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

#define NUM_VERTS_MAX 100

enum KsmrTrailType{
	KSMR_TRAIL_NORMAL,
	KSMR_TRAIL_LINE_THIN,
	KSMR_TRAIL_MESH
};

class KsmrTrail{
public:
	void setup(ofVec3f pos, float wid = 13.0, int length = 20);
	void update(ofVec3f target);
	void draw(KsmrTrailType type = KSMR_TRAIL_NORMAL, int resolution = 1);

	void setWidth(float w);
	void setNumVerts(int num);
	void setHeadAttenuation(float att);
	void setColor(ofFloatColor c);

	void resetPosition(ofVec3f pos);

	ofVec3f* getHeadsPos(){return &head[0];};
	ofVec3f* getHeadsVec(){return &head_vec[0];};
	ofVec3f* getHeadsAcc(){return &head_acc[0];};

protected:
	int numVerts;

	ofVec3f head_acc[NUM_VERTS_MAX];
	ofVec3f head_vec[NUM_VERTS_MAX];
	ofVec3f head[NUM_VERTS_MAX];

	float width;
	float coef_x;
	float coef_y;

	float head_atten;
	float tail_atten;
	float tail_accVel;

	ofFloatColor col;
};

#endif /* defined(__KsmrTailTest__KsmrTrail__) */
