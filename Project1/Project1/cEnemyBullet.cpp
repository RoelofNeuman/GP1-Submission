#include "cEnemyBullet.h"

/*
=================
cBullet.cpp
- Header file for class definition - IMPLEMENTATION
=================

/*
=================================================================
Defualt Constructor
=================================================================
*/
cEnemyBullet::cEnemyBullet() : cSprite()
{
	this->EnemybulletVelocity = { 0, 0 };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cEnemyBullet::update(double deltaTime)
{

	FPoint direction = { 0.0, 0.0 };
	direction.X = (sin((this->getSpriteRotAngle())*PI / 180));
	direction.Y = -(cos((this->getSpriteRotAngle())*PI / 180));

	direction.X *= this->getSpriteTranslation().x;
	direction.Y *= this->getSpriteTranslation().y;

	this->EnemybulletVelocity.x = this->EnemybulletVelocity.x + direction.X;
	this->EnemybulletVelocity.y = this->EnemybulletVelocity.y + direction.Y;

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->EnemybulletVelocity.x * deltaTime;
	currentSpritePos.y += this->EnemybulletVelocity.y * deltaTime;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });

	//cout << "Enemy bullet position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl;

	this->setBoundingRect(this->getSpritePos());

}
/*
=================================================================
Sets the velocity for the Bullet
=================================================================
*/
void cEnemyBullet::setEnemyBulletVelocity(SDL_Point bulletVel)
{
	this->EnemybulletVelocity = bulletVel;
}
/*
=================================================================
Gets the Bullet velocity
=================================================================
*/
SDL_Point cEnemyBullet::getEnemyBulletVelocity()
{
	return this->EnemybulletVelocity;
}
