//
//  KsmrTrail.cpp
//  KsmrTailTest
//
//  Created by Ovis aries on 2014/10/23.
//
//

#include "KsmrTrail.h"

void KsmrTrail::setup(ofVec3f pos, float wid, int length){
	for (int i = 0;i < NUM_VERTS_MAX;i++){
		head[i] = pos;
	}

	coef_x = ofRandom(30.0,200.0);
	coef_y = ofRandom(30.0,200.0);

	width = wid;

	tail_accVel = 1.0;
	tail_atten = 0.3;

	head_atten = 0.95;
	numVerts = length;
}

void KsmrTrail::update(ofVec3f target){
	float dst = target.distanceSquared(head[0]);
	
	ofVec3f noiseV = ofVec3f(ofNoise(dst/1.0)*10,
							 ofNoise(dst/1.0)*10,
							 ofNoise(dst/1.0)*10);

	for (int i = 0;i < numVerts;i++){

		if (i == 0){
			head_acc[i] = (target + noiseV) - head[i];
			head_vec[i].x += head_acc[i].x / coef_x;
			head_vec[i].y += head_acc[i].y / coef_y;
			head_vec[i] *= head_atten;
		}else{
			head_acc[i] = (head[i - 1] - head[i])*tail_accVel;
			head_vec[i] += head_acc[i];
			head_vec[i] *= tail_atten;
		}

		head[i] += head_vec[i];
	}

}

void KsmrTrail::setColor(ofFloatColor c){
	col = c;
}

void KsmrTrail::setWidth(float w){
	width = w;
}

void KsmrTrail::draw(){

	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofSetColor(col);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0;i < numVerts - 1;i++){
		if (i < numVerts - 2){
			ofVec3f v1 = (head[i]   - head[i+1]);
			ofVec3f v2 = (head[i+1] - head[i+2]);
			ofVec3f vn = v1.crossed(v2).normalized() * width * sin(i / float(numVerts-1.0f) * PI);

			ofVec3f vn1 = head[i] + vn;
			ofVec3f vn2 = head[i] - vn;

			glVertex3f(vn1.x, vn1.y, vn1.z);
			glVertex3f(vn2.x, vn2.y, vn2.z);
		}else{
			glVertex3f(head[i].x, head[i].y, head[i].z);
		}
	}
	glEnd();

	ofSetColor(255);
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
}

void KsmrTrail::resetPosition(ofVec3f pos){
	for (int i = 0;i < NUM_VERTS_MAX;i++){
		head[i] = pos;
		head_acc[i].set(0.0, 0.0, 0.0);
		head_vec[i].set(0.0, 0.0, 0.0);
	}
}

void KsmrTrail::setNumVerts(int num){
	resetPosition(head[0]);
}

void KsmrTrail::setHeadAttenuation(float att){
	head_atten = att;
}