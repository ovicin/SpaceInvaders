#include "testApp.h"


void testApp::setup(){

	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);
	ofEnableAlphaBlending();

	ofSetCircleResolution(33);
	ofDisableArbTex();
/*
	startup.loadSound("start.wav");
	launch.loadSound("launch.wav");
	explode.loadSound("explode.wav");
	empty.loadSound("empty.wav");
*/	
	logo.loadImage("logo.png");
	logo.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	startButton.loadImage("startButton.png");
	startButton.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);


	font.loadFont("standard-07-55.ttf", 24, false, false);


	// game ////

	aliens.reset();

	// explosions

	MEDIA_LOAD_TEXTURE("smoke2.png", TEX_SMOKE);
	MEDIA_GET_TEXURE(TEX_SMOKE)->setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

	MEDIA_LOAD_TEXTURE("fire.png", TEX_FIRE);
	MEDIA_GET_TEXURE(TEX_FIRE)->setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

	MEDIA_LOAD_TEXTURE("explosion.png", TEX_EXPLOSION);
	MEDIA_GET_TEXURE(TEX_EXPLOSION)->setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

	e.setup( MEDIA_GET_TEXURE(TEX_SMOKE), MEDIA_GET_TEXURE(TEX_FIRE), MEDIA_GET_TEXURE(TEX_EXPLOSION) );
	e.setSmokeProperties(
						 5,					//random spawn pos offset from debris
						 ofVec2f(0,-50),	//smoke particles speed in pix / sec
						 ofVec2f(150,0),		//smoke particles acc in pix / sec
						 0.9					//life in seconds
						 );

	strength = 400;
	numP = 10;
	friction = 0.94;
	life = 0.9;
	offset = 0;
	spawnOffset = 5;
	smokeLife = 0.9;
	gravity = 200;


	///////////
#ifdef USE_REMOTE_CAMERA
	remoteCam.initGrabber(640,480);
	remoteCam.start();
	remoteCam.setRequestedImageType(OF_IMAGE_GRAYSCALE);
	remoteCam.setRequestedCompressionQuality( 90 );//jpeg, [0..100]
#endif

	laser.setup(ofRectangle(0,0, ofGetWidth(), ofGetHeight()), this, 640, 480, OF_IMAGE_GRAYSCALE);

	state = START_SCREEN;
	state = PLAYING;

	//graffiti
	currentLine = -1;

	//ofSetWindowPosition(-800,0);
	//ofSetFullscreen(true);
}


void testApp::update(){

	float dt = 1/60.;


	///////////////

#ifdef USE_REMOTE_CAMERA
	remoteCam.update();

	if(remoteCam.isFrameNew()){
		laser.update( remoteCam.getPixels() );
	}
#endif

	/////////////////



	switch (state) {

		case PLAYING:{

			e.setSmokeProperties(
								 spawnOffset,					//random spawn pos offset from debris
								 ofVec2f(0,-50),	//smoke particles speed in pix / sec
								 ofVec2f(50,0),	//smoke particles acc in pix / sec
								 smokeLife					//life in seconds
								 );

			e.update(1./60.);


			// GAME OVER ///////////

			if ( false ){
				gameOverTimer += dt;
				if (gameOverTimer > GAME_OVER_TIME){
					gameOver();
				}
			}else{
				gameOverTimer = 0.0;
			}

			// NEXT LEVEL ///////////
			if (false){
				nextLevel();
			}

			// GAME UPDATE //////////
			aliens.update();


		}break;

		default:
			break;
	}
}



void testApp::draw(){

	//ofShowCursor();
	ofSetLineWidth(LINE_WIDTH);

	ofSetColor(255, 128);
	laser.draw();

	if (state == PLAYING){

		ofSetColor(255);

		e.drawMesh();

		aliens.draw();


		ofSetColor(255,0,0);
		font.drawString( "LEVEL: " + ofToString(currentLevel+1), 22,40);
	}

	if (state == START_SCREEN){

		ofNoFill();
		ofSetColor(0,255,0);

		for(int i = 0; i < lines.size(); i++){
			ofBeginShape();
			for(int j = 0; j < lines[i].size(); j++){
				ofVertex(lines[i][j].x, lines[i][j].y);
			}
			ofEndShape();
		}

		ofFill();

		ofSetColor(255);
		logo.draw(ofGetWidth()/2 - logo.getWidth()/2, ofGetHeight()/2 - logo.getHeight() );
		startButton.draw(START_BUTTON_POS);
	}

}

void testApp::gameOver(){

	state = START_SCREEN;
	lines.clear();
	currentLine = -1;
	e.stopPostExplosionSmoke();

}


void testApp::nextLevel(){

	startup.play();
	e.stopPostExplosionSmoke();
	state = PLAYING;

}


void testApp::exit(){
	remoteCam.close();
}


void testApp::keyPressed(int key){

	if(key==' ')ofToggleFullscreen();
}


void testApp::keyReleased(int key){

}


void testApp::mouseMoved(int x, int y){

}


void testApp::mousePressed(int x, int y, int button){

	if(state==START_SCREEN){
		currentLine++;
		vector<ofPoint> v;
		lines.push_back( v );
		lines[currentLine].push_back( ofVec2f(x ,y ));
	}

	if(state==PLAYING){
		aliens.hitTest( ofVec2f(x ,y ) );
	}
}

void testApp::mouseDragged(int x, int y, int button){

	if(state==START_SCREEN){
		lines[currentLine].push_back( ofVec2f(x ,y ));
	}
}



void testApp::mouseReleased(int x, int y, int button){

	ofVec2f target = ofVec2f(x,y);

	if(state==START_SCREEN){

		ofRectangle startb = ofRectangle(START_BUTTON_POS);
		if( startb.inside(x, y)){
			currentLevel = 0;
			nextLevel();
		}else{

			lines[currentLine].push_back( ofVec2f(x ,y ));
		}
	}

	if(state==PLAYING){
	}
}



