#include "MapHandler.h"
#include <fstream>

Pathfinder *g_pathfinder;

MapHandler::MapHandler()
{
	m_currentWave = 0;
	m_waveTimer = 0.0f;
	m_gridHeight = 0;
	m_gridWidth = 0;
	m_nrOfPaths = 0;
	m_paths = NULL;
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
	
	for(int i = 0; i < m_gridHeight; i++)
		delete m_grid[i];
	delete m_grid;
	if(m_paths)
	{
		for(int i = 0; i < m_nrOfPaths; i++)
			delete m_paths[i].points;
		delete m_paths;
	}

	delete g_pathfinder;
}

bool MapHandler::isDone()
{
	return false;	// Here to stay.
}

void MapHandler::loadMap(std::string filename)
{
	this->m_waveTimer = 0.0f;

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
			stream.getline(buf, 1024);
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
		}
	}

	m_paths = new Path[m_nrOfPaths];

	for(int i = 0; i < m_nrOfPaths; i++)
	{
		m_paths[i].nrOfPoints = paths[i].nrOfPoints;
		m_paths[i].points = paths[i].points;
	}

	g_pathfinder->setStart(255 * this->m_paths[0].points[0].x / 64, 255 * this->m_paths[0].points[0].y / 64);
	g_pathfinder->setEnd(255 * this->m_paths[0].points[2].x / 64, 255 * this->m_paths[0].points[2].y / 64);

	//Path p = g_pathfinder->getPath();

	//for(int i = 0; i < p.nrOfPoints; i++)
	//{
	//	p.points[i].x = (p.points[i].x / 255) * 64;
	//	p.points[i].y = (p.points[i].y / 255) * 64;
	//}


	this->m_waves.push_back(vector<ServerEntity*>());
	//m_waves[0].push_back(new Enemy(FLOAT3(0.0f, 0.0f, 0.0f), p));
	//m_waves[0].push_back(new Enemy(FLOAT3(10.0f, 0.0f, 0.0f), p));
	//m_waves[0].push_back(new Enemy(FLOAT3(20.0f, 0.0f, 0.0f), p));
	//m_waves[0].push_back(new Enemy(FLOAT3(15.0f, 0.0f, 5.0f), p));
	//m_waves[0].push_back(new Enemy(FLOAT3(25.0f, 0.0f, 10.0f), p));
	//m_waves[0].push_back(new Enemy(FLOAT3(20.0f, 0.0f, 15.0f), p));
	m_waves[0].push_back(new Enemy(FLOAT3(30.0f, 0.0f, 8.0f), this->m_paths[0]));
	m_waves[0].push_back(new Enemy(FLOAT3(35.0f, 0.0f, 15.0f), this->m_paths[0]));
	m_waves[0].push_back(new Enemy(FLOAT3(40.0f, 0.0f, 18.0f), this->m_paths[0]));
	this->m_waves.push_back(vector<ServerEntity*>());
	m_waves[1].push_back(new Enemy(FLOAT3(50.0f, 0.0f, 0.0f), this->m_paths[0]));
	m_waves[1].push_back(new Enemy(FLOAT3(100.0f, 0.0f, 0.0f), this->m_paths[0]));
	m_waves[1].push_back(new Enemy(FLOAT3(20.0f, 0.0f, 0.0f), this->m_paths[0]));
	this->m_waves.push_back(vector<ServerEntity*>());
	m_waves[2].push_back(new Enemy(FLOAT3(5.0f, 0.0f, 30.0f), this->m_paths[0]));
	m_waves[2].push_back(new Enemy(FLOAT3(70.0f, 0.0f, 10.0f), this->m_paths[0]));
	m_waves[2].push_back(new Enemy(FLOAT3(10.0f, 0.0f, 20.0f), this->m_paths[0]));
}

void MapHandler::update(float _dt)
{
	if(m_waveTimer > 0.0f)
	{
		m_waveTimer = max(m_waveTimer-_dt, 0.0f);
		if(m_waveTimer == 0.0f)
		{
			for(int i = 0; i < m_waves[m_currentWave].size(); i++)
			{
				EntityHandler::addEntity(m_waves[m_currentWave][i]);
				m_waves[m_currentWave][i] = NULL; // Null them bitches, they are the entity handlers problem now.
			}
			m_currentWave++;
		}
	}
	else
	{
		if(EntityHandler::getNrOfEnemies() == 0 && m_currentWave < m_waves.size())
		{
			m_waveTimer = 10.0f;
		}
	}
}