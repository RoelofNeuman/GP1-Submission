/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
static cFontMgr* theFontMgr = cFontMgr::getInstance();
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
static cButtonMgr* thebuttonMgr = cButtonMgr::getInstance(); //for searching buttons lab10


/*
=================================================================================
Constructor
=================================================================================
*/
cGame::cGame()
{

}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}

//function that spawns an enemy2 bullet for enemy2 class
void cGame::fireEnemyBullet1(int enemyvariable)
{
		theEnemyBullets.push_back(new cEnemyBullet);
		int numEnemyBullets = theEnemyBullets.size() - 1;
		theEnemyBullets[numEnemyBullets]->setSpritePos({ theEnemies[enemyvariable]->getSpritePos().x, theEnemies[enemyvariable]->getSpritePos().y });
		theEnemyBullets[numEnemyBullets]->setSpriteTranslation({ -25, -25 });
		theEnemyBullets[numEnemyBullets]->setTexture(theTextureMgr->getTexture(textureName[3]));
		theEnemyBullets[numEnemyBullets]->setSpriteDimensions(theTextureMgr->getTexture(textureName[3])->getTWidth(), theTextureMgr->getTexture(textureName[3])->getTHeight());
		theEnemyBullets[numEnemyBullets]->setEnemyBulletVelocity({ -25, -25 });
		theEnemyBullets[numEnemyBullets]->setActive(true);
		
}
//function that spawns an enemy bullet for enemy2 class
void cGame::fireEnemyBullet2(int enemyvariable)
{
		theEnemyBullets.push_back(new cEnemyBullet);
		int numEnemyBullets = theEnemyBullets.size() - 1;
		theEnemyBullets[numEnemyBullets]->setSpritePos({ theEnemies2[enemyvariable]->getSpritePos().x, theEnemies2[enemyvariable]->getSpritePos().y });
		theEnemyBullets[numEnemyBullets]->setSpriteTranslation({ -25, -25 });
		theEnemyBullets[numEnemyBullets]->setTexture(theTextureMgr->getTexture(textureName[3]));
		theEnemyBullets[numEnemyBullets]->setSpriteDimensions(theTextureMgr->getTexture(textureName[3])->getTWidth(), theTextureMgr->getTexture(textureName[3])->getTHeight());
		theEnemyBullets[numEnemyBullets]->setEnemyBulletVelocity({ -25, -25 });
		theEnemyBullets[numEnemyBullets]->setActive(true);
		
}

void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	// Get width and height of render context
	SDL_GetRendererOutputSize(theRenderer, &renderWidth, &renderHeight);
	this->m_lastTime = high_resolution_clock::now();
	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);
	
	theTextureMgr->setRenderer(theRenderer);
	theFontMgr->initFontLib();
	theSoundMgr->initMixer();

	//set game variables to starting values
	score = 0;
	health = 3;

	// Set filename
	theFile.setFileName("Data/usermap.dat");
	// Check file is available
	if (!theFile.openFile(ios::in)) //open file for input output
	{
		cout << "Could not open specified file '" << theFile.getFileName() << "'. Error " << SDL_GetError() << endl;
		fileAvailable = false;
	}
	else
	{
		cout << "File '" << theFile.getFileName() << "' opened for input!" << endl;
		fileAvailable = true;
	}

	theAreaClicked = { 0, 0 };

	// Store the textures
	textureName = { "enemy1", "enemy2", "bullet player", "nemesisPellet", "theRocket","theBackground", "ControlsExplained"};
	texturesToUse = { "Images\\enemy1.png", "Images\\enemy2.png","Images\\bullet player.png", "Images\\nemesisPellet.png", "Images\\rocketSprite.png", "Images\\background.jpg", "Images\\ControlsExplained.png"};
	for (int tCount = 0; tCount < textureName.size(); tCount++)
	{	
		theTextureMgr->addTexture(textureName[tCount], texturesToUse[tCount]);
	}
	// Create textures for Game Dialogue (text)
	fontList = { "digital", "spaceAge", "Draconian" };
	fontsToUse = { "Fonts/digital-7.ttf", "Fonts/xray.ttf", "Fonts/Draconian.ttf" };

	//stores the fonts
	for (int fonts = 0; fonts < fontList.size(); fonts++)
	{
		theFontMgr->addFont(fontList[fonts], fontsToUse[fonts], 36);
	}
	gameTextList = { "Bullet Purgatory", "Score: 0", "Health 3/3", "Game Over", "Your score: 0" };
	
	theTextureMgr->addTexture("Title", theFontMgr->getFont("Draconian")->createTextTexture(theRenderer, gameTextList[0], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));
	theTextureMgr->addTexture("Points", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, gameTextList[1], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));
	theTextureMgr->addTexture("Health", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, gameTextList[2], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));
	theTextureMgr->addTexture("GameOver", theFontMgr->getFont("Draconian")->createTextTexture(theRenderer, gameTextList[3], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));
	theTextureMgr->addTexture("PointsFinal", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, gameTextList[4], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));

	//store buttons
	btnNameList = { "exit_btn", "instructions_btn", "load_btn", "menu_btn", "play_btn", "save_btn", "settings_btn" };
	btnTexturesToUse = {"Images/Buttons/button_exit.png", "Images/Buttons/button_instructions.png", "Images/Buttons/button_load.png", "Images/Buttons/button_menu.png", "Images/Buttons/button_play.png", "Images/Buttons/button_save.png", "Images/Buttons/button_settings.png"};
	btnPos = { {400, 375}, {400, 300}, {400,300}, {50, 375}, {50,300}, {740, 500}, {400, 300} };
	
	for (int buttonCount = 0; buttonCount < btnNameList.size(); buttonCount++)
	{
		theTextureMgr->addTexture(btnNameList[buttonCount], btnTexturesToUse[buttonCount]);
	}

	for (int buttonCount = 0; buttonCount < btnNameList.size(); buttonCount++)
	{
		cButton * newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture(btnNameList[buttonCount]));
		newBtn->setSpritePos(btnPos[buttonCount]);
		newBtn->setSpriteDimensions(theTextureMgr->getTexture(btnNameList[buttonCount])->getTWidth(), theTextureMgr->getTexture(btnNameList[buttonCount])->getTHeight());
		thebuttonMgr->add(btnNameList[buttonCount], newBtn);
	}


	theGameState = MENU;
	theBtnType = EXIT;




	// Load game sounds
	soundList = { "theme", "shot", "explosion", "click", "enemyShot", "friendlyhit"};
	soundTypes = { MUSIC, SFX, SFX, SFX, SFX, SFX };
	soundsToUse = { "Audio/game music.wav", "Audio/shot007.wav", "Audio/explosion2.wav", "Audio/ButtonClick.wav", "Audio/enemyshot.wav", "Audio/friendlyhit.wav"};
	for (int sounds = 0; sounds < soundList.size(); sounds++)
	{
		theSoundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}

	theSoundMgr->getSnd("theme")->play(-1);

	//renders the background
	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());

	//renders the rocket
	theRocket.setSpritePos({ 450, 600 });
	theRocket.setTexture(theTextureMgr->getTexture("theRocket"));
	theRocket.setSpriteDimensions(theTextureMgr->getTexture("theRocket")->getTWidth(), theTextureMgr->getTexture("theRocket")->getTHeight());
	theRocket.setRocketVelocity({ 0, 0 });

	
	
	
}



void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	 loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);
	spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
	

	//SDL_RenderClear(theRenderer);
	switch (theGameState)
	{
	//renders everything needed for the menu/ opening screen
	case MENU:
	{
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		// Render the Title
		cTexture* tempTextTexture = theTextureMgr->getTexture("Title");
		SDL_Rect pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		FPoint scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
	
		thebuttonMgr->getBtn("exit_btn")->setSpritePos({ 50, 450 });

		thebuttonMgr->getBtn("play_btn")->render(theRenderer, &thebuttonMgr->getBtn("play_btn")->getSpriteDimensions(), &thebuttonMgr->getBtn("play_btn")->getSpritePos(), thebuttonMgr->getBtn("play_btn")->getSpriteScale());
		thebuttonMgr->getBtn("exit_btn")->render(theRenderer, &thebuttonMgr->getBtn("exit_btn")->getSpriteDimensions(), &thebuttonMgr->getBtn("exit_btn")->getSpritePos(), thebuttonMgr->getBtn("exit_btn")->getSpriteScale());
		thebuttonMgr->getBtn("load_btn")->render(theRenderer, &thebuttonMgr->getBtn("load_btn")->getSpriteDimensions(), &thebuttonMgr->getBtn("load_btn")->getSpritePos(), thebuttonMgr->getBtn("load_btn")->getSpriteScale());
		thebuttonMgr->getBtn("load_btn")->setSpritePos({ 50, 375 });
	
		tempTexture = theTextureMgr->getTexture("ControlsExplained");
		pos = { 350, 450, tempTexture->getTextureRect().w, tempTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTexture->renderTexture(theRenderer, tempTexture->getTexture(), &tempTexture->getTextureRect(), &pos, scale);
	}


	break;

	//renders everything needed when the game is running ie the game state is playing
	case PLAYING:
	{
		SDL_RenderClear(theRenderer);
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());


		// Render the Title
		cTexture* tempTextTexture = theTextureMgr->getTexture("Title");
		SDL_Rect pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		FPoint scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		//render the buttons 
		thebuttonMgr->getBtn("exit_btn")->setSpritePos({ 740, 650 });
		thebuttonMgr->getBtn("exit_btn")->render(theRenderer, &thebuttonMgr->getBtn("exit_btn")->getSpriteDimensions(), &thebuttonMgr->getBtn("exit_btn")->getSpritePos(), thebuttonMgr->getBtn("exit_btn")->getSpriteScale());
		thebuttonMgr->getBtn("save_btn")->setSpritePos({ 740, 575 });
		thebuttonMgr->getBtn("save_btn")->render(theRenderer, &thebuttonMgr->getBtn("save_btn")->getSpriteDimensions(), &thebuttonMgr->getBtn("save_btn")->getSpritePos(), thebuttonMgr->getBtn("save_btn")->getSpriteScale());

		// render the rocket
		theRocket.render(theRenderer, &theRocket.getSpriteDimensions(), &theRocket.getSpritePos(), theRocket.getSpriteRotAngle(), &theRocket.getSpriteCentre(), theRocket.getSpriteScale());
		

		// Render each bullet in the vector array
		for (int draw = 0; draw < theBullets.size(); draw++)
		{
			theBullets[draw]->render(theRenderer, &theBullets[draw]->getSpriteDimensions(), &theBullets[draw]->getSpritePos(), theBullets[draw]->getSpriteRotAngle(), &theBullets[draw]->getSpriteCentre(), theBullets[draw]->getSpriteScale());
		}

		// Render each enemy in the vector array
		for (int draw = 0; draw < theEnemies.size(); draw++)
		{
			theEnemies[draw]->render(theRenderer, &theEnemies[draw]->getSpriteDimensions(), &theEnemies[draw]->getSpritePos(), theEnemies[draw]->getSpriteRotAngle(), &theEnemies[draw]->getSpriteCentre(), theEnemies[draw]->getSpriteScale());
		}
		//render eacht enemy 2 in the vector array
		for (int draw = 0; draw < theEnemies2.size(); draw++)
		{
			theEnemies2[draw]->render(theRenderer, &theEnemies2[draw]->getSpriteDimensions(), &theEnemies2[draw]->getSpritePos(), theEnemies2[draw]->getSpriteRotAngle(), &theEnemies2[draw]->getSpriteCentre(), theEnemies2[draw]->getSpriteScale());
		}

		//render each Enemy bullets in the vector array
		for (int draw = 0; draw < theEnemyBullets.size(); draw++)
		{
			theEnemyBullets[draw]->render(theRenderer, &theEnemyBullets[draw]->getSpriteDimensions(), &theEnemyBullets[draw]->getSpritePos(), theEnemyBullets[draw]->getSpriteRotAngle(), &theEnemyBullets[draw]->getSpriteCentre(), theEnemyBullets[draw]->getSpriteScale());
		}


		//render score 
		//updates the score after it has been changed and redraws the texture
		if (scoreChanged)
		{
			gameTextList[1] = ScoreAsString.c_str();
			theTextureMgr->addTexture("Points", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, gameTextList[1], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));
			scoreChanged = false;
		}
		tempTextTexture = theTextureMgr->getTexture("Points");
		pos = { 10, 50, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		//render health once it has been changed. 
		if (healthChanged)
		{
			gameTextList[2] = healthAsString.c_str();
			theTextureMgr->addTexture("Health", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, gameTextList[2], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));
			scoreChanged = false;
		}

		tempTextTexture = theTextureMgr->getTexture("Health");
		pos = { 700, 50, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);


		SDL_RenderPresent(theRenderer);
	}
	break;
	//SDL_RenderClear(theRenderer);


	//All that renders when the game is in End state or finished
	case END:
	{
		//renders background
		//spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		cTexture* tempTextTexture = theTextureMgr->getTexture("Title");
		SDL_Rect pos = { 380, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		FPoint scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		//renders the text game over.
		tempTextTexture = theTextureMgr->getTexture("GameOver");
		pos = { 410, 200, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		gameTextList[1] = ScoreAsString.c_str();
		theTextureMgr->addTexture("Points", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, gameTextList[1], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));
		tempTextTexture = theTextureMgr->getTexture("Points");
		pos = { 315, 275, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);


		//renders buttons
		thebuttonMgr->getBtn("menu_btn")->setSpritePos({450, 500 });
		thebuttonMgr->getBtn("menu_btn")->render(theRenderer, &thebuttonMgr->getBtn("menu_btn")->getSpriteDimensions(), &thebuttonMgr->getBtn("menu_btn")->getSpritePos(), thebuttonMgr->getBtn("menu_btn")->getSpriteScale());
		thebuttonMgr->getBtn("exit_btn")->setSpritePos({ 450, 575 });
		thebuttonMgr->getBtn("exit_btn")->render(theRenderer, &thebuttonMgr->getBtn("exit_btn")->getSpriteDimensions(), &thebuttonMgr->getBtn("exit_btn")->getSpritePos(), thebuttonMgr->getBtn("exit_btn")->getSpriteScale());
		
	}
	break;

	case QUIT:
	{
		loop = false;
	
	}
	break;
	default:
		break;
	}

	SDL_RenderPresent(theRenderer);

}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{

	SDL_RenderPresent(theRenderer);
}

void cGame::update()
{

}

void cGame::update(double deltaTime)
{
	switch (theGameState)
	{
	//all functionality that has to be checked on the opening screen/menu
	case MENU:
	{
		//deletes game variabes (health and score so it can redraw)
		health = 3;
		if (theTextureMgr->getTexture("Health") != NULL)
		{
			theTextureMgr->deleteTexture("Health");
		}
		string theHealth = to_string(health);
		healthAsString = "Health " + theHealth + "/3";
		healthChanged = true;

		score = 0;
		if (theTextureMgr->getTexture("Points") != NULL)
		{
			theTextureMgr->deleteTexture("Points");
		}
		string thescore = to_string(score);
		ScoreAsString = "score: " + thescore;
		scoreChanged = true;

		if (theGameState == PLAYING)
		{
			//removes all enemies so they can be reset
			vector<cEnemy*>::iterator enemyIterator = theEnemies.begin();
			while (enemyIterator != theEnemies.end())
			{
				enemyIterator = theEnemies.erase(enemyIterator);
			}

			// Create vector array of textures for the enemy class
			for (int enemy = 0; enemy < 10; enemy++)
			{
				theEnemies.push_back(new cEnemy);
				theEnemies[enemy]->setSpritePos({ 100 * enemy, 150 });
				theEnemies[enemy]->setSpriteTranslation({ 100, 0 });

				theEnemies[enemy]->setTexture(theTextureMgr->getTexture(textureName[0]));
				theEnemies[enemy]->setSpriteDimensions(theTextureMgr->getTexture(textureName[0])->getTWidth(), theTextureMgr->getTexture(textureName[0])->getTHeight());
				theEnemies[enemy]->setEnemyVelocity({ 0, 0 });
				theEnemies[enemy]->setActive(true);
			}

			//creates vector array of textures for the enemy 2 class
			for (int enemy2 = 0; enemy2 < 6; enemy2++)
			{
				theEnemies2.push_back(new cEnemy2);
				theEnemies2[enemy2]->setSpritePos({ 100 * enemy2, 50 });
				theEnemies2[enemy2]->setSpriteTranslation({ 0, 100 });

				theEnemies2[enemy2]->setTexture(theTextureMgr->getTexture(textureName[1]));
				theEnemies2[enemy2]->setSpriteDimensions(theTextureMgr->getTexture(textureName[1])->getTWidth(), theTextureMgr->getTexture(textureName[1])->getTHeight());
				theEnemies2[enemy2]->setEnemy2Velocity({ 0, 0 });
				theEnemies2[enemy2]->setActive(true);
			}
		}

		//checks if buttons are pressend and updates the gamestate to the relevant state
		theGameState = thebuttonMgr->getBtn("exit_btn")->update(theGameState, QUIT, theAreaClicked);
		theGameState = thebuttonMgr->getBtn("play_btn")->update(theGameState, PLAYING, theAreaClicked);
		theGameState = thebuttonMgr->getBtn("load_btn")->update(theGameState, LOADMAP, theAreaClicked);
		
		if (fileAvailable && theGameState == LOADMAP)
		{
			theTileMap.initialiseMapFromFile(&theFile);
			theGameState = PLAYING;
			theAreaClicked = { 0, 0 };
		}
	}
	break;

	//all functionality that has to be checked whiile the game is running
	case PLAYING:
	{
		theGameState = thebuttonMgr->getBtn("exit_btn")->update(theGameState, END, theAreaClicked);

		theGameState = thebuttonMgr->getBtn("save_btn")->update(theGameState, SAVEMAP, theAreaClicked);
		if (theGameState == SAVEMAP)
		{
			// Check file is available
			if (!theFile.openFile(ios::out)) //open file for output
			{
				cout << "Could not open specified file '" << theFile.getFileName() << "'. Error " << SDL_GetError() << endl;
			}
			else
			{
				cout << "File '" << theFile.getFileName() << "' opened for output!" << endl;
				theTileMap.writeMapDataToFile(&theFile);
			}

		//sets the gamestate back to playing so the game continues
			theGameState = PLAYING;
			theAreaClicked = { 0, 0 };
		}



		// Update the Player Rockets position
		theRocket.update(deltaTime);

		// Update the visibility and position of each asteriod
		vector<cEnemy*>::iterator enemyIterator = theEnemies.begin();
		while (enemyIterator != theEnemies.end())
		{
			if ((*enemyIterator)->isActive() == false)
			{
				enemyIterator = theEnemies.erase(enemyIterator);
			}
			else
			{
				(*enemyIterator)->update(deltaTime);
				++enemyIterator;
			}
		}

		// Update the visibility and position of each asteriod
		vector<cEnemy2*>::iterator enemy2Iterator = theEnemies2.begin();
		while (enemy2Iterator != theEnemies2.end())
		{
			if ((*enemy2Iterator)->isActive() == false)
			{
				enemy2Iterator = theEnemies2.erase(enemy2Iterator);
			}
			else
			{
				(*enemy2Iterator)->update(deltaTime);
				++enemy2Iterator;
			}
		}


		// Update the visibility and position of each bullet
		vector<cBullet*>::iterator bulletIterartor = theBullets.begin();
		while (bulletIterartor != theBullets.end())
		{
			if ((*bulletIterartor)->isActive() == false)
			{
				bulletIterartor = theBullets.erase(bulletIterartor);
			}
			else
			{
				(*bulletIterartor)->update(deltaTime);
				++bulletIterartor;
			}
		}

		// Update the visibility and position of each Enemybullet
		vector<cEnemyBullet*>::iterator enemyBulletIterartor = theEnemyBullets.begin();
		while (enemyBulletIterartor != theEnemyBullets.end())
		{
			if ((*enemyBulletIterartor)->isActive() == false)
			{
				enemyBulletIterartor = theEnemyBullets.erase(enemyBulletIterartor);
			}
			else
			{
				(*enemyBulletIterartor)->update(deltaTime);
				++enemyBulletIterartor;
			}
		}


		//checks if the rocket is directly in front of enemy 1 and then fires
		for (int firecheck = 0; firecheck < theEnemies.size(); ++firecheck)
		{
			if (theRocket.getSpritePos().x == theEnemies[firecheck]->getSpritePos().x)
			{
				if (theEnemies[firecheck] != NULL)
				{
					fireEnemyBullet1(firecheck);
					theSoundMgr->getSnd("enemyShot")->play(0);
				}
			}
		}
		//checks if the rocket is in front enemy2 and then fires

		for (int firecheck = 0; firecheck < theEnemies2.size(); ++firecheck)
		{
			if (theEnemies2[firecheck] != NULL)
			{
				if (theRocket.getSpritePos().x == theEnemies2[firecheck]->getSpritePos().x)
				{
					fireEnemyBullet2(firecheck);
					theSoundMgr->getSnd("enemyShot")->play(0);
				}
			}
		}

		//checks if enemy 2 is too low and if so gets rid of them to save power
		for (int tooLow = 0; tooLow < theEnemies2.size(); ++tooLow)
		{
			if (theEnemies2[tooLow]->getSpritePos().y >= (renderHeight - 80))
			{
				if (theEnemies2[tooLow] != NULL)
				{
					theEnemies2[tooLow]->setActive(false);
				}

			}
		}
		//when the first class of enemies are all gone, a new wave will spawn
		if (theEnemies.size() == 0)
		{
			for (int enemy = 0; enemy < 9; enemy++)
			{
				theEnemies.push_back(new cEnemy);
				theEnemies[enemy]->setSpritePos({ 100 * enemy, 150 });
				theEnemies[enemy]->setSpriteTranslation({ 100, 0 });
				theEnemies[enemy]->setTexture(theTextureMgr->getTexture(textureName[0]));
				theEnemies[enemy]->setSpriteDimensions(theTextureMgr->getTexture(textureName[0])->getTWidth(), theTextureMgr->getTexture(textureName[0])->getTHeight());
				theEnemies[enemy]->setEnemyVelocity({ 0, 0 });
				theEnemies[enemy]->setActive(true);
			}
		}

		//when the second class of enemies are all gone, a new wave will spawn
		if (theEnemies2.size() == 0)
		{

			for (int enemy = 0; enemy < 5; enemy++)
			{
				theEnemies2.push_back(new cEnemy2);
				theEnemies2[enemy]->setSpritePos({ 100 * enemy, 50 });
				theEnemies2[enemy]->setSpriteTranslation({ 0, 100 });
				theEnemies2[enemy]->setTexture(theTextureMgr->getTexture(textureName[1]));
				theEnemies2[enemy]->setSpriteDimensions(theTextureMgr->getTexture(textureName[1])->getTWidth(), theTextureMgr->getTexture(textureName[1])->getTHeight());
				theEnemies2[enemy]->setEnemy2Velocity({ 0, 0 });
				theEnemies2[enemy]->setActive(true);
			}
		}

		//once health is 0 the gamestate is changed to end which means gamever
		if (health <= 0)
		{
			theGameState = END;
		}

		/*
		==============================================================
		| Check for collisions
		==============================================================
		*/
		for (vector<cBullet*>::iterator bulletIterartor = theBullets.begin(); bulletIterartor != theBullets.end(); ++bulletIterartor)
		{
			//(*bulletIterartor)->update(deltaTime);
			for (vector<cEnemy*>::iterator enemyIterator = theEnemies.begin(); enemyIterator != theEnemies.end(); ++enemyIterator)
			{
				if ((*enemyIterator)->collidedWith(&(*enemyIterator)->getBoundingRect(), &(*bulletIterartor)->getBoundingRect()))
				{
					// if a collision set the bullet and enemies to false
					score += 10;
					if (theTextureMgr->getTexture("Points") != NULL)
					{
						theTextureMgr->deleteTexture("Points");
					}

					string thescore = to_string(score);   
					ScoreAsString = "score: " + thescore;  

					scoreChanged = true;
					if ((*enemyIterator) != NULL)
					{
						(*enemyIterator)->setActive(false);
					}

					if ((*bulletIterartor) != NULL)
					{
						(*bulletIterartor)->setActive(false);
					}

					//saving the score for the file handler and TileMap
					string scoreAsStringForFile = ScoreAsString;

					theSoundMgr->getSnd("explosion")->play(0);
				}

				//this checks if an enemy collides with the player rocket
				if ((*enemyIterator)->collidedWith(&(*enemyIterator)->getBoundingRect(), &theRocket.getBoundingRect()))
				{
					if ((*enemyIterator) != NULL)
					{
						(*enemyIterator)->setActive(false);
					}
				}
			}

			//since the second enemy class is a different class there's more coliision detetction needed.
			for (vector<cEnemy2*>::iterator enemy2Iterator = theEnemies2.begin(); enemy2Iterator != theEnemies2.end(); ++enemy2Iterator)
			{
				if ((*enemy2Iterator)->collidedWith(&(*enemy2Iterator)->getBoundingRect(), &(*bulletIterartor)->getBoundingRect()))
				{
					// if a collision set the bullet and enemies to false
					score += 5;
					if (theTextureMgr->getTexture("Points") != NULL)
					{
						theTextureMgr->deleteTexture("Points");
					}

					string thescore = to_string(score);
					ScoreAsString = "score: " + thescore;

					scoreChanged = true;

					if ((*enemy2Iterator) != NULL)
					{
						(*enemy2Iterator)->setActive(false);
					}

					if ((*bulletIterartor) != NULL)
					{
						(*bulletIterartor)->setActive(false);
					}
					theSoundMgr->getSnd("explosion")->play(0);
				}
				//this checks if an enemy2 collides with the player rocket
				if((*enemy2Iterator)->collidedWith(&(*enemy2Iterator)->getBoundingRect(), &theRocket.getBoundingRect()))
				{ 
					if ((*enemy2Iterator) != NULL)
					{
						(*enemy2Iterator)->setActive(false);
					}
				}
			}	
		}

		//collision detection for the player rocket with enemy bullets and enemy ships
		for (vector<cEnemyBullet*>::iterator enemyBulletIterartor = theEnemyBullets.begin(); enemyBulletIterartor != theEnemyBullets.end(); ++enemyBulletIterartor)
		{
			if (theRocket.collidedWith(&theRocket.getBoundingRect(), &(*enemyBulletIterartor)->getBoundingRect()))
			{
				//if a collision set the bullet and enemies to false

				(*enemyBulletIterartor)->setActive(false);
				health --;
				if (theTextureMgr->getTexture("Health") != NULL)
				{
					theTextureMgr->deleteTexture("Health");
				}

				theSoundMgr->getSnd("friendlyhit")->play(0);

				string theHealth = to_string(health);
				healthAsString = "Health " + theHealth +"/3"; 
				healthChanged = true;
				
			}
		}
	}
		break;
	case END:
	{	//the end screen just needs to check to things wether exit or menu is clicked
		
		



		//renders the points for display at the end
		

		//checks if buttons are clicked
		theGameState = thebuttonMgr->getBtn("exit_btn")->update(theGameState, QUIT, theAreaClicked);
		
		theGameState = thebuttonMgr->getBtn("menu_btn")->update(theGameState, MENU, theAreaClicked);
	}
	break;

	}
}

bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}

		switch (event.type)
		{
			///checks where the user clicks and stores it for button checks
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					
					theAreaClicked = {event.motion.x, event.motion.y};
					
				}
				break;
				case SDL_BUTTON_RIGHT:
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
				}
				break;
				case SDL_BUTTON_RIGHT:
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEMOTION:
			break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					theLoop = false;
					break;
				case SDLK_DOWN:
				{
					//moves the rocket down when the user presses the down key
					if (theRocket.getSpritePos().y < (renderHeight - theRocket.getSpritePos().h))
					{
						theRocket.setRocketVelocity({ 0, 250 });
					}
				}
				break;

				case SDLK_UP:
				{
					//moves the rocket up when the user presses the up key
					if (theRocket.getSpritePos().y > 0)
					{
						theRocket.setRocketVelocity({ 0, -250 });
					}
				}
				break;
				case SDLK_RIGHT:
				{
					//moves the rocket to the right when the user presses the righ key
					if (theRocket.getSpritePos().x < (renderWidth - theRocket.getSpritePos().w))
					{
						theRocket.setRocketVelocity({ 250, 0 });
					}
				}
				break;

				case SDLK_LEFT:
				{
					//moves the rocket to the left when the user presses the left key
					if (theRocket.getSpritePos().x > 0)
					{
						theRocket.setRocketVelocity({ -250, 0 });
					}
				}
				break;
				case SDLK_SPACE:
				{
					//spawns a bullet when the user presses the spacebar
					theBullets.push_back(new cBullet);
					int numBullets = theBullets.size() - 1;
					theBullets[numBullets]->setSpritePos({ theRocket.getBoundingRect().x, theRocket.getBoundingRect().y  });
					theBullets[numBullets]->setSpriteTranslation({ 75, 75 });
					theBullets[numBullets]->setTexture(theTextureMgr->getTexture("bullet player"));
					theBullets[numBullets]->setSpriteDimensions(theTextureMgr->getTexture("bullet player")->getTWidth(), theTextureMgr->getTexture("bullet player")->getTHeight());
					theBullets[numBullets]->setBulletVelocity({ 75, 75 });

					theBullets[numBullets]->setActive(true);
					cout << "Bullet added to Vector at position - x: " << theRocket.getBoundingRect().x << " y: " << theRocket.getBoundingRect().y << endl;
				}
				theSoundMgr->getSnd("shot")->play(0);
				break;
				default:
					break;
				}

			default:
				break;
		}

	}
	return theLoop;
}

double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}

