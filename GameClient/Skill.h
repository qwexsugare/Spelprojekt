#pragma once

#include "ServerEntity.h"

class Skill
{
private:
	int m_id;
	float m_cooldown;
	float m_currentCooldown;
	float m_range;
public:
	static enum SKILLS {
		IDLE,
		DEATH,
		MOVE, 
		ATTACK, 
		MELEE_ATTACK,
		RANGED_ATTACK,
		AOE_MELEE_ATTACK,
		AOE_ATTACK,
		STRENGTH,
		AGILITY,
		WITS,
		FORTITUDE,
		TURRET_CONSTRUCTION,
		AIM,
		DEADLY_STRIKE, 
		GREED, 
		LIFESTEALING_STRIKE, 
		MENTAL_RESISTANCE, 
		PHYSICAL_RESISTANCE, 
		POISON_STRIKE, 
		TURRET_LIFE,
		CHAIN_STRIKE, 
		STUNNING_STRIKE, 
		CLOUD_OF_DARKNESS, 
		HEALING_TOUCH,
		DEMONIC_PRESENCE,
		TELEPORT,
		WALL,
		ENIGMATIC_PRESENCE,
		SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR,
		COURAGE_HONOR_VALOR,
		TARGET_ACQUIRED_PERMISSION_TO_FIRE,
		READY_AIM_FIRE,
		TIME_IS_MONEY,
		ENHANCED_DEVELOPMENT,
		LIFE_REGEN,
		SIMONS_EVIL,
		TESLA_CHAIN_TURRET,
		FROST_TURRET,
		POISON_ATTACK,
		HYPNOTIC_STARE,
		DEATH_PULSE_TURRET,
		POISON_TURRET,
		FROST_TURRET_PROJECTILE,
		POISON_TURRET_PROJECTILE,
		DEATH_PULSE_TURRET_PROJECTILE,
		NR_OF_SKILLS
		};

	Skill();
	Skill(int _id, float _cooldown);
	virtual ~Skill();
	
	virtual bool activate(unsigned int _senderId);
	virtual bool activate(unsigned int _targetId, unsigned int _senderId);
	virtual bool activate(FLOAT3 position, unsigned int _senderId);
	float getCurrentCooldown()const { return m_currentCooldown; }
	float getCooldown()const { return this->m_cooldown; }
	float getRange();
	void setRange(float _range);
	int getId()const { return m_id; }
	void resetCooldown();
	void update(float _dt);
	virtual void updateSpecificSkill(float _dt) = 0;
};