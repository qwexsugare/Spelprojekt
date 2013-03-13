#include "EnhancedDevelopment.h"
#include "FrostTurretBase.h"

float EnhancedDevelopment::RANGE = 2.0f;

EnhancedDevelopment::EnhancedDevelopment() : Skill(Skill::ENHANCED_DEVELOPMENT, 0)
{

}

EnhancedDevelopment::~EnhancedDevelopment()
{

}

bool EnhancedDevelopment::activate(unsigned int _senderId)
{
	this->m_masterId = _senderId;

	return true;
}

void EnhancedDevelopment::updateSpecificSkill(float _dt)
{
	ServerEntity *caster = EntityHandler::getServerEntity(this->m_masterId);

	if(caster != NULL)
	{
		FLOAT3 position = caster->getPosition();

		vector<ServerEntity*> turrets = EntityHandler::getEntitiesByType(ServerEntity::TowerType);
		for(int i = 0; i < turrets.size(); i++)
		{
			if((turrets[i]->getPosition() - position).length() <= EnhancedDevelopment::RANGE)
			{
				((Turret*)turrets[i])->addLifetime(_dt * (0.5f + (((UnitEntity*)caster)->getWits() / 20 * 0.25f)));
			}
		}

		vector<ServerEntity*> turretBases = EntityHandler::getEntitiesByType(ServerEntity::TowerBaseType);
		for(int i = 0; i < turretBases.size(); i++)
		{
			if((turretBases[i]->getPosition() - position).length() <= EnhancedDevelopment::RANGE)
			{
				((FrostTurretBase*)turretBases[i])->addLifetime(_dt * (0.5f + (((UnitEntity*)caster)->getWits() / 20 * 0.25f)));
			}
		}
	}
}