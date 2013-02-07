#include "MapHandler.h"
#include <fstream>

Pathfinder *g_pathfinder;

MapHandler::MapHandler()
{
	this->m_currentWave = 0;
	this->m_waveTimer = 0.0f;
	this->m_enemySpawnTimer = 0.0f;
	this->m_gridHeight = 0;
	this->m_gridWidth = 0;
	this->m_nrOfPaths = 0;
	this->m_grid = NULL;
	this->m_paths = NULL;
}

MapHandler::~MapHandler()
{
	for(int i = 0; i < m_waves.size(); i++)
	{
		for(int j = 0; j < m_waves[i].size(); j++)
		{
			// If the waves wasnt added to the entity handler, simon must delete them here :')
			if(m_waves[i][j])
				delete m_waves[i][j];
		}
	}

	delete g_pathfinder;
	
	if(m_grid)
	{
		for(int i = 0; i < m_gridHeight; i++)
			delete m_grid[i];
		delete []m_grid;
	}

	if(m_paths)
		delete []m_paths;
}

bool MapHandler::isDone()
{
	//return m_currentWave >= m_waves.size();	//The work of Marcus the Game Destroyer
	return false;
}

void MapHandler::loadMap(std::string filename)
{
	this->m_waveTimer = 0.0f;
	
	FLOAT3 v1 = FLOAT3(0.0f, 0.0f, 0.0f);
	FLOAT3 v2 = FLOAT3(100.0f, 0.0f, 100.0f);
	int height;
	int width;
	Path paths[100];
	ifstream stream;
	stream.open(filename);
	while(!stream.eof())
	{
		char buf[1024];
		char key[1024];
		stream.getline(buf, 1024);
		sscanf(buf, "%s", key);
		
		if(strcmp(key, "width:") == 0)
		{
			sscanf(buf, "width: %d", &width);
		}
		else if(strcmp(key, "height:") == 0)
		{
			sscanf(buf, "height: %d", &height);
		}
		else if(strcmp(key, "MODELS:") == 0)
		{
			string s;
			bool done = false;
			while(!done)
			{
				stream.getline(buf, 1024);
				sscanf(buf, "%s", key);
				
				if(strcmp(key, "end") == 0)
				{
					done = true;
				}
				else
				{
					char in[100];
					FLOAT3 position;
					FLOAT3 rotation;
					sscanf(buf, "%s %f %f %f %f %f %f", &in, &position.x, &position.y, &position.z, &rotation.y, &rotation.x, &rotation.z);

					position.z = v2.z+position.z;
					rotation.x = rotation.x * (D3DX_PI/180.0f);
					
					Model *m = g_graphicsEngine->createModel(key, position);
					m->setRotation(rotation);

					EntityHandler::addEntity(new ServerEntity(position, rotation, new BoundingOrientedBox(*m->getObb()), ServerEntity::Type::StaticType));
					g_graphicsEngine->removeModel(m);
				}
			}
		}
		else if(strcmp(key, "GRID") == 0)
		{
			stream.getline(buf, 1024);
			sscanf(buf, "width, height %d %d", &m_gridWidth, &m_gridHeight);

			g_pathfinder = new Pathfinder(this->m_gridWidth, this->m_gridHeight, width, height);
			
			m_grid = new bool*[m_gridHeight];
			for(int j = m_gridHeight-1; j >= 0; j--)
			{
				m_grid[j] = new bool[m_gridWidth];

				stream.getline(buf, 1024);
				sscanf(buf, "%s", key);

				for(int i = 0; i < m_gridWidth; i++)
				{
					//m_grid[j][i] = atoi(&key[i]);
					m_grid[j][i] = '0' - key[i];

					if(m_grid[j][i] == true)
					{
						g_pathfinder->setAsWall(i, j);
					}
				}
			}

			// The END string key should be here, get rid of it
			//stream.getline(buf, 1024);
		}
		else if(strcmp(key, "path") == 0)
		{
			stream.getline(buf, 1024);
			sscanf(buf, "%s", key);

			int nrOfPoints = 0;
			FLOAT2 points[100];
			while(strcmp(key, "end") != 0)
			{
				float notInvertZ;
				sscanf(buf, "%f %f", &points[nrOfPoints].x, &notInvertZ);
				points[nrOfPoints].y = height+notInvertZ;
				nrOfPoints++;
				stream.getline(buf, 1024);
				sscanf(buf, "%s", key);
			}
			
			FLOAT2* optimizedPoints = new FLOAT2[nrOfPoints];
			for(int i = 0; i < nrOfPoints; i++)
			{
				optimizedPoints[i] = points[i];
			}

			paths[m_nrOfPaths++] = Path(nrOfPoints, optimizedPoints);
			delete []optimizedPoints;
		}
	}
	
	m_paths = new Path[m_nrOfPaths];

	for(int i = 0; i < m_nrOfPaths; i++)
		m_paths[i] = paths[i];
	
	//this->m_waves.push_back(vector<ServerEntity*>());
	//m_waves[0].push_back(new Enemy(FLOAT3(this->m_paths[0].points[0].x, 0.0f, this->m_paths[0].points[0].y), this->m_paths[0]));
	//m_waves[0].push_back(new Enemy(FLOAT3(this->m_paths[0].points[0].x, 0.0f, this->m_paths[0].points[0].y), this->m_paths[0]));
	//m_waves[0].push_back(new Enemy(FLOAT3(this->m_paths[0].points[0].x, 0.0f, this->m_paths[0].points[0].y), this->m_paths[0]));
	//this->m_waves.push_back(vector<ServerEntity*>());
	//m_waves[1].push_back(new Enemy(FLOAT3(this->m_paths[0].points[0].x, 0.0f, this->m_paths[0].points[0].y), this->m_paths[0]));
	//m_waves[1].push_back(new Enemy(FLOAT3(this->m_paths[0].points[0].x, 0.0f, this->m_paths[0].points[0].y), this->m_paths[0]));
	//m_waves[1].push_back(new Enemy(FLOAT3(this->m_paths[0].points[0].x, 0.0f, this->m_paths[0].points[0].y), this->m_paths[0]));
	//this->m_waves.push_back(vector<ServerEntity*>());
	//m_waves[2].push_back(new Enemy(FLOAT3(this->m_paths[0].points[0].x, 0.0f, this->m_paths[0].points[0].y), this->m_paths[0]));
	//m_waves[2].push_back(new Enemy(FLOAT3(this->m_paths[0].points[0].x, 0.0f, this->m_paths[0].points[0].y), this->m_paths[0]));
	//m_waves[2].push_back(new Enemy(FLOAT3(this->m_paths[0].points[0].x, 0.0f, this->m_paths[0].points[0].y), this->m_paths[0]));
}

void MapHandler::update(float _dt)
{
	//if(m_waveTimer > 0.0f)
	//{
	//	m_waveTimer = max(m_waveTimer-_dt, 0.0f);
	//}
	//else if(m_waveTimer == 0.0f && m_currentWave < m_waves.size())
	//{
	//	//for(int i = 0; i < m_waves[m_currentWave].size(); i++)
	//	//{
	//	//	EntityHandler::addEntity(m_waves[m_currentWave][i]);
	//	//	m_waves[m_currentWave][i] = NULL; // Null them bitches, they are the entity handlers problem now.
	//	//}

	//	this->m_enemySpawnTimer = max(this->m_enemySpawnTimer-_dt, 0.0f);

	//	if(this->m_enemySpawnTimer == 0.0f)
	//	{
	//		if(this->m_waves[this->m_currentWave].empty() == false)
	//		{
	//			EntityHandler::addEntity(this->m_waves[this->m_currentWave].front());
	//			this->m_waves[this->m_currentWave].erase(this->m_waves[this->m_currentWave].begin());
	//			this->m_enemySpawnTimer = 1.0f;
	//		}
	//		else
	//		{
	//			m_currentWave++;
	//			this->m_waveTimer = -1.0f;
	//		}
	//	}
	//}
	//else
	//{
	//	if(EntityHandler::getNrOfEnemies() == 0 && m_currentWave < m_waves.size())
	//	{
	//		m_waveTimer = 10.0f;
	//	}
	//}
}