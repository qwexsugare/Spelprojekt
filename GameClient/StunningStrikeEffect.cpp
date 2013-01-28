#include "StunningStrikeEffect.h"
#include "EntityHandler.h"
#include "MyAlgorithms.h"

StunningStrikeEffect::StunningStrikeEffect(FLOAT3 _position)
{
	m_position = _position;

	this->m_obb = new BoundingOrientedBox();
	m_modelId = 0;
	m_timer = 0.0f;
	m_type = OtherType;

	vector<ServerEntity*>* enemies = EntityHandler::getAllEnemies();

	for(int i = 0; i < enemies->size(); i++)
	{
		if(((*enemies)[i]->getPosition()-m_position).length() <= AOE)
		{
			if(random(1, 100) <= 50)
			{
				((UnitEntity*)(*enemies)[i])->stun(8);
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