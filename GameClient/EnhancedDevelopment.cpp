#include "EnhancedDevelopment.h"

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
				((Turret*)turrets[i])->addLifetime(_dt * 0.75f);
			}
		}
	}
}