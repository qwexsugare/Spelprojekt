#include "MapHandler.h"

MapHandler::MapHandler()
{

}

MapHandler::~MapHandler()
{

}

void MapHandler::loadMap(std::string filename)
{
	this->m_waveDelay =  0.0f;
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