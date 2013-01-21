#ifndef MAP_HANDLER_H
#define MAP_HANDLER_H

#include "EntityHandler.h"
#include "Enemy.h"

//Import a map and update it, creating new enemies when needed
class MapHandler
{
private:
	vector<vector<ServerEntity*>> m_waves;
	float m_waveTimer;
	int m_currentWave;
public:
	MapHandler();
	~MapHandler();

	void loadMap(std::string filename);
	bool isDone();
	void update(float _dt);
};

#endif