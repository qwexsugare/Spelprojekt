#include "TowerPlacer.h"
#include "Input.h"
#include "Skill.h"
#include "EntityHandler.h"
#include "Turrets.h"

BoundingOrientedBox* TowerPlacer::m_deathPulseTurretObb;
BoundingOrientedBox* TowerPlacer::m_frostTurretObb;
BoundingOrientedBox* TowerPlacer::m_poisonTurretObb;
BoundingOrientedBox* TowerPlacer::m_teslaChainTurretObb;

void TowerPlacer::init()
{
	Model* temp;
	
	temp = g_graphicsEngine->createModel("DeathTurret", FLOAT3(0,0,0));
	TowerPlacer::m_deathPulseTurretObb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);

	temp = g_graphicsEngine->createModel("FrostTurret", FLOAT3(0,0,0));
	TowerPlacer::m_frostTurretObb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);

	temp = g_graphicsEngine->createModel("PoisonTurret", FLOAT3(0,0,0));
	TowerPlacer::m_poisonTurretObb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);

	temp = g_graphicsEngine->createModel("LightningTurret", FLOAT3(0,0,0));
	TowerPlacer::m_teslaChainTurretObb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);
}

void TowerPlacer::place(Skill::SKILLS _towerType, const FLOAT3& _pos)
{
	vector<ServerEntity*> entities = EntityHandler::getEntities();
	bool validPos = true;
	switch(_towerType)
	{
	case Skill::DEATH_PULSE_TURRET:
		TowerPlacer::m_deathPulseTurretObb->Center = XMFLOAT3(_pos.x, _pos.y, _pos.z);
		for(int i = 0; i < entities.size(); i++)
		{
			if(entities[i]->contains(*TowerPlacer::m_deathPulseTurretObb) != ContainmentType::DISJOINT)
			{
				validPos = false;
				i = entities.size();
			}
		}
		if(validPos)
		{
			EntityHandler::addEntity(new DeathPulseTurret(_pos));
		}
		break;
	case Skill::FROST_TURRET:
		break;
	}

}

void TowerPlacer::release()
{
	delete TowerPlacer::m_deathPulseTurretObb;
	delete TowerPlacer::m_frostTurretObb;
	delete TowerPlacer::m_poisonTurretObb;
	delete TowerPlacer::m_teslaChainTurretObb;
}