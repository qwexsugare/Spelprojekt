#ifndef HERO_H
#define HERO_H

#include "Datastructures.h"
#include "UnitEntity.h"
#include "ServerEntity.h"
#include "EntityHandler.h"
#include "Projectile.h"

class Hero : public UnitEntity
{
private:
	FLOAT3 m_nextPosition;
	bool m_reachedPosition;

	unsigned int m_target;
	bool m_hasTarget;

	float m_attackRange;
	float m_attackCooldown;
public:
	Hero();
	virtual ~Hero();
	
	void updateSpecificUnitEntity(float dt);
	void setNextPosition(FLOAT3 _nextPosition);
	void setTarget(unsigned int _target);
	FLOAT3 getDirection();
};

#endif