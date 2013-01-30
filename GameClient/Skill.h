#pragma once

#include "ServerEntity.h"

class Skill
{
private:
	int m_id;
	float m_cooldown;
	float m_currentCooldown;
public:
	static enum SKILLS {DEMONIC_PRESENCE, HEALING_TOUCH, MOVE, ATTACK, CHAIN_STRIKE, CLOUD_OF_DARKNESS, STUNNING_STRIKE, TELEPORT, AIM, DEADLY_STRIKE, GREED, LIFESTEALING_STRIKE, MENTAL_RESISTANCE, PHYSICAL_RESISTANCE, POISON_STRIKE, DEATH_TOWER};

	Skill();
	Skill(int _id, float _cooldown);
	virtual ~Skill();
	
	virtual bool activate(unsigned int _senderId);
	virtual bool activate(unsigned int _targetId, unsigned int _senderId);
	virtual bool activate(FLOAT3 position, unsigned int _senderId);
	float getCurrentCooldown()const { return m_currentCooldown; }
	int getId()const { return m_id; }
	void resetCooldown();
	void update(float _dt);
	virtual void updateSpecificSkill(float _dt) = 0;
};