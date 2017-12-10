 #ifndef _GAME_H
#define _GAME_H

/*
==================================================================================
cGame.h
==================================================================================
*/

#include <SDL.h>

// Game specific includes
#include "asteroidsGame.h"


using namespace std;

class cGame
{
public:
	cGame();

	void initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void cleanUp(SDL_Window* theSDLWND);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre);
	void update();
	void update(double deltaTime);
	bool getInput(bool theLoop);
	double getElapsedSeconds();

	static cGame* getInstance();

	void fireEnemyBullet1(int enemyvariable);

	void fireEnemyBullet2(int enemyvariable);

private:

	static cGame* pInstance;
	// for framerates
	time_point< high_resolution_clock > m_lastTime;
	time_point< high_resolution_clock > m_CurrentTime;
	duration< double > deltaTime;
	bool loop;

	// Sprites for displaying background and rocket textures
	cSprite spriteBkgd;
	cRocket theRocket;
	cEnemy theEnemy;
	cBullet theBullet;
	cEnemyBullet theEnemyBullet;
	// game related variables
	vector<LPCSTR> textureName;
	vector<LPCSTR> textName;
	vector<LPCSTR> texturesToUse;
	vector<cEnemy*> theEnemies;
	vector<cEnemy2*> theEnemies2;
	vector<cBullet*> theBullets;
	vector<cEnemyBullet*> theEnemyBullets;
	// Fonts to use
	vector<LPCSTR> fontList;
	vector<LPCSTR> fontsToUse;
	// Text for Game
	vector<LPCSTR> gameTextList;
	// Game Sounds
	vector<LPCSTR> soundList;
	vector<soundType> soundTypes;
	vector<LPCSTR> soundsToUse;
	
	//menu and button things
	vector<LPCSTR> btnNameList; //menu
	vector<LPCSTR> btnTexturesToUse;
	vector<SDL_Point> btnPos;
	vector<cButton> theButtons;
	

	SDL_Rect pos;
	FPoint scale;

	
	
	
	// Game objects
	// Define the elements and there position in/on the array/map
	int renderWidth, renderHeight;
	
	
	gameState theGameState;// lab 10
	btnTypes theBtnType;//
	cTexture* tempTexture;//
	SDL_Point theAreaClicked;//

	SDL_Point theTileClicked; //
	SDL_Point mapTileClicked;//
	SDL_Point aRect;// lab10

	bool fileAvailable;
	cFileHandler theFile;
	cTileMap theTileMap;

	//score related variables
	int score;
	string ScoreAsString;
	bool scoreChanged;

	
	
};

#endif
