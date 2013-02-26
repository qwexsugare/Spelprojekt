#pragma once

#include "Entity.h"
#include "client.h"
#include "Graphics.h"
#include "Skill.h"

class TowerPlacer
{
private:
	static BoundingOrientedBox* m_deathPulseTurretObb;
	static BoundingOrientedBox* m_frostTurretObb;
	static BoundingOrientedBox* m_poisonTurretObb;
	static BoundingOrientedBox* m_teslaChainTurretObb;
public:
	static void init();
	static void place(Skill::SKILLS _towerType, const FLOAT3& _pos);
	static void release();
};