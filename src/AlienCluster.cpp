//
//  AlienCluster.cpp
//  SpaceInvaders
//
//  Created by Oriol Ferrer Mesià on 26/04/13.
//
//

#include "AlienCluster.h"


AlienCluster::AlienCluster(){

	reset();
}


void AlienCluster::reset(){

	stepDown = 0;
	direction = 1;
	WALK_ALIENS{
		allAliens[i][j].reset();
		allAliens[i][j].setup(NULL, NULL);
		ofRectangle r = ofRectangle(
									i * (ALIEN_W + ALIEN_SPACING_W) + ALIEN_SCREEN_GAP,
									j * (ALIEN_H + ALIEN_SPACING_H) + ALIEN_INITIAL_V ,
									ALIEN_W,
									ALIEN_H
									);
		allAliens[i][j].set( r );
	}

	ALIEN_H_VELOCITY = 0.2;
	stepDown = 0;
	direction = 1;

}


void AlienCluster::updateBlock(){

	float minX = FLT_MAX;
	float maxX = FLT_MIN;
	float minY = FLT_MAX;
	float maxY = FLT_MIN;
	WALK_ALIENS{
		if(allAliens[i][j].isAlive()){
			if ( allAliens[i][j].x < minX) minX = allAliens[i][j].x;
			if ( allAliens[i][j].x > maxX) maxX = allAliens[i][j].x;
			if ( allAliens[i][j].y < minY) minY = allAliens[i][j].y;
			if ( allAliens[i][j].y > maxY) maxY = allAliens[i][j].y;
		}
	}
	block.x = minX;
	block.y = minY;
	block.width = maxX - minX + ALIEN_W;
	block.height = maxY -  minY + ALIEN_H;
}


void AlienCluster::update(){

	if (block.x + block.width > ofGetWidth() - ALIEN_SCREEN_GAP){
		direction *= -1;
		stepDown = ALIEN_STEP_DOWN;
		ALIEN_H_VELOCITY *= ALIEN_SPEEDUP;
	}

	if (block.x < ALIEN_SCREEN_GAP){
		direction *= -1;
		stepDown = ALIEN_STEP_DOWN;
		ALIEN_H_VELOCITY *= ALIEN_SPEEDUP;
	}


	WALK_ALIENS{
		allAliens[i][j].update( ofVec2f(direction * ALIEN_H_VELOCITY, stepDown) );
	}

	updateBlock();

	stepDown = 0;

}


void AlienCluster::draw(){

	ofNoFill();
	ofSetColor(255,0,0);
		ofRect(block);
	ofFill();

	ofSetColor(255);
	WALK_ALIENS{
		allAliens[i][j].draw();
	}
}


void AlienCluster::hitTest( ofVec2f hit){

	WALK_ALIENS{
		if( allAliens[i][j].hitTest( hit ) ){
			allAliens[i][j].kill();
		}
	}
}


