/*
=================
cAsteroid.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cEnemy.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cEnemy::cEnemy() : cSprite()
{
	this->enemyVelocity = { 25, 25 };
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
	currentSpritePos.y += this->getSpriteTranslation().y * deltaTime;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });
	cout << "Enemy position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl;
	this->setBoundingRect(this->getSpritePos());
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
