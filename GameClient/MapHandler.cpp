#include "MapHandler.h"

MapHandler::MapHandler()
{

}

MapHandler::~MapHandler()
{

}

void loadMap(std::string filename)
{

}

void MapHandler::update()
{
	if(EntityHandler::getAllEnemies().size() < 1)
	{
		new Enemy();
	}
}

bool MapHandler::isDone()
{
	return false;	//Temp
}