#include "TowerPlacer.h"
#include "Input.h"
#include "Skill.h"
#include "EntityHandler.h"
#include "Turrets.h"

BoundingOrientedBox* TowerPlacer::m_deathPulseTurretObb;
BoundingOrientedBox* TowerPlacer::m_frostTurretObb;
BoundingOrientedBox* TowerPlacer::m_poisonTurretObb;
BoundingOrientedBox* TowerPlacer::m_teslaChainTurretObb;
FLOAT3 TowerPlacer::m_deathPulseTurretObbOffset;
FLOAT3 TowerPlacer::m_frostTurretObbOffset;
FLOAT3 TowerPlacer::m_poisonTurretObbOffset;
FLOAT3 TowerPlacer::m_teslaChainTurretObbOffset;

void TowerPlacer::init()
{
	Model* temp;
	
	temp = g_graphicsEngine->createModel("DeathTurret", FLOAT3(0,0,0));
	TowerPlacer::m_deathPulseTurretObb = new BoundingOrientedBox(*temp->getObb());
	m_deathPulseTurretObbOffset = FLOAT3(temp->getObb()->Center.x, temp->getObb()->Center.y, temp->getObb()->Center.z);
	g_graphicsEngine->removeModel(temp);

	temp = g_graphicsEngine->createModel("FrostTurret", FLOAT3(0,0,0));
	TowerPlacer::m_frostTurretObb = new BoundingOrientedBox(*temp->getObb());
	m_frostTurretObbOffset = FLOAT3(temp->getObb()->Center.x, temp->getObb()->Center.y, temp->getObb()->Center.z);
	g_graphicsEngine->removeModel(temp);

	temp = g_graphicsEngine->createModel("PoisonTurret", FLOAT3(0,0,0));
	TowerPlacer::m_poisonTurretObb = new BoundingOrientedBox(*temp->getObb());
	m_poisonTurretObbOffset = FLOAT3(temp->getObb()->Center.x, temp->getObb()->Center.y, temp->getObb()->Center.z);
	g_graphicsEngine->removeModel(temp);

	temp = g_graphicsEngine->createModel("LightningTurret", FLOAT3(0,0,0));
	TowerPlacer::m_teslaChainTurretObb = new BoundingOrientedBox(*temp->getObb());
	m_teslaChainTurretObbOffset = FLOAT3(temp->getObb()->Center.x, temp->getObb()->Center.y, temp->getObb()->Center.z);
	g_graphicsEngine->removeModel(temp);
}

void TowerPlacer::place(Skill::SKILLS _towerType, const FLOAT3& _pos)
{
	vector<ServerEntity*> entities = EntityHandler::getEntities();
	bool validPos = true;
	switch(_towerType)
	{
	case Skill::DEATH_PULSE_TURRET:
		TowerPlacer::m_deathPulseTurretObb->Center = XMFLOAT3(_pos.x+m_deathPulseTurretObbOffset.x, _pos.y+m_deathPulseTurretObbOffset.y, _pos.z+m_deathPulseTurretObbOffset.z);
		for(int i = 0; i < entities.size(); i++)
		{
			if(entities[i]->intersects(*TowerPlacer::m_deathPulseTurretObb))
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
		TowerPlacer::m_frostTurretObb->Center = XMFLOAT3(_pos.x+m_frostTurretObbOffset.x, _pos.y+m_frostTurretObbOffset.y, _pos.z+m_frostTurretObbOffset.z);
		for(int i = 0; i < entities.size(); i++)
		{
			if(entities[i]->intersects(*TowerPlacer::m_frostTurretObb))
			{
				validPos = false;
				i = entities.size();
			}
		}
		if(validPos)
		{
			EntityHandler::addEntity(new FrostTurret(_pos));
		}
		break;
	case Skill::TESLA_CHAIN_TURRET:
		TowerPlacer::m_teslaChainTurretObb->Center = XMFLOAT3(_pos.x+m_teslaChainTurretObbOffset.x, _pos.y+m_teslaChainTurretObbOffset.y, _pos.z+m_teslaChainTurretObbOffset.z);
		for(int i = 0; i < entities.size(); i++)
		{
			if(entities[i]->intersects(*TowerPlacer::m_teslaChainTurretObb))
			{
				validPos = false;
				i = entities.size();
			}
		}
		if(validPos)
		{
			EntityHandler::addEntity(new TeslaChainTurret(_pos, 9001, 9001));
		}
		break;
	case Skill::POISON_TURRET:
		TowerPlacer::m_poisonTurretObb->Center = XMFLOAT3(_pos.x+m_poisonTurretObbOffset.x, _pos.y+m_poisonTurretObbOffset.y, _pos.z+m_poisonTurretObbOffset.z);
		for(int i = 0; i < entities.size(); i++)
		{
			if(entities[i]->intersects(*TowerPlacer::m_poisonTurretObb))
			{
				validPos = false;
				i = entities.size();
			}
		}
		if(validPos)
		{
			EntityHandler::addEntity(new PoisonTurret(_pos));
		}
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