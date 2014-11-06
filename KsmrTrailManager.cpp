//
//  KsmrTrailManager.cpp
//  KsmrTailTest
//
//  Created by Ovis aries on 2014/10/23.
//
//

#include "KsmrTrailManager.h"

void KsmrTrailManager::setup(int numTrail,ofVec3f pos){
	trails.assign(numTrail, KsmrTrail());
	for (int i = 0;i < trails.size();i++){
		trails[i].setup(pos);
	}
}

void KsmrTrailManager::update(ofVec3f target){
	for (int i = 0;i < trails.size();i++){
		trails[i].update(target);
	}
}

void KsmrTrailManager::draw(){
	for (int i = 0;i < trails.size();i++){
		trails[i].draw();
	}
}