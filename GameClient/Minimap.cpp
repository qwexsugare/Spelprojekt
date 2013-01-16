#include "Minimap.h"
#include "Graphics.h"

Minimap::Minimap()
{

}

Minimap::Minimap(string _file)
{
	m_screenSpacePos = FLOAT2(0.84f, 0.72f);
	m_screenSpaceSize = FLOAT2(0.28f, 0.5f);
	m_sprite = g_graphicsEngine->createSprite(_file, m_screenSpacePos, m_screenSpaceSize, 0);
}

Minimap::~Minimap()
{
	g_graphicsEngine->removeSprite(m_sprite);
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

FLOAT2 Minimap::getTerrainPos(INT2 _mousePos, FLOAT2 _terrainMin, FLOAT2 _terrainMax)const
{
	float mouseX = (_mousePos.x/float(g_graphicsEngine->getRealScreenSize().x)*2.0f-1.0f);
	float mouseY = (_mousePos.y/float(g_graphicsEngine->getRealScreenSize().y)*2.0f-1.0f);

	FLOAT2 distanceFromMapStart = FLOAT2(
		mouseX-((m_screenSpacePos.x-m_screenSpaceSize.x/2.0f)),
		mouseY-((-m_screenSpacePos.y-m_screenSpaceSize.y/2.0f)));
	
	return FLOAT2(
		distanceFromMapStart.x/m_screenSpaceSize.x,
		distanceFromMapStart.y/m_screenSpaceSize.y)
		* (_terrainMax-_terrainMin) + _terrainMin;
}