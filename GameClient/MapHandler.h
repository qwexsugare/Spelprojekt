#ifndef MAP_HANDLER_H
#define MAP_HANDLER_H

#include "EntityHandler.h"
#include "Enemy.h"

//Import a map and update it, creating new enemies when needed
class MapHandler
{
private:
	vector<vector<ServerEntity*>> m_waves;
	float m_waveDelay;
public:
	MapHandler();
	~MapHandler();

	void loadMap(std::string filename);
	void update();
	bool isDone();
};

#endif