
/*
=================
cBullet.h
- Header file for class definition - SPECIFICATION
- Header file for the Bullet class which is a child of cSprite class
=================
*/
#ifndef _CEnemyBULLET_H
#define _CEnemyBULLET_H
#include "cSprite.h"


class cEnemyBullet : public cSprite
{
private:
	SDL_Point EnemybulletVelocity;

public:
	cEnemyBullet();
	void update(double deltaTime);		//Enemy Bullet update method
	void setEnemyBulletVelocity(SDL_Point bulletVel);   // Sets the velocity for the Bullet
	SDL_Point getEnemyBulletVelocity();				 // Gets the Bullet velocity
};
#endif