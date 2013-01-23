#include "ChainStrikeEffect.h"
#include "EntityHandler.h"
#include "Graphics.h"
#include "SoundWrapper.h"

ChainStrikeEffect::ChainStrikeEffect(unsigned int _firstTarget, FLOAT3 _positon, int _maxJumps)
{
	m_firstTarget = _firstTarget;
	m_position = _positon;
	m_maxJumps = _maxJumps;
	this->m_type = OtherType;
	this->m_obb = new BoundingOrientedBox();
	m_modelId = 0;
	m_jumpTimer = 0.0f;
	m_jumps = 0;
	m_sound = createSoundHandle("knife.wav", false);
}

ChainStrikeEffect::~ChainStrikeEffect()
{
	deactivateSound(m_sound);
}

void ChainStrikeEffect::update(float _dt)
{
	m_jumpTimer-=_dt;

	if(m_jumpTimer <= 0.0f)
	{
		// If its the first jump we can use the first target variable to make a simpler algorithm.
		if(m_invalidTargets.size() == 0)
		{
			ServerEntity* target = EntityHandler::getServerEntity(m_firstTarget);

			if(target)
			{
				m_position = target->getPosition();
				target->takeDamage(200/(++m_jumps), false);
				playSound(m_sound);

				// If max number of jumps is reached, delete me
				if(m_jumps == m_maxJumps)
					this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
				else
					m_invalidTargets.push_back(m_firstTarget);
			}
			// No target was found, delete me
			else
			{
				this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
			}
		}
		// If its not the first jump we must get all enemies on the battlefield to find a target
		else
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
			vector<ServerEntity*>* enemies = EntityHandler::getAllEnemies();
			for(int i = 0; i < enemies->size(); i++)
			{
				bool enemyIsValidTarget = true;

				for(int j = 0; j < m_invalidTargets.size() && enemyIsValidTarget; j++)
				{
					if((*enemies)[i] == EntityHandler::getServerEntity(m_invalidTargets[j]))
					{
						enemyIsValidTarget = false;
					}
				}

				if(enemyIsValidTarget)
				{
					// If a valid target has been found before, compare the distance between it and this effect to the distance between this one and this effect. 
					if(closestValidTarget)
					{
						float distance = D3DXVec2Length(&D3DXVECTOR2(m_position.x - (*enemies)[i]->getPosition().x, m_position.z - (*enemies)[i]->getPosition().z));
						if(distance < distanceToClosestValidTarget)
						{
							closestValidTarget = (*enemies)[i];
							distanceToClosestValidTarget = distance;
						}
					}
					// Else this was the first valid target found and it will be the closest valid target
					else
					{
						closestValidTarget = (*enemies)[i];
						distanceToClosestValidTarget = D3DXVec2Length(&D3DXVECTOR2(m_position.x - closestValidTarget->getPosition().x, m_position.z - closestValidTarget->getPosition().z));
					}
				}
			}

			if(closestValidTarget && distanceToClosestValidTarget < MAX_JUMP_DISTANCE)
			{
				m_position = closestValidTarget->getPosition();
				closestValidTarget->takeDamage(200/(++m_jumps), false);
				playSound(m_sound);

				// If max number of jumps is reached, delete me
				if(m_jumps == m_maxJumps)
					this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
				else
					m_invalidTargets.push_back(closestValidTarget->getId());
			}
			// No target was found, delete me
			else
			{
				this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
			}

			delete enemies;
		}

		m_jumpTimer = 0.5f;
	}
}