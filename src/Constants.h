//
//  Constants.h
//  opencvExample
//
//  Created by Oriol Ferrer Mesià on 22/04/13.
//
//

#ifndef opencvExample_Constants_h
#define opencvExample_Constants_h

//#define USE_REMOTE_CAMERA


#define ALIEN_W					60
#define ALIEN_H					40
#define ALIEN_SPACING_W			12
#define ALIEN_SPACING_H			22

#define NUM_ALIEN_COLUMNS		12
#define NUM_ALIEN_ROWS			5

#define ALIEN_INITIAL_V			50
#define ALIEN_STEP_DOWN			33
#define ALIEN_SCREEN_GAP		30
#define ALIEN_SPEEDUP			1.33

#define EXPLOSION_DURATION		2.5

#define START_BUTTON_POS		ofGetWidth()/2 - startButton.getWidth()/2, ofGetHeight()/2 + 2 * startButton.getHeight(), startButton.getWidth(), startButton.getHeight()

#define GAME_OVER_TIME			5
#define LINE_WIDTH				3



enum TextureID{
	TEX_SMOKE, TEX_EXPLOSION, TEX_FIRE
};


#endif
