#include "StunningStrikeEffect.h"
#include "EntityHandler.h"
#include "MyAlgorithms.h"
#include "Skill.h"

StunningStrikeEffect::StunningStrikeEffect(FLOAT3 _position, unsigned int _masterId)
{
	m_position = _position;
	
	this->m_obb = NULL;
	this->m_bs = new BoundingSphere(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), AOE);
	m_visible = false;
	m_timer = 0.0f;
	m_type = OtherType;

	UnitEntity *ue = (UnitEntity*)EntityHandler::getServerEntity(_masterId);

	vector<ServerEntity*> enemies = EntityHandler::getAllEnemies();

	for(int i = 0; i < enemies.size(); i++)
	{
		if(random(1, 100) <= 40 + ue->getStrength())
		{
			ServerEntity* enemy = (enemies)[i];
			if(enemy->getObb())
			{
				if(enemy->getObb()->Intersects(*m_bs))
				{
					((UnitEntity*)(enemies)[i])->stun(8);
					this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::STUNNING_STRIKE_VICTIM, enemies[i]->getId(), FLOAT3(0.0f, 0.0f, 0.0f)));
				}
			}
			else if(enemy->getBs())
			{
				if(enemy->getBs()->Intersects(*m_bs))
				{
					((UnitEntity*)(enemies)[i])->stun(8);
					this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::STUNNING_STRIKE_VICTIM, enemies[i]->getId(), FLOAT3(0.0f, 0.0f, 0.0f)));
				}
			}
		}
	}
	
	this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::STUNNING_STRIKE, _masterId, _position));
}

StunningStrikeEffect::~StunningStrikeEffect()
{

}

void StunningStrikeEffect::update(float _dt)
{
	m_timer += _dt;

	if(m_timer >= LIFETIME)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}