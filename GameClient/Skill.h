#pragma once

#include "ServerEntity.h"

class Skill
{
private:
	int m_id;
	float m_cooldown;
public:
	Skill();
	Skill(int _id, float _cooldown);
	virtual ~Skill();
	
	virtual void activate();
	virtual void activate(unsigned int _targetId);
	virtual void activate(FLOAT3 position);
	float getCooldown()const { return m_cooldown; }
	int getId()const { return m_id; }
	void update(float _dt);
	virtual void updateSpecificSkill(float _dt) = 0;
};