#pragma once

#include "ofMain.h"
#include "Obj2D.h"
#include "Constants.h"
#include "LaserPointer.h"
#include "ofxRemoteCameraClient.h"

#include "AlienCluster.h"
#include "Explosion.h"



class testApp : public ofBaseApp{

	enum gameState{PLAYING, START_SCREEN, END_LEVEL};

	public:

		void setup();
		void update();
		void draw();
		void exit();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		void nextLevel();
		void gameOver();
		float gameOverTimer;

		Explosion e;


		gameState state;
		int currentLevel;
	
		ofImage logo;
		ofImage startButton;

		ofSoundPlayer startup, launch, explode, empty;

		ofTrueTypeFont font;	

		///////////
		
		ofxRemoteCameraClient	remoteCam;
		LaserPointer			laser;
		AlienCluster			aliens;


	//GRAFFITI

	int currentLine;
	vector< vector<ofPoint> > lines;

	//////////

	//expolosions

	float strength;
	float numP;
	float friction;
	float life;
	float offset;
	float spawnOffset;
	float smokeLife;
	float gravity;

};
