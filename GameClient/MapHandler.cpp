#include "MapHandler.h"
#include "MyAlgorithms.h"
#include <fstream>
#include "Imp.h"
#include "SpittingDemon.h"
#include "FrostDemon.h"
#include "Shade.h"
#include "BruteSteed.h"
#include "SoulEaterSteed.h"
#include "HellfireSteed.h"
#include "ThunderSteed.h"

Pathfinder *g_pathfinder;

MapHandler::MapHandler()
{
	this->m_messageQueue = new MessageQueue();
	this->m_currentWave = 0;
	this->m_waveTimer = 30.0f;
	this->m_enemySpawnTimer = 30.0f;
	this->m_gridHeight = 0;
	this->m_gridWidth = 0;
	this->m_nrOfPaths = 0;
	this->m_grid = NULL;
	this->m_paths = NULL;
	this->m_lives = 100;
	Statistics::setStartLife(this->m_lives);
	this->nrOfSpawnPoints=0;
	for(int i=0;i<5;i++)
	{
		this->playerStartPositions[i]=FLOAT3(0.0f,0.0f,0.0f);
	}
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

MapHandler::State MapHandler::getState()
{
	if(this->m_lives <= 0)
	{
		return MapHandler::State::DEFEAT;
	}
	else if(this->m_currentWave > this->m_waves.size())
	{
		return MapHandler::State::VICTORY;
	}
	else
	{
		return MapHandler::State::RUNNING;
	}
}

void MapHandler::loadMap(std::string filename)
{
	this->m_waveTimer = 0.0f;
	
	bool heightLoaded = false;
	bool widthLoaded = false;
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

			if(heightLoaded)
				EntityHandler::initQuadTree(FLOAT2(width, height));
			else
				widthLoaded = true;
		}
		else if(strcmp(key, "height:") == 0)
		{
			sscanf(buf, "height: %d", &height);

			if(widthLoaded)
				EntityHandler::initQuadTree(FLOAT2(width, height));
			else
				heightLoaded = true;
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

					position.z = -position.z;
					rotation.x *= -(D3DX_PI/180);
					rotation.y *= (D3DX_PI/180);
					rotation.z *= (D3DX_PI/180);
					//rotation = FLOAT3(0,0,0);
					
					//if the model represents a spawn point
					if(key[0]=='S'&&key[1]=='P'&&key[2]=='A'&&key[3]=='W'&&key[4]=='N')
					{
						//doctor
						if(key[5]=='D')
							this->playerStartPositions[HERO_TYPE::DOCTOR]=position;
						//enginer
						if(key[5]=='E')
							this->playerStartPositions[HERO_TYPE::ENGINEER]=position;
						//mentalist
						if(key[5]=='M')
							this->playerStartPositions[HERO_TYPE::THE_MENTALIST]=position;
						//officer
						if(key[5]=='O')
							this->playerStartPositions[HERO_TYPE::OFFICER]=position;
						//redknight
						if(key[5]=='R')
							this->playerStartPositions[HERO_TYPE::RED_KNIGHT]=position;

						this->nrOfSpawnPoints++;
					}
					else if(strcmp(key, "Fountain") == 0)
					{
						EntityHandler::addEntity(new HealingFountain(position));
					}
					else if(strcmp(key, "FountainAngel") == 0)
					{
						EntityHandler::addEntity(new HealingFountain(position));
					}
					else
					{
						Model *m = g_graphicsEngine->createModel(key, FLOAT3(0.0f, 0.0f, 0.0f), false); //must be nonstatic (false)
						m->setRotation(rotation);
						if(strcmp(key, "Church")==0)
							EntityHandler::addEntity(new ServerEntity(position, rotation, new BoundingOrientedBox(*m->getObb()), ServerEntity::Type::GoalType));
						else
							EntityHandler::addEntity(new ServerEntity(position, rotation, new BoundingOrientedBox(*m->getObb()), ServerEntity::Type::StaticType));
						g_graphicsEngine->removeModel(m);
					}
				}
			}
		}
		else if(strcmp(key, "GRID") == 0)
		{
			stream.getline(buf, 1024);
			sscanf(buf, "width, height %d %d", &m_gridWidth, &m_gridHeight);

			this->map = Map(this->m_gridWidth, this->m_gridHeight);
			
			m_grid = new bool*[m_gridHeight];
			for(int j = 0; j < m_gridHeight; j++)
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
						map.getNode(Position(i, j))->actAsWall();
					}
				}
			}

			g_pathfinder = new Pathfinder(map, FLOAT2(width, height));

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
				points[nrOfPoints].y = -notInvertZ;
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

	//Improve the paths
	for(int i = 0; i < this->m_nrOfPaths; i++)
	{
		FLOAT2 *tempPoints = new FLOAT2[500];
		int nrOfPoints = 0;

		for(int j = 0; j < this->m_paths[i].nrOfPoints - 1; j++)
		{
			Path p = g_pathfinder->getPath(this->m_paths[i].points[j], this->m_paths[i].points[j + 1]);

			for(int k = 0; k < p.nrOfPoints && nrOfPoints < 500; k++)
			{
				tempPoints[nrOfPoints] = p.points[k];
				nrOfPoints++;
			}
		}

		FLOAT2 *optimizedPoints = new FLOAT2[nrOfPoints];

		for(int j = 0; j < nrOfPoints; j++)
		{
			optimizedPoints[j] = tempPoints[j];
		}

		delete tempPoints;
		delete this->m_paths[i].points;

		this->m_paths[i].points = optimizedPoints;
		this->m_paths[i].nrOfPoints = nrOfPoints;
	}
	
	//createWave(0,10,0,0,0,0,0,0); // MÖGs super advanced specified wave with extra cheese
	

	/// This is where all waves are created! 
	///
	/// createWave(imps, shades, spitting, Frost, SoulEater, Hellfire, Thunder, Brute)
	///
	///
	string waveName="";
	for(int i=0;i<filename.length()-4;i++)
	{
		waveName+=filename[i];
	}

	waveName+="waves.txt";
	ifstream file;
	file.open(waveName.c_str());

	if(file.is_open())
	{
		while(!file.eof())
		{
			int q,w,e,r,t,y,u,i;
			string type="w";
			string missionType="";
			string missionName="";
			int startTime=0,endTime=0;
			float posx=0.0f,posz=0.0f;
			q=w=e=r=t=y=u=i=0;
			file >> type;
			if(type[0]=='w')
			{
				file >> q >> w >> e >> r >> t >> y >> u >> i;
				createWave(q,w,e,r,t,y,u,i);
			}
			if(type[0]=='m')
			{
				file >> missionType >> posx>> posz>> startTime >> endTime >> missionName;
				for(int i=0;i<missionName.size();i++)
				{
					if(missionName[i]=='_')
						missionName[i]=' ';
				}
				this->missions.push_back(new Mission());
				this->missions[this->missions.size()-1]->createMission(missionType, posx, posz, startTime, endTime,missionName);
			}
			
		}
	}
	file.close();

}

void MapHandler::update(float _dt)
{
	//if(m_waveTimer == 0.0f)
	{
		//EntityHandler::addEntity(new Mission(this->mission));
		for(int i=0;i<this->missions.size();i++)
		{
			if(this->missions[i]->handle(this->m_currentWave))
			{
				if(!this->missions[i]->isAddedToEntityHandler())
				{
					this->missions[i]->addToEntityHandler();
					EntityHandler::addEntity(this->missions[i]);
					this->m_messageQueue->pushOutgoingMessage(new MissionMessage(this->missions[i]->getMissionName(),"start"));
				}
			}
		}
	}

	Statistics::addTime(_dt);
	if(m_waveTimer > 0.0f)
	{
		m_waveTimer = max(m_waveTimer-_dt, 0.0f);


	}
	else if(m_waveTimer == 0.0f && m_currentWave < m_waves.size())
	{
		this->m_enemySpawnTimer = max(this->m_enemySpawnTimer-_dt, 0.0f);

		if(this->m_enemySpawnTimer == 0.0f)
		{
			if(this->m_waves[this->m_currentWave].empty() == false)
			{
				EntityHandler::addEntity(this->m_waves[this->m_currentWave].front());
				this->m_waves[this->m_currentWave].erase(this->m_waves[this->m_currentWave].begin());
				this->m_enemySpawnTimer = 2.0f;

			}
			else
			{
				m_currentWave++;
				Statistics::waveFinnished();
				this->m_waveTimer = -1.0f;
			}
		}
	}
	else if(EntityHandler::getNrOfEnemies() == 0)
	{	
		if(this->m_currentWave < m_waves.size())
		{
			m_waveTimer = 10.0f;
			this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::WAVE_UPDATE, this->m_currentWave + 1, FLOAT3()));
		}
		else
		{
			this->m_currentWave = this->m_waves.size() + 1;
		}
	}
}

void MapHandler::enemyDied()
{
	this->m_lives--;
	Statistics::decreaseStartLife();
}

void MapHandler::createWave(int _imps,  int _spits, int _shades, int _frosts, int _souls, int _hell, int _thunder, int _brutes)
{
	m_waves.push_back(vector<ServerEntity*>());
	int totalMonsters = _imps + _shades + _spits + _frosts + _souls + _hell + _thunder + _brutes;
	int t = random(0,0);
	
	int _min = 0;
	int _max =  this->m_nrOfPaths-1;

	for(int i = 0; i < totalMonsters; i ++)
	{
		if(i < _imps)
		{
			
			t = random(_min,_max);
			m_waves[m_waves.size()-1].push_back(new Imp(FLOAT3(this->m_paths[t].points[0].x, 0.0f, this->m_paths[t].points[0].y), this->m_paths[t]));
		}
		if(i < _shades)
		{
			t = random(_min,_max);
			m_waves[m_waves.size()-1].push_back(new Shade(FLOAT3(this->m_paths[t].points[0].x, 0.0f, this->m_paths[t].points[0].y), this->m_paths[t]));
		}
		if(i < _spits)
		{
			t = random(_min,_max);
			m_waves[m_waves.size()-1].push_back(new SpittingDemon(FLOAT3(this->m_paths[t].points[0].x, 0.0f, this->m_paths[t].points[0].y), this->m_paths[t]));
		}
		if(i < _frosts)
		{
			t = random(_min,_max);
			m_waves[m_waves.size()-1].push_back(new FrostDemon(FLOAT3(this->m_paths[t].points[0].x, 0.0f, this->m_paths[t].points[0].y), this->m_paths[t]));
		}
		if(i < _souls)
		{
			t = random(_min,_max);
			m_waves[m_waves.size()-1].push_back(new SoulEaterSteed(FLOAT3(this->m_paths[t].points[0].x, 0.0f, this->m_paths[t].points[0].y), this->m_paths[t]));
		}
		if(i < _hell)
		{
			t = random(_min,_max);
			m_waves[m_waves.size()-1].push_back(new HellfireSteed(FLOAT3(this->m_paths[t].points[0].x, 0.0f, this->m_paths[t].points[0].y), this->m_paths[t]));
		}
		if(i < _thunder)
		{
			t = random(_min,_max);
			m_waves[m_waves.size()-1].push_back(new ThunderSteed(FLOAT3(this->m_paths[t].points[0].x, 0.0f, this->m_paths[t].points[0].y), this->m_paths[t]));
		}
		if(i < _brutes)
		{
			t = random(_min,_max);
			m_waves[m_waves.size()-1].push_back(new BruteSteed(FLOAT3(this->m_paths[t].points[0].x, 0.0f, this->m_paths[t].points[0].y), this->m_paths[t]));
		}
			

	
	}

}

FLOAT3 MapHandler::getPlayerPosition(int p)
{
	FLOAT3 pos = FLOAT3(0.0f,0.0f,0.0f);
	if(p>=0&&p<this->nrOfSpawnPoints)
	{
		pos = this->playerStartPositions[p];
	}
	return pos;
}

int MapHandler::getLivesLeft()
{
	return this->m_lives;
}

MessageQueue* MapHandler::getMessageQueue()
{
	return this->m_messageQueue;
}