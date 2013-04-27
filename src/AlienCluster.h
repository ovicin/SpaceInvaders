//
//  AlienCluster.h
//  SpaceInvaders
//
//  Created by Oriol Ferrer Mesià on 26/04/13.
//
//

#ifndef __SpaceInvaders__AlienCluster__
#define __SpaceInvaders__AlienCluster__

#include <iostream>

#include "ofMain.h"
#include "Obj2D.h"
#include "Alien.h"
#include "Constants.h"

#define WALK_ALIENS 	for(int j = 0; j < NUM_ALIEN_ROWS; j++)for(int i = 0; i < NUM_ALIEN_COLUMNS; i++) 


class AlienCluster{

public:

	AlienCluster();
	void reset();
	void update();
	void draw();
	void hitTest( ofVec2f hit);


private:

	void updateBlock();
	//vector< vector<Alien*> > allAliens;
	Alien allAliens[NUM_ALIEN_COLUMNS][NUM_ALIEN_ROWS];

	ofRectangle			block;
	int					direction; // -1 | 1
	int					stepDown;	// [0.. GameOver]

	float				ALIEN_H_VELOCITY;


};


#endif /* defined(__SpaceInvaders__AlienCluster__) */
