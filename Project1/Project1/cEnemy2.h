
/*
=================
cAsteroid.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _CENEMY2_H
#define _CENEMY2_H
#include "cSprite.h"

class cEnemy2 : public cSprite
{
private:
	SDL_Point enemy2Velocity;

public:
	cEnemy2();
	void update(double deltaTime);		// Rocket update method
	void setEnemy2Velocity(SDL_Point asteroidVel);   // Sets the velocity for the Enemy
	SDL_Point getEnemy2Velocity();				 // Gets the Enemy velocity
};
#endif