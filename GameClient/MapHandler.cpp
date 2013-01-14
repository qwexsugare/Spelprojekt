#include "MapHandler.h"

MapHandler::MapHandler()
{
	this->m_waves.push_back(vector<ServerEntity*>());
	m_waves[0].push_back(new Enemy(FLOAT3(0.0f, 0.0f, 0.0f)));
	m_waves[0].push_back(new Enemy(FLOAT3(10.0f, 0.0f, 0.0f)));
	m_waves[0].push_back(new Enemy(FLOAT3(20.0f, 0.0f, 0.0f)));
	this->m_waves.push_back(vector<ServerEntity*>());
	m_waves[1].push_back(new Enemy(FLOAT3(50.0f, 0.0f, 0.0f)));
	m_waves[1].push_back(new Enemy(FLOAT3(100.0f, 0.0f, 0.0f)));
	m_waves[1].push_back(new Enemy(FLOAT3(20.0f, 0.0f, 0.0f)));
	this->m_waves.push_back(vector<ServerEntity*>());
	m_waves[2].push_back(new Enemy(FLOAT3(5.0f, 0.0f, 30.0f)));
	m_waves[2].push_back(new Enemy(FLOAT3(70.0f, 0.0f, 10.0f)));
	m_waves[2].push_back(new Enemy(FLOAT3(10.0f, 0.0f, 20.0f)));

	m_currentWave = 0;
	m_waveTimer = 0.0f;
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
}

bool MapHandler::isDone()
{
	return false;	// Here to stay.
}

void MapHandler::loadMap(std::string filename)
{
	this->m_waveTimer =  0.0f;
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
	else if(EntityHandler::getAllEnemies().size() == 0 && m_currentWave < m_waves.size())
	{
		m_waveTimer = 10.0f;
	}
}