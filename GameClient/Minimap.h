#pragma once

#include "Sprite.h"

class Minimap
{
private:
	Sprite* m_sprite;
	FLOAT2 m_screenSpacePos;
	FLOAT2 m_screenSpaceSize;
public:
	Minimap();
	Minimap(string _file);
	~Minimap();
	
	bool isMouseInMap(INT2 _mousePos)const;
	FLOAT2 getTerrainPos(INT2 _mousePos, FLOAT2 _terrainMin, FLOAT2 _terrainMax)const;
};