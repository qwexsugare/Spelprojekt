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

	temp = g_graphicsEngine->createModel("FrostBase", FLOAT3(0,0,0));
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

bool TowerPlacer::place(Skill::SKILLS _towerType, const FLOAT3& _pos, const FLOAT3& _origin, UnitEntity *_creator)
{
	bool success = false;
	float distance = (_pos-_origin).length();
	if(distance <= PLACE_RANGE)
	{
		switch(_towerType)
		{
		case Skill::DEATH_PULSE_TURRET:
			TowerPlacer::m_deathPulseTurretObb->Center = XMFLOAT3(_pos.x+m_deathPulseTurretObbOffset.x, _pos.y+m_deathPulseTurretObbOffset.y, _pos.z+m_deathPulseTurretObbOffset.z);
			if(!EntityHandler::intersects(*TowerPlacer::m_deathPulseTurretObb))
			{
				success = true;
				EntityHandler::addEntity(new DeathPulseTurret(_pos, _creator));
			}
			break;
		case Skill::FROST_TURRET:
			TowerPlacer::m_frostTurretObb->Center = XMFLOAT3(_pos.x+m_frostTurretObbOffset.x, _pos.y+m_frostTurretObbOffset.y, _pos.z+m_frostTurretObbOffset.z);
			if(!EntityHandler::intersects(*TowerPlacer::m_frostTurretObb))
			{
				success = true;
				EntityHandler::addEntity(new FrostTurret(_pos, _creator));
				EntityHandler::addEntity(new FrostTurretBase(_pos, _creator->getTurretDuration() * 20));
			}
			break;
		case Skill::TESLA_CHAIN_TURRET:
			TowerPlacer::m_teslaChainTurretObb->Center = XMFLOAT3(_pos.x+m_teslaChainTurretObbOffset.x, _pos.y+m_teslaChainTurretObbOffset.y, _pos.z+m_teslaChainTurretObbOffset.z);
			if(!EntityHandler::intersects(*TowerPlacer::m_teslaChainTurretObb))
			{
				success = true;
				EntityHandler::addEntity(new TeslaChainTurret(_pos, _creator));
			}
			break;
		case Skill::POISON_TURRET:
			TowerPlacer::m_poisonTurretObb->Center = XMFLOAT3(_pos.x+m_poisonTurretObbOffset.x, _pos.y+m_poisonTurretObbOffset.y, _pos.z+m_poisonTurretObbOffset.z);
			if(!EntityHandler::intersects(*TowerPlacer::m_poisonTurretObb))
			{
				success = true;
				EntityHandler::addEntity(new PoisonTurret(_pos, _creator));
			}
			break;
		}
	}
	return success;
}

void TowerPlacer::release()
{
	delete TowerPlacer::m_deathPulseTurretObb;
	delete TowerPlacer::m_frostTurretObb;
	delete TowerPlacer::m_poisonTurretObb;
	delete TowerPlacer::m_teslaChainTurretObb;
}