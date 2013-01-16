#pragma once

#include "Sprite.h"
#include "Entity.h"

class Minimap
{
private:
	Sprite* m_sprite;
	vector<Sprite*> m_enemyPositions;
	FLOAT2 m_screenSpacePos;
	FLOAT2 m_screenSpaceSize;
	FLOAT2 m_terrainMax;
	FLOAT2 m_terrainMin;
public:
	Minimap();
	Minimap(string _file, FLOAT2 _terrainMin, FLOAT2 _terrainMax);
	~Minimap();
	
	bool isMouseInMap(INT2 _mousePos)const;
	FLOAT2 getTerrainPos(INT2 _mousePos)const;
	void update(const vector<Entity*>& _entites);
};