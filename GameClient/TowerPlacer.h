#pragma once

#include "Entity.h"
#include "client.h"
#include "Graphics.h"
#include "Skill.h"

class TowerPlacer
{
private:
	static BoundingOrientedBox* m_deathTowerObb;
public:
	static void init();
	static void place(Skill::SKILLS _towerType, const FLOAT3& _pos);
	static void release();
};