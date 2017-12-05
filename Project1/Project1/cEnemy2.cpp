/*
=================
cAsteroid.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cEnemy2.h"
#include "cEnemyBullet.h"


/*
=================================================================
Defualt Constructor
=================================================================
*/
cEnemy2::cEnemy2() : cSprite()
{
	this->enemy2Velocity = { 0, 0 };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cEnemy2::update(double deltaTime)
{

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->getSpriteTranslation().x * deltaTime;
	currentSpritePos.y += this->getSpriteTranslation().y * deltaTime;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });
	cout << "Enemy position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl;
	this->setBoundingRect(this->getSpritePos());

	//Makes enemy shoot at random times



}
/*
=================================================================
Sets the velocity for the Enemy
=================================================================
*/
void cEnemy2::setEnemy2Velocity(SDL_Point EnemyVel)
{
	enemy2Velocity = EnemyVel;
}
/*
=================================================================
Gets the Asteroid velocity
=================================================================
*/
SDL_Point cEnemy2::getEnemy2Velocity()
{
	return enemy2Velocity;
}
