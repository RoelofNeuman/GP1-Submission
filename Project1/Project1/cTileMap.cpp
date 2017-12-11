/*
=================
- cTileMap.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cTileMap.h"

/*
=================================================================
 Defualt Constructor
=================================================================
*/
cTileMap::cTileMap() : cSprite()
{
	this->initialiseMap();
}

cTileMap::cTileMap(cFileHandler* aFile) : cSprite()
{
	this->initialiseMapFromFile(aFile);
}

void cTileMap::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, cTextureMgr* theTxtMgr, vector<LPCSTR> theTxt)
{


}

/*
=================================================================
Update the sprite position
=================================================================
*/


/*
=================================================================
- Set the initial values for the map
=================================================================
*/
void cTileMap::initialiseMap()
{
	srand(time(NULL));
	

}
/*
=================================================================
- Set the initial values for the map from file input
=================================================================
*/
void cTileMap::initialiseMapFromFile(cFileHandler* aFile)
{
	string fileData;
	fileData = aFile->readDataFromFile();

	stringstream mapData(fileData);

	// Fill map with data from file
	
		
			 
			if (mapData.peek() == ',')
			{
				mapData.ignore();
			}
		
	
	aFile->closeFile();
}
/*
=================================================================
- set start position for tile map
=================================================================
*/
void cTileMap::setMapStartXY(SDL_Point startPosXY)
{
	mapStartXY = startPosXY;
}
/*
=================================================================
- get start pposition for tile map
=================================================================
*/
SDL_Point cTileMap::getMapStartXY()
{
	return mapStartXY;
}
/*
=================================================================
- get the tile map as a string
=================================================================
*/
string cTileMap::getMapData()
{
	string mapData = "";
	
	
		
	mapData =  scoreAsStringForFile;
		
		mapData += '\n';
	
	return mapData;
}

/*
=================================================================
- Write the values from the map to the file
=================================================================
*/
void cTileMap::writeMapDataToFile(cFileHandler* aFile)
{
	string mapDataToWrite = "";
	string theMapData = this->getMapData();
	stringstream outputStr(theMapData);
	if (!theMapData.empty())
	{
		while (getline(outputStr, mapDataToWrite, '\n')){
			mapDataToWrite += '\n';
			aFile->writeDataToFile(mapDataToWrite);
		}
	}
	aFile->closeFile();
}
