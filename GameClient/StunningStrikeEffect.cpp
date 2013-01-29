#include "StunningStrikeEffect.h"
#include "EntityHandler.h"
#include "MyAlgorithms.h"

StunningStrikeEffect::StunningStrikeEffect(FLOAT3 _position)
{
	m_position = _position;
	
	this->m_obb = NULL;
	this->m_bs = new BoundingSphere(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), AOE);
	m_visible = false;
	m_timer = 0.0f;
	m_type = OtherType;

	vector<ServerEntity*>* enemies = EntityHandler::getAllEnemies();

	for(int i = 0; i < enemies->size(); i++)
	{
		if(random(1, 100) <= 50)
		{
			ServerEntity* enemy = (*enemies)[i];
			if(enemy->getObb())
			{
				if(enemy->getObb()->Intersects(*m_bs))
				{
					((UnitEntity*)(*enemies)[i])->stun(8);
				}
			}
			else if(enemy->getBs())
			{
				if(enemy->getBs()->Intersects(*m_bs))
				{
					((UnitEntity*)(*enemies)[i])->stun(8);
				}
			}
		}
	}

	delete enemies;
}

StunningStrikeEffect::~StunningStrikeEffect()
{

}

void StunningStrikeEffect::update(float _dt)
{
	m_timer += _dt;

	if(m_timer > LIFETIME)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}