#ifndef MAP_HANDLER_H
#define MAP_HANDLER_H

#include "EntityHandler.h"
#include "Enemy.h"
#include "Pathfinder.h"
#include "Graphics.h"
#include "MessageHandler.h"

//Import a map and update it, creating new enemies when needed
class MapHandler
{
private:
	MessageQueue* m_messageQueue;

	int m_nrOfPaths;
	Path* m_paths;

	vector<vector<ServerEntity*>> m_waves;
	float m_waveTimer;
	float m_enemySpawnTimer;
	int m_currentWave;

	int m_lives;

	int m_gridHeight;
	int m_gridWidth;
	bool** m_grid;
public:
	static enum State {RUNNING, VICTORY, DEFEAT};

	MapHandler();
	~MapHandler();

	void loadMap(std::string filename);
	State getState();
	void update(float _dt);

	void enemyDied();
};

#endif