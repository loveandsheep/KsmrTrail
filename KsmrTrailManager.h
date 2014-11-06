//
//  KsmrTrailManager.h
//  KsmrTailTest
//
//  Created by Ovis aries on 2014/10/23.
//
//

#ifndef __KsmrTailTest__KsmrTrailManager__
#define __KsmrTailTest__KsmrTrailManager__

#include "ofMain.h"
#include "KsmrTrail.h"

class KsmrTrailManager{
public:
	void setup(int numTrail,ofVec3f pos);
	void update(ofVec3f target);
	void draw();

	vector<KsmrTrail> trails;
};

#endif /* defined(__KsmrTailTest__KsmrTrailManager__) */
