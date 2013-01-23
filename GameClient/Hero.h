#ifndef HERO_H
#define HERO_H

#include "Datastructures.h"
#include "ServerEntity.h"
#include "EntityHandler.h"
#include "Projectile.h"

class Hero : public ServerEntity
{
private:
	int m_strength;
	int m_agility;
	int m_wits;
	int m_fortitude;

	FLOAT3 m_nextPosition;
	bool m_reachedPosition;
	float m_movementSpeed;

	unsigned int m_hp;
	unsigned int m_target;
	bool m_hasTarget;

	float m_attackRange;
	float m_attackCooldown;
public:
	Hero();
	virtual ~Hero();

	int getWits()const { return m_wits; }
	void update(float dt);
	void setNextPosition(FLOAT3 _nextPosition);
	void setTarget(unsigned int _target);
	FLOAT3 getDirection();
	
	void takeDamage(int damage);
};

#endif