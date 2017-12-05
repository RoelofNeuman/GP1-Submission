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

	score = 0;

	// Store the textures
	textureName = { "enemy1", "enemy2", "bullet player", "nemesisPellet", "theRocket","theBackground"};
	texturesToUse = { "Images\\enemy1.png", "Images\\enemy2.png","Images\\bullet player.png", "Images\\nemesisPellet.png", "Images\\rocketSprite.png", "Images\\starscape1024x768.png"};
	for (int tCount = 0; tCount < textureName.size(); tCount++)
	{	
		theTextureMgr->addTexture(textureName[tCount], texturesToUse[tCount]);
	}
	// Create textures for Game Dialogue (text)
	fontList = { "digital", "spaceAge", "Draconian" };
	fontsToUse = { "Fonts/digital-7.ttf", "Fonts/space age.ttf", "Fonts/Draconian.ttf" };
	for (int fonts = 0; fonts < fontList.size(); fonts++)
	{
		theFontMgr->addFont(fontList[fonts], fontsToUse[fonts], 36);
	}
	gameTextList = { "Bullet Purgatory", "Score: 0" };
	
	theTextureMgr->addTexture("Title", theFontMgr->getFont("Draconian")->createTextTexture(theRenderer, gameTextList[0], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));
	theTextureMgr->addTexture("Points", theFontMgr->getFont("spaceAge")->createTextTexture(theRenderer, gameTextList[1], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));
	

	// Load game sounds
	soundList = { "theme", "shot", "explosion" };
	soundTypes = { MUSIC, SFX, SFX };
	soundsToUse = { "Audio/game music.wav", "Audio/shot007.wav", "Audio/explosion2.wav" };
	for (int sounds = 0; sounds < soundList.size(); sounds++)
	{
		theSoundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}

	theSoundMgr->getSnd("theme")->play(-1);

	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());

	theRocket.setSpritePos({ 450, 600 });
	theRocket.setTexture(theTextureMgr->getTexture("theRocket"));
	theRocket.setSpriteDimensions(theTextureMgr->getTexture("theRocket")->getTWidth(), theTextureMgr->getTexture("theRocket")->getTHeight());
	theRocket.setRocketVelocity({ 0, 0 });


	// Create vector array of textures

	for (int enemy = 0; enemy < 8; enemy++)
	{
		theEnemies.push_back(new cEnemy);
		theEnemies[enemy]->setSpritePos({100 * enemy, 100});
		theEnemies[enemy]->setSpriteTranslation({ (0, 100) });
		int randEnemy = rand() % 4;
		theEnemies[enemy]->setTexture(theTextureMgr->getTexture(textureName[0]));
		theEnemies[enemy]->setSpriteDimensions(theTextureMgr->getTexture(textureName[0])->getTWidth(), theTextureMgr->getTexture(textureName[0])->getTHeight());
		theEnemies[enemy]->setEnemyVelocity({ 0, 0 });
		theEnemies[enemy]->setActive(true);
	}
	

	for (int enemy2 = 0; enemy2 < 8; enemy2++)
	{
		theEnemies2.push_back(new cEnemy2);
		theEnemies2[enemy2]->setSpritePos({ 100 * enemy2, 300 });
		theEnemies2[enemy2]->setSpriteTranslation({ (0, 100) });
		
		theEnemies2[enemy2]->setTexture(theTextureMgr->getTexture(textureName[1]));
		theEnemies2[enemy2]->setSpriteDimensions(theTextureMgr->getTexture(textureName[1])->getTWidth(), theTextureMgr->getTexture(textureName[1])->getTHeight());
		theEnemies2[enemy2]->setEnemy2Velocity({ 0, 0 });
		theEnemies2[enemy2]->setActive(true);
	}

}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	bool loop = true;

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
	// Render each enemy in the vector array
	for (int draw = 0; draw < theEnemies.size(); draw++)
	{
		theEnemies[draw]->render(theRenderer, &theEnemies[draw]->getSpriteDimensions(), &theEnemies[draw]->getSpritePos(), theEnemies[draw]->getSpriteRotAngle(), &theEnemies[draw]->getSpriteCentre(), theEnemies[draw]->getSpriteScale());
	}

	for (int draw = 0; draw < theEnemies2.size(); draw++)
	{
		theEnemies2[draw]->render(theRenderer, &theEnemies2[draw]->getSpriteDimensions(), &theEnemies2[draw]->getSpritePos(), theEnemies2[draw]->getSpriteRotAngle(), &theEnemies2[draw]->getSpriteCentre(), theEnemies[draw]->getSpriteScale());
	}


	// Render each bullet in the vector array
	for (int draw = 0; draw < theBullets.size(); draw++)
	{
		theBullets[draw]->render(theRenderer, &theBullets[draw]->getSpriteDimensions(), &theBullets[draw]->getSpritePos(), theBullets[draw]->getSpriteRotAngle(), &theBullets[draw]->getSpriteCentre(), theBullets[draw]->getSpriteScale());
	}

	//render each Enemy bullets in the vector array
	for (int draw = 0; draw < theEnemyBullets.size(); draw++)
	{
		theEnemyBullets[draw]->render(theRenderer, &theEnemyBullets[draw]->getSpriteDimensions(), &theEnemyBullets[draw]->getSpritePos(), theEnemyBullets[draw]->getSpriteRotAngle(), &theEnemyBullets[draw]->getSpriteCentre(), theEnemyBullets[draw]->getSpriteScale());
	}
	

	

	// Render the Title
	cTexture* tempTextTexture = theTextureMgr->getTexture("Title");
	SDL_Rect pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
	FPoint scale = { 1, 1 };
	tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

	//render score

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
	
	
	// render the rocket
	theRocket.render(theRenderer, &theRocket.getSpriteDimensions(), &theRocket.getSpritePos(), theRocket.getSpriteRotAngle(), &theRocket.getSpriteCentre(), theRocket.getSpriteScale());
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

	// Update the visibility and position of each bullet
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

	//attemt at enemies shooting
/*	for (int shoot = theEnemies.size; shoot = 0; shoot--);
	{
		theEnemyBullets.push_back(new cEnemyBullet);
		int numEnemyBullets = theEnemyBullets.size() - 1;
		theEnemyBullets[numEnemyBullets]->setSpritePos({ 20,20 });
		theEnemyBullets[numEnemyBullets]->setSpriteTranslation({ 75, 75 });
		theEnemyBullets[numEnemyBullets]->setTexture(theTextureMgr->getTexture("nemesisPellet"));
		theEnemyBullets[numEnemyBullets]->setSpriteDimensions(theTextureMgr->getTexture("nemesisPellet")->getTWidth(), theTextureMgr->getTexture("nemesisPellet")->getTHeight());
		theEnemyBullets[numEnemyBullets]->setEnemyBulletVelocity({ 75, 75 });

		theEnemyBullets[numEnemyBullets]->setActive(true);
		cout << "step one is doen dde";
	}
	*/




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
				if (theTextureMgr->getTexture ("Points") != NULL)
				{
					theTextureMgr->deleteTexture("Points");
				}
				

				string thescore = to_string(score);
				ScoreAsString = "score: " + thescore;

				scoreChanged = true;

				(*enemyIterator)->setActive(false);
				(*bulletIterartor)->setActive(false);
				theSoundMgr->getSnd("explosion")->play(0);
			}
		}


		for (vector<cEnemy2*>::iterator enemy2Iterator = theEnemies2.begin(); enemy2Iterator != theEnemies2.end(); ++enemy2Iterator)
		{
			if ((*enemy2Iterator)->collidedWith(&(*enemy2Iterator)->getBoundingRect(), &(*bulletIterartor)->getBoundingRect()))
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

				(*enemy2Iterator)->setActive(false);
				(*bulletIterartor)->setActive(false);
				theSoundMgr->getSnd("explosion")->play(0);
			}
		}
	}


	// Update the Rockets position
	theRocket.update(deltaTime);
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
			case SDL_MOUSEBUTTONDOWN:
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
					if (theRocket.getSpritePos().y < (renderHeight - theRocket.getSpritePos().h))
					{
						theRocket.setRocketVelocity({ 0, 350 });
					}
				}
				break;

				case SDLK_UP:
				{
					if (theRocket.getSpritePos().y > 0)
					{
						theRocket.setRocketVelocity({ 0, -350 });
					}
				}
				break;
				case SDLK_RIGHT:
				{
					if (theRocket.getSpritePos().x < (renderWidth - theRocket.getSpritePos().w))
					{
						theRocket.setRocketVelocity({ 350, 0 });
					}
				}
				break;

				case SDLK_LEFT:
				{
					if (theRocket.getSpritePos().x > 0)
					{
						theRocket.setRocketVelocity({ -350, 0 });
					}
				}
				break;
				case SDLK_SPACE:
				{
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

