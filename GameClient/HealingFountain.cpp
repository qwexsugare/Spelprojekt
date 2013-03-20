#include "HealingFountain.h"

const float HealingFountain::RANGE = 4.0f;

HealingFountain::HealingFountain(FLOAT3 _pos) : ServerEntity(_pos)
{ 
	this->m_bs = new BoundingSphere(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), HealingFountain::RANGE);
	this->m_visible = false;
	this->m_type = ServerEntity::OtherType;
	this->m_timeSinceLastTick = 0.0f;
}

HealingFountain::~HealingFountain()
{

}

void HealingFountain::update(float _dt)
{
	this->m_timeSinceLastTick += _dt;

	if(this->m_timeSinceLastTick >= 1.0f)
	{
		this->m_timeSinceLastTick -= 1.0f;

		vector<ServerEntity*> heroes = EntityHandler::getEntitiesByType(ServerEntity::HeroType);

		for(int i = 0; i < heroes.size(); i++)
		{
			if(heroes[i]->intersects(*this->m_bs) == true)
			{
				((UnitEntity*)heroes[i])->heal((float)((UnitEntity*)heroes[i])->getMaxHealth() / 60.0f);
				this->m_messageQueue->pushOutgoingMessage(new CreateActionMessage(Skill::HEALING_FOUNTAIN, heroes[i]->getId(), heroes[i]->getPosition()));
			}
		}
	}
}