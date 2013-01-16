#include "Minimap.h"
#include "Graphics.h"

Minimap::Minimap()
{

}

Minimap::Minimap(string _file, FLOAT2 _terrainMin, FLOAT2 _terrainMax, FLOAT2 _cameraPos)
{
	m_terrainMin = _terrainMin;
	m_terrainMax = _terrainMax;
	m_screenSpacePos = FLOAT2(0.84f, 0.72f);
	m_screenSpaceSize = FLOAT2(0.28f, 0.5f);
	m_sprite = g_graphicsEngine->createSprite(_file, m_screenSpacePos, m_screenSpaceSize, 0);
	m_view = g_graphicsEngine->createSprite("maps\\view.png", m_screenSpacePos, FLOAT2(0.12f, 0.08f), 0);
}

Minimap::~Minimap()
{
	g_graphicsEngine->removeSprite(m_sprite);
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

void Minimap::update(const vector<Entity*>& _entites, FLOAT2 _cameraPos)
{
	for(int i = 0; i < m_enemyPositions.size(); i++)
		g_graphicsEngine->removeSprite(m_enemyPositions[i]);
	m_enemyPositions.resize(_entites.size());

	float screenSpaceX;
	float screenSpaceY;

	for(int i = 0; i < _entites.size(); i++)
	{
		switch(_entites[i]->m_type)
		{
		case ServerEntity::HeroType:
			screenSpaceX = _entites[i]->m_model->getPosition().x/(m_terrainMax.x-m_terrainMin.x)*2.0f-1.0f;
			screenSpaceY = _entites[i]->m_model->getPosition().z/(m_terrainMax.y-m_terrainMin.y)*2.0f-1.0f;
	
			m_enemyPositions[i] = g_graphicsEngine->createSprite("maps\\player_pos.png",
				FLOAT2(m_screenSpaceSize.x/2.0f*screenSpaceX+m_screenSpacePos.x, m_screenSpaceSize.y/2.0f*(-screenSpaceY)+m_screenSpacePos.y),
				FLOAT2(0.009f, 0.016f),
				0);
			break;

		case ServerEntity::EnemyType:
			screenSpaceX = _entites[i]->m_model->getPosition().x/(m_terrainMax.x-m_terrainMin.x)*2.0f-1.0f;
			screenSpaceY = _entites[i]->m_model->getPosition().z/(m_terrainMax.y-m_terrainMin.y)*2.0f-1.0f;
	
			m_enemyPositions[i] = g_graphicsEngine->createSprite("maps\\enemy_pos.png",
				FLOAT2(m_screenSpaceSize.x/2.0f*screenSpaceX+m_screenSpacePos.x, m_screenSpaceSize.y/2.0f*(-screenSpaceY)+m_screenSpacePos.y),
				FLOAT2(0.009f, 0.016f),
				0);
			break;
		}
	}
	
	screenSpaceX = _cameraPos.x/(m_terrainMax.x-m_terrainMin.x)*2.0f-1.0f;
	screenSpaceY = _cameraPos.y/(m_terrainMax.y-m_terrainMin.y)*2.0f-1.0f;
	
	m_view->setPosition(FLOAT2(m_screenSpaceSize.x/2.0f*screenSpaceX+m_screenSpacePos.x, m_screenSpaceSize.y/2.0f*(-screenSpaceY)+m_screenSpacePos.y));
}