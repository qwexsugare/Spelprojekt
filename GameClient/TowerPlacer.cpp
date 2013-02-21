#include "TowerPlacer.h"
#include "Input.h"
#include "Skill.h"
#include "EntityHandler.h"
#include "Tower.h"

BoundingOrientedBox* TowerPlacer::m_deathTowerObb;

void TowerPlacer::init()
{
	Model* deathTower = g_graphicsEngine->createModel("DeathTurret", FLOAT3(0,0,0));
	TowerPlacer::m_deathTowerObb = new BoundingOrientedBox(*deathTower->getObb());
	g_graphicsEngine->removeModel(deathTower);
}

void TowerPlacer::place(Skill::SKILLS _towerType, const FLOAT3& _pos)
{
	TowerPlacer::m_deathTowerObb->Center = XMFLOAT3(_pos.x, _pos.y, _pos.z);
		
	vector<ServerEntity*> entities = EntityHandler::getEntities();
	bool validPos = true;
	for(int i = 0; i < entities.size(); i++)
	{
		if(entities[i]->contains(*TowerPlacer::m_deathTowerObb) != ContainmentType::DISJOINT)
		{
			validPos = false;
			i = entities.size();
		}
	}

	if(validPos)
	{
		EntityHandler::addEntity(new Tower(_pos));
	}
}

void TowerPlacer::release()
{
	delete TowerPlacer::m_deathTowerObb;
}