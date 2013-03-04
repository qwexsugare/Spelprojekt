#include "Skill.h"

Skill::Skill()
{
	m_id = -1;
	m_currentCooldown = 0.0f;
	m_cooldown = 0.0f;
	this->m_range = 0.0f;
}

Skill::Skill(int _id, float _cooldown)
{
	m_id = _id;
	m_currentCooldown = 0;
	m_cooldown = _cooldown;
	this->m_range = 0.0f;
}

Skill::~Skill()
{

}

void Skill::update(float _dt)
{
	m_currentCooldown = max(m_currentCooldown-_dt, 0.0f);
	this->updateSpecificSkill(_dt);
}

bool Skill::activate(unsigned int _senderId)
{
	return false;
}

bool Skill::activate(unsigned int _targetId, unsigned int _senderId)
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
	
	return false;
}

bool Skill::activate(FLOAT3 position, unsigned int _senderId)
{
	return false;
}

void Skill::resetCooldown()
{
	m_currentCooldown = m_cooldown;
}

float Skill::getRange()
{
	return this->m_range;
}

void Skill::setRange(float _range)
{
	this->m_range = _range;
}