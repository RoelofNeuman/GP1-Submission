/*
=================
cAsteroid.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _CENEMY_H
#define _CENEMY_H
#include "cSprite.h"

class cEnemy : public cSprite
{
private:
	SDL_Point enemyVelocity;

public:
	cEnemy();
	void update(double deltaTime);		// Rocket update method
	void setEnemyVelocity(SDL_Point asteroidVel);   // Sets the velocity for the Enemy
	SDL_Point getEnemyVelocity();				 // Gets the Enemy velocity
};
#endif