#include "ReadyAimFire.h"

float ReadyAimFire::RANGE = 2.0f;

ReadyAimFire::ReadyAimFire() : Skill(Skill::READY_AIM_FIRE, 0)
{

}

ReadyAimFire::~ReadyAimFire()
{

}

bool ReadyAimFire::activate(unsigned int _senderId)
{
	this->m_senderId = _senderId;
	return true;
}

void ReadyAimFire::updateSpecificSkill(float dt)
{
	ServerEntity *caster = EntityHandler::getServerEntity(this->m_senderId);

	if(caster != NULL)
	{
		FLOAT3 position = caster->getPosition();

		vector<ServerEntity*> turrets = EntityHandler::getEntitiesByType(ServerEntity::TowerType);

		for(int i = 0; i < turrets.size(); i++)
		{
			if((turrets[i]->getPosition() - position).length() <= ReadyAimFire::RANGE)
			{
				((Turret*)turrets[i])->setReadyAimFire(0.05f * ((UnitEntity*)caster)->getAgility());
			}
			else
			{
				((Turret*)turrets[i])->setReadyAimFire(0.0f);
			}
		}
	}
}