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
	virtual void activate(unsigned int _targetId, unsigned int _senderId);
	virtual void activate(FLOAT3 position);
	float getCooldown()const { return m_cooldown; }
	int getId()const { return m_id; }
	void setCooldown(int _cooldown) { m_cooldown = _cooldown; }
	void update(float _dt);
	virtual void updateSpecificSkill(float _dt) = 0;
};