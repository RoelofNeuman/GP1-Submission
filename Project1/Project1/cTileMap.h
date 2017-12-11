/*
=================
cTileMap.h
- Header file for class definition - SPECIFICATION
- Header file for the tileMap class which is a child of cSprite class
=================
*/
#ifndef _CTILEMAP_H
#define _CTILEMAP_H
#include "asteroidsGame.h"
#include <sstream>


class cTileMap: public cSprite
{
protected:
	

private:
	SDL_Point mapStartXY;
	SDL_Point tileClickedRC;
	cSprite aTile;
	void initialiseMap();		// Set the initial values for the map

public:
	cTileMap();
	cTileMap(cFileHandler* aFile);

	void initialiseMapFromFile(cFileHandler* aFile);		// Set the initial values for the map from file input
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, cTextureMgr* theTxtMgr, vector<LPCSTR> theTxt);		// Default render function
	
	void setMapStartXY(SDL_Point startPosXY);
	SDL_Point getMapStartXY();
	string getMapData();
	void writeMapDataToFile(cFileHandler* aFile);

	string scoreAsStringForFile;
};
#endif