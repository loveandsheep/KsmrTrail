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

	currentType = KSMR_TRAIL_NORMAL;
	dynamic_width = false;
	dynamic_width_k = 200.0;
	resolution = 1;
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

	//シェイプ更新

	if ((currentType == KSMR_TRAIL_NORMAL) ||
		(currentType == KSMR_TRAIL_MESH)){
		verts_shape.clear();
		for (int i = 0;i < numVerts - 1;i+=resolution){
			if (i < numVerts - 2){
				ofVec3f v1 = (head[i]   - head[i+1]);
				ofVec3f v2 = (head[i+1] - head[i+2]);

				if (dynamic_width){
					width = v2.distance(v1)*dynamic_width_k;
				}

				ofVec3f vn = v1.crossed(v2).normalized() * width * sin(i / float(numVerts-1.0f) * PI);

				ofVec3f vn1 = head[i] + vn;
				ofVec3f vn2 = head[i] - vn;
				verts_shape.push_back(ofVec3f(vn1));
				verts_shape.push_back(ofVec3f(vn2));

			}else{
				verts_shape.push_back(ofVec3f(head[i]));
			}
		}
	}

	if (currentType == KSMR_TRAIL_RIBBON){
		verts_shape.clear();
		for (int i = 0;i < numVerts - 1;i+=resolution){
			if (i < numVerts - 2){
				ofVec3f v1 = (head[i]   - head[i+1]);
				ofVec3f v2 = (head[i+1] - head[i+2]);

				if (dynamic_width){
					width = v2.distance(v1)*dynamic_width_k;
				}

				ofVec3f vn = v1.crossed(v2).normalized() * width;

				vn.rotate(ofNoise(v1.x/3.0)*40.0,
						  ofNoise(v1.y/3.0)*40.0,
						  ofNoise(v1.z/3.0)*40.0);

				ofVec3f vn1 = head[i] + vn;
				ofVec3f vn2 = head[i] - vn;

				verts_shape.push_back(ofVec3f(vn1));
				verts_shape.push_back(ofVec3f(vn2));
			}else{
//				verts_shape.push_back(ofVec3f(head[i]));
			}
		}
	}

}

void KsmrTrail::setColor(ofFloatColor c){
	col = c;
}

void KsmrTrail::setWidth(float w){
	width = w;
}

void KsmrTrail::draw(){
	ofSetColor(col);

	if ((currentType == KSMR_TRAIL_NORMAL) ||
		(currentType == KSMR_TRAIL_RIBBON)){
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &verts_shape[0]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, verts_shape.size());
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	if (currentType == KSMR_TRAIL_MESH){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &verts_shape[0]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, verts_shape.size());
		glDisableClientState(GL_VERTEX_ARRAY);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (currentType == KSMR_TRAIL_LINE_THIN){
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &head[0]);
		glDrawArrays(GL_LINE_STRIP, 0, numVerts);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

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
	numVerts = ofClamp(num, 0, NUM_VERTS_MAX);
}

void KsmrTrail::setHeadAttenuation(float att){
	head_atten = att;
}

void KsmrTrail::setType(KsmrTrailType type){
	currentType = type;
}