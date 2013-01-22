#include "Minimap.h"
#include "Graphics.h"
#include "Input.h"

Minimap::Minimap()
{
	m_sprite = NULL;
	m_view = NULL;
}

Minimap::Minimap(string _file, FLOAT2 _terrainMin, FLOAT2 _terrainMax, FLOAT2 _cameraPos)
{
	m_terrainMin = _terrainMin;
	m_terrainMax = _terrainMax;
	m_screenSpacePos = FLOAT2(0.79215f, 0.7235f);
	m_screenSpaceSize = FLOAT2(0.2625f, 0.466666667f);
	m_sprite = g_graphicsEngine->createSprite(_file, m_screenSpacePos, m_screenSpaceSize, 0);
	m_view = g_graphicsEngine->createSprite("minimap/view.png", m_screenSpacePos, FLOAT2(0.12f, 0.1f), 0);
	m_movingCameraWithMinimap = false;
}

Minimap::~Minimap()
{
	if(m_sprite)
		g_graphicsEngine->removeSprite(m_sprite);
	if(m_view)
		g_graphicsEngine->removeSprite(m_view);
	for(int i = 0; i < m_enemyPositions.size(); i++)
		g_graphicsEngine->removeSprite(m_enemyPositions[i]);
}

bool Minimap::isMouseInMap(INT2 _mousePos)const
{
	if(_mousePos.x/float(g_graphicsEngine->getRealScreenSize().x)*2.0f-1.0f > (m_screenSpacePos.x-m_screenSpaceSize.x/2.0f) &&
		_mousePos.x/float(g_graphicsEngine->getRealScreenSize().x)*2.0f-1.0f < (m_screenSpacePos.x+m_screenSpaceSize.x/2.0f) &&
		_mousePos.y/float(g_graphicsEngine->getRealScreenSize().y)*2.0f-1.0f > (-m_screenSpacePos.y-m_screenSpaceSize.y/2.0f) &&
		_mousePos.y/float(g_graphicsEngine->getRealScreenSize().y)*2.0f-1.0f < (-m_screenSpacePos.y+m_screenSpaceSize.y/2.0f))
		return true;
	else
		return false;
}

FLOAT2 Minimap::getTerrainPos(INT2 _mousePos)const
{
	float mouseX = (_mousePos.x/float(g_graphicsEngine->getRealScreenSize().x)*2.0f-1.0f);
	float mouseY = (_mousePos.y/float(g_graphicsEngine->getRealScreenSize().y)*2.0f-1.0f);

	FLOAT2 distanceFromMapStart = FLOAT2(
		mouseX-((m_screenSpacePos.x-m_screenSpaceSize.x/2.0f)),
		mouseY-((-m_screenSpacePos.y-m_screenSpaceSize.y/2.0f)));
	
	return FLOAT2(
		distanceFromMapStart.x/m_screenSpaceSize.x,
		distanceFromMapStart.y/m_screenSpaceSize.y)
		* (m_terrainMax-m_terrainMin) + m_terrainMin;
}

void Minimap::update(const vector<Entity*>& _entites, FLOAT2 _cameraPos, float _terrainWidth, float _terrainHeight)
{
	if(g_mouse->isLButtonPressed())
	{
		m_movingCameraWithMinimap = true;
	}
	else if(g_mouse->isLButtonReleased())
	{
		m_movingCameraWithMinimap = false;
	}

	if(m_movingCameraWithMinimap)
	{
		if(this->isMouseInMap(g_mouse->getPos()))
		{
			FLOAT2 pos = this->getTerrainPos(g_mouse->getPos());

			if(pos.x > _terrainWidth-27.0f)
			{
				g_graphicsEngine->getCamera()->setX(_terrainWidth-27.0f);
			}
			else if(pos.x < 27.0f)
			{
				g_graphicsEngine->getCamera()->setX(27.0f);
			}
			else
			{
				g_graphicsEngine->getCamera()->setX(pos.x);
			}
			
			if(pos.y < 25.0f)
			{
				g_graphicsEngine->getCamera()->setZ(25.0f);
			}
			else if(pos.y > _terrainHeight-4.0f)
			{
				g_graphicsEngine->getCamera()->setZ(_terrainHeight-4.0f);
			}
			else
			{
				g_graphicsEngine->getCamera()->setZ(pos.y);
			}
		}
	}

	float screenSpaceX;
	float screenSpaceY;
	int enemyTypeCounter = 0;
	int heroTypeCounter = 0;
	for(int i = 0; i < _entites.size(); i++)
	{
		switch(_entites[i]->m_type)
		{
		case ServerEntity::HeroType:
			screenSpaceX = _entites[i]->m_model->getPosition().x/(m_terrainMax.x-m_terrainMin.x)*2.0f-1.0f;
			screenSpaceY = _entites[i]->m_model->getPosition().z/(m_terrainMax.y-m_terrainMin.y)*2.0f-1.0f;
			heroTypeCounter++;
			if(heroTypeCounter > m_playerPositions.size())
			{
				m_playerPositions.push_back(g_graphicsEngine->createSprite("minimap/player_pos.png",
					FLOAT2(m_screenSpaceSize.x/2.0f*screenSpaceX+m_screenSpacePos.x, m_screenSpaceSize.y/2.0f*(-screenSpaceY)+m_screenSpacePos.y),
					FLOAT2(0.009f, 0.016f),
					0));
			}
			else
			{
				m_playerPositions[heroTypeCounter-1]->setPosition(FLOAT2(m_screenSpaceSize.x/2.0f*screenSpaceX+m_screenSpacePos.x, m_screenSpaceSize.y/2.0f*(-screenSpaceY)+m_screenSpacePos.y));
			}
			break;

		case ServerEntity::EnemyType:
			screenSpaceX = _entites[i]->m_model->getPosition().x/(m_terrainMax.x-m_terrainMin.x)*2.0f-1.0f;
			screenSpaceY = _entites[i]->m_model->getPosition().z/(m_terrainMax.y-m_terrainMin.y)*2.0f-1.0f;
			enemyTypeCounter++;
			if(enemyTypeCounter > m_enemyPositions.size())
			{
				m_enemyPositions.push_back(g_graphicsEngine->createSprite("minimap/enemy_pos.png",
					FLOAT2(m_screenSpaceSize.x/2.0f*screenSpaceX+m_screenSpacePos.x, m_screenSpaceSize.y/2.0f*(-screenSpaceY)+m_screenSpacePos.y),
					FLOAT2(0.009f, 0.016f),
					0));
			}
			else
			{
				m_enemyPositions[enemyTypeCounter-1]->setPosition(FLOAT2(m_screenSpaceSize.x/2.0f*screenSpaceX+m_screenSpacePos.x, m_screenSpaceSize.y/2.0f*(-screenSpaceY)+m_screenSpacePos.y));
			}
			break;
		}
	}
	
	while(heroTypeCounter < m_playerPositions.size())
	{
		g_graphicsEngine->removeSprite(m_playerPositions.back());
		m_playerPositions.pop_back();
	}
	while(enemyTypeCounter < m_enemyPositions.size())
	{
		g_graphicsEngine->removeSprite(m_enemyPositions.back());
		m_enemyPositions.pop_back();
	}
	
	screenSpaceX = _cameraPos.x/(m_terrainMax.x-m_terrainMin.x)*2.0f-1.0f;
	screenSpaceY = _cameraPos.y/(m_terrainMax.y-m_terrainMin.y)*2.0f-1.0f;
	m_view->setPosition(FLOAT2(m_screenSpaceSize.x/2.0f*screenSpaceX+m_screenSpacePos.x, m_screenSpaceSize.y/2.0f*(-screenSpaceY)+m_screenSpacePos.y));
}