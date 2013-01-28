#pragma once

#include "ServerEntity.h"

class Skill
{
private:
	int m_id;
	float m_cooldown;
	float m_currentCooldown;
public:
	static enum SKILLS {MOVE, ATTACK, CHAIN_STRIKE, CLOUD_OF_DARKNESS, STUNNING_STRIKE, TELEPORT};

	Skill();
	Skill(int _id, float _cooldown);
	virtual ~Skill();
	
	virtual void activate(unsigned int _senderId);
	virtual void activate(unsigned int _targetId, unsigned int _senderId);
	virtual void activate(FLOAT3 position, unsigned int _senderId);
	float getCurrentCooldown()const { return m_currentCooldown; }
	int getId()const { return m_id; }
	void resetCooldown();
	void update(float _dt);
	virtual void updateSpecificSkill(float _dt) = 0;
};