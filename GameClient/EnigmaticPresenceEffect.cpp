#include "EnigmaticPresenceEffect.h"
#include "EntityHandler.h"

const float EnigmaticPresenceEffect::MOVEMENT_SPEED_FACTOR = 0.05f;
map<unsigned int, float> EnigmaticPresenceEffect::m_affectedGuys;

EnigmaticPresenceEffect::EnigmaticPresenceEffect(unsigned int _caster)
{
	m_caster = _caster;

	this->m_obb = NULL;
	FLOAT3 pos = EntityHandler::getServerEntity(_caster)->getPosition();
	this->m_bs = new BoundingSphere(XMFLOAT3(pos.x, 0.0f, pos.z), AOE);
	m_visible = false;
	m_type = OtherType;
	
	ServerEntity* caster = EntityHandler::getServerEntity(m_caster);
	vector<ServerEntity*> enemies = EntityHandler::getAllEnemies();
	for(int i = 0; i < enemies.size(); i++)
	{
		bool alreadyAffected = false;
		for(map<unsigned int, float>::iterator iter = m_affectedGuys.begin(); iter != m_affectedGuys.end(); iter++)
		{
			if(enemies[i]->getId() == iter->first)
			{
				alreadyAffected = true;
				iter = m_affectedGuys.end();
				iter--;
			}
		}

		if(!alreadyAffected)
		{
			if((caster->getPosition()-enemies[i]->getPosition()).length() <= AOE)
			{
				float movementSpeedImpairment = -((UnitEntity*)caster)->getWits()*MOVEMENT_SPEED_FACTOR;
				m_affectedGuys[enemies[i]->getId()] = movementSpeedImpairment;
				((UnitEntity*)enemies.at(i))->alterMovementSpeed(movementSpeedImpairment);
				this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::ENIGMATIC_PRESENCE, 0, enemies[i]->getId(), enemies[i]->getPosition()));
			}
		}
	}
}

EnigmaticPresenceEffect::~EnigmaticPresenceEffect()
{

}

void EnigmaticPresenceEffect::update(float _dt)
{
	ServerEntity* caster = EntityHandler::getServerEntity(m_caster);

	if(caster)
	{
		vector<map<unsigned int, float>::iterator> removeIndices;

		// Check if any of the affected guys have died or escaped the aura area.
		for(map<unsigned int, float>::iterator iter = m_affectedGuys.begin(); iter != m_affectedGuys.end(); iter++)
		{
			ServerEntity* se = EntityHandler::getServerEntity(iter->first);
			// Check if the affected guy has died recently then remove it.
			if(!se)
			{
				removeIndices.push_back(iter);
				this->m_messageQueue->pushOutgoingMessage(new RemoveActionTargetMessage(Skill::ENIGMATIC_PRESENCE, 0, se->getId()));
			}
			// Else the affected guys is still alive and might have escaped the aura area and needs to be taken down!
			else if((caster->getPosition()-se->getPosition()).length() > AOE)
			{
				((UnitEntity*)se)->alterMovementSpeed(-iter->second);
				removeIndices.push_back(iter);
				this->m_messageQueue->pushOutgoingMessage(new RemoveActionTargetMessage(Skill::ENIGMATIC_PRESENCE, 0, se->getId()));
			}
		}

		for(int i = 0; i < removeIndices.size(); i++)
		{
			m_affectedGuys.erase(removeIndices[i]);
		}

		// Check if any newcomers want to join in on the oral (aural) fun.
		vector<ServerEntity*> enemies = EntityHandler::getAllEnemies();
		for(int i = 0; i < enemies.size(); i++)
		{
			bool alreadyAffected = false;
			for(map<unsigned int, float>::iterator iter = m_affectedGuys.begin(); iter != m_affectedGuys.end(); iter++)
			{
				if(enemies[i]->getId() == iter->first)
				{
					alreadyAffected = true;
					iter = m_affectedGuys.end();
					iter--;
				}
			}

			if(!alreadyAffected)
			{
				if((caster->getPosition()-enemies[i]->getPosition()).length() <= AOE)
				{
					float movementSpeedImpairment = -((UnitEntity*)caster)->getWits()*MOVEMENT_SPEED_FACTOR;
					m_affectedGuys[enemies[i]->getId()] = movementSpeedImpairment;
					((UnitEntity*)enemies.at(i))->alterMovementSpeed(movementSpeedImpairment);
					this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::ENIGMATIC_PRESENCE, 0, enemies[i]->getId(), enemies[i]->getPosition()));
				}
			}
		}
	}
}