//
//  Alien.h
//  SpaceInvaders
//
//  Created by Oriol Ferrer Mesià on 26/04/13.
//
//

#ifndef SpaceInvaders_Alien_h
#define SpaceInvaders_Alien_h


#include "ofMain.h"
#include "Obj2D.h"
#include "Constants.h"


class Alien : public Obj2D{

public:

	void setup(ofImage * sprite1, ofImage * sprite2){
		reset();
	}

	void reset(){
		alive = true;
	}


	void kill(){
		alive = false;
	}

	bool isAlive(){ return alive; }

	void update(ofVec2f offset){
		time++;
		x += offset.x;
		y += offset.y;
	}

	void draw(){
		if (alive) {
			Obj2D::draw();
		}else{
			ofSetColor(0, 128);
			ofRect( x, y, width, height );
		}	
	}

	bool alive;
	int time;
	ofImage* sprite1, sprite2;

};


#endif
