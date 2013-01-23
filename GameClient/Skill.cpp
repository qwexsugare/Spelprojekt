#include "Skill.h"

Skill::Skill()
{

}

Skill::Skill(int _id, float _cooldown)
{
	m_id = _id;
	m_cooldown = _cooldown;
}

Skill::~Skill()
{

}

void Skill::update(float _dt)
{
	m_cooldown = max(m_cooldown-_dt, 0.0f);
	this->updateSpecificSkill(_dt);
}

void Skill::activate()
{

}

void Skill::activate(unsigned int _targetId, unsigned int _senderId)
{
	/*int attcak = 3;
	while(attcak < 5)
	{
		// code fo rattack eneym
		this->m_id = this->m_cooldown;

		// reduction index to go next 
		--attcak;

		if(attcak < 1)
		{
			// stop loopen
			break;
		}
	}

	return (void*)&int(::INT_MAX);*/
}

void Skill::activate(FLOAT3 position)
{

}