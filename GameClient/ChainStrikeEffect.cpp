#include "ChainStrikeEffect.h"
#include "EntityHandler.h"
#include "SoundWrapper.h"

const FLOAT ChainStrikeEffect::TIME_BETWEEN_JUMPS = 1.5f;

ChainStrikeEffect::ChainStrikeEffect(unsigned int _firstTarget, int _maxJumps, int _baseDamage, unsigned int _masterId)
{
	m_masterId = _masterId;
	m_firstTarget = _firstTarget;
	m_maxJumps = _maxJumps;
	this->m_type = OtherType;
	this->m_obb = new BoundingOrientedBox();
	m_visible = false;
	m_jumpTimer = 0.0f;
	m_jumps = 0;
	m_baseDamage = _baseDamage;

	ServerEntity* target = EntityHandler::getServerEntity(m_firstTarget);
	if(target)
	{
		m_position = target->getPosition();
		target->takeDamage(m_masterId, 0, m_baseDamage/(++m_jumps));
		this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::CHAIN_STRIKE_FIRST_EXCEPTION, m_masterId, m_position));

		// If max number of jumps is reached, delete me
		if(m_jumps == m_maxJumps)
			this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
		else
			m_invalidTargets.push_back(m_firstTarget);

		m_jumpTimer = TIME_BETWEEN_JUMPS;
	}
	// No target was found, delete me
	else
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}

ChainStrikeEffect::~ChainStrikeEffect()
{

}

void ChainStrikeEffect::update(float _dt)
{
	m_jumpTimer = max(m_jumpTimer-_dt, 0.0f);

	if(m_jumpTimer == 0.0f)
	{
		// First remove invalid target indices that no longer exists on the battlefield
		for(int i = 0; i < m_invalidTargets.size(); i++)
		{
			if(!EntityHandler::getServerEntity(m_invalidTargets[i]))
			{
				m_invalidTargets.erase(m_invalidTargets.begin() + i);
				i--;
			}
		}

		// Time to find a new target
		ServerEntity* closestValidTarget = NULL;
		float distanceToClosestValidTarget = 0.0f;
		vector<ServerEntity*> enemies = EntityHandler::getEntitiesByType(ServerEntity::EnemyType);
		for(int i = 0; i < enemies.size(); i++)
		{
			bool enemyIsValidTarget = true;

			for(int j = 0; j < m_invalidTargets.size() && enemyIsValidTarget; j++)
			{
				if(enemies[i] == EntityHandler::getServerEntity(m_invalidTargets[j]))
				{
					enemyIsValidTarget = false;
				}
			}

			if(enemyIsValidTarget)
			{
				// If a valid target has been found before, compare the distance between it and this effect to the distance between this one and this effect. 
				if(closestValidTarget)
				{
					float distance = D3DXVec2Length(&D3DXVECTOR2(m_position.x - enemies[i]->getPosition().x, m_position.z - enemies[i]->getPosition().z));
					if(distance < distanceToClosestValidTarget)
					{
						closestValidTarget = enemies[i];
						distanceToClosestValidTarget = distance;
					}
				}
				// Else this was the first valid target found and it will be the closest valid target
				else
				{
					closestValidTarget = enemies[i];
					distanceToClosestValidTarget = D3DXVec2Length(&D3DXVECTOR2(m_position.x - closestValidTarget->getPosition().x, m_position.z - closestValidTarget->getPosition().z));
				}
			}
		}

		if(closestValidTarget && distanceToClosestValidTarget <= MAX_JUMP_DISTANCE)
		{
			m_position = closestValidTarget->getPosition();
			closestValidTarget->takeDamage(m_masterId, 0, m_baseDamage/(++m_jumps));

			// If max number of jumps is reached, delete me
			if(m_jumps == m_maxJumps)
				this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
			else
				m_invalidTargets.push_back(closestValidTarget->getId());

			this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::CHAIN_STRIKE, m_masterId, m_position));
		}
		// No target was found, delete me
		else
		{
			this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
		}

		m_jumpTimer = TIME_BETWEEN_JUMPS;
	}
}