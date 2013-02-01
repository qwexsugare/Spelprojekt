#ifndef MAP_HANDLER_H
#define MAP_HANDLER_H

#include "EntityHandler.h"
#include "Enemy.h"
#include "Pathfinder.h"

//Import a map and update it, creating new enemies when needed
class MapHandler
{
private:
	int m_nrOfPaths;
	Path* m_paths;

	vector<vector<ServerEntity*>> m_waves;
	float m_waveTimer;
	int m_currentWave;

	int m_gridHeight;
	int m_gridWidth;
	bool** m_grid;
public:
	MapHandler();
	~MapHandler();

	void loadMap(std::string filename);
	bool isDone();
	void update(float _dt);
};

#endif