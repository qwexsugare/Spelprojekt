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
	static FLOAT3 m_deathPulseTurretObbOffset;
	static FLOAT3 m_frostTurretObbOffset;
	static FLOAT3 m_poisonTurretObbOffset;
	static FLOAT3 m_teslaChainTurretObbOffset;
public:
	static const int PLACE_RANGE = 5;

	static void init();
	static void place(Skill::SKILLS _towerType, const FLOAT3& _pos, const FLOAT3& _origin);
	static void release();
};

