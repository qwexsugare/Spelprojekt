#ifndef HERO_H
#define HERO_H

#include "Datastructures.h"
#include "UnitEntity.h"
#include "ServerEntity.h"
#include "EntityHandler.h"
#include "Projectile.h"
#include "MapHandler.h"
#include "Path.h"

class Hero : public UnitEntity
{
private:
	FLOAT3 m_nextPosition;
	FLOAT3 m_goalPosition;
	bool m_reachedPosition;
	bool m_reallyReachedPosition;

	unsigned int m_target;
	bool m_hasTarget;

	Path m_path;
	int m_pathCounter;
public:
	Hero();
	virtual ~Hero();
	
	void updateSpecificUnitEntity(float dt);
	void setNextPosition(FLOAT3 _nextPosition);
	void setTarget(unsigned int _target);
	FLOAT3 getDirection();
};

#endif