/*
=================
cAsteroid.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cEnemy.h"
#include "cEnemyBullet.h"


/*
=================================================================
Defualt Constructor
=================================================================
*/
cEnemy::cEnemy() : cSprite()
{
	this->enemyVelocity = { 0, 0 };
	
}
/*
=================================================================
Update the sprite position
=================================================================
*/



void cEnemy::update(double deltaTime)
{

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->getSpriteTranslation().x * deltaTime;
	currentSpritePos.y += this->getSpriteTranslation().y * 25 * deltaTime;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });
	this->setBoundingRect(this->getSpritePos());

	//Makes enemy shoot at random times
	
	if (currentSpritePos.x <= 0)
	{
		this->setSpriteTranslation({100, 0});
	}
	
	if (currentSpritePos.x >= 1000)
	{
		this->setSpriteTranslation({ -200,0 });
	}


	
}
/*
=================================================================
  Sets the velocity for the Enemy
=================================================================
*/
void cEnemy::setEnemyVelocity(SDL_Point EnemyVel)
{
	enemyVelocity = EnemyVel;
}
/*
=================================================================
  Gets the Asteroid velocity
=================================================================
*/
SDL_Point cEnemy::getEnemyVelocity()
{
	return enemyVelocity;
}
