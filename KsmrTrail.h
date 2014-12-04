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
	KSMR_TRAIL_MESH,
	KSMR_TRAIL_RIBBON
};

class KsmrTrail{
public:
	void setup(ofVec3f pos, float wid = 13.0, int length = 20);
	void update(ofVec3f target);
	void draw();

	void setWidth(float w);
	void setNumVerts(int num);
	void setHeadAttenuation(float att);
	void setColor(ofFloatColor c);

	void setType(KsmrTrailType type);
	void resetPosition(ofVec3f pos);

	ofFloatColor getColor(){return col;};

	ofVec3f* getHeadsPos(){return &head[0];};
	ofVec3f* getHeadsVec(){return &head_vec[0];};
	ofVec3f* getHeadsAcc(){return &head_acc[0];};

	bool dynamic_width;
	float dynamic_width_k;
	int resolution;
protected:
	KsmrTrailType currentType;
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
	vector<ofVec3f> verts_shape;
};

#endif /* defined(__KsmrTailTest__KsmrTrail__) */
