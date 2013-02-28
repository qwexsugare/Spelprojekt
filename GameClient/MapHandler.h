#ifndef MAP_HANDLER_H
#define MAP_HANDLER_H

#include "EntityHandler.h"
#include "Enemy.h"
#include "SoulEaterSteed.h"
#include "HellfireSteed.h"
#include "BruteSteed.h"
#include "ThunderSteed.h"
#include "Imp.h"
#include "FrostDemon.h"
#include "SpittingDemon.h"
#include "Shade.h"
#include "Pathfinder.h"
#include "Graphics.h"
#include "MessageHandler.h"

//Import a map and update it, creating new enemies when needed
class MapHandler
{
private:
	static enum HERO_TYPE {OFFICER, RED_KNIGHT, ENGINEER, DOCTOR, THE_MENTALIST, NONE};
	MessageQueue* m_messageQueue;

	int m_nrOfPaths;
	Path* m_paths;
	FLOAT3 playerStartPositions[5];
	int nrOfSpawnPoints;
	vector<vector<ServerEntity*>> m_waves;
	float m_waveTimer;
	float m_enemySpawnTimer;
	int m_currentWave;

	int m_lives;

	int m_gridHeight;
	int m_gridWidth;
	bool** m_grid;
	Map map;
public:
	static enum State {RUNNING, VICTORY, DEFEAT};

	MapHandler();
	~MapHandler();

	void loadMap(std::string filename);
	State getState();
	void update(float _dt);
	void createWave(int _imps, int _shades, int _spits, int _frosts, int _souls, int _hell, int _thunder, int _brutes);

	void enemyDied();
	FLOAT3 getPlayerPosition(int p);
};

#endif