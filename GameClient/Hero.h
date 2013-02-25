#ifndef HERO_H
#define HERO_H

#include "Datastructures.h"
#include "UnitEntity.h"
#include "ServerEntity.h"
#include "EntityHandler.h"
#include "Projectile.h"
#include "MapHandler.h"
#include "Path.h"
#include "Skills.h"

class Hero : public UnitEntity
{
public:
	static enum HERO_TYPE {OFFICER, RED_KNIGHT, ENGINEER, DOCTOR, THE_MENTALIST, NONE};
	static enum WEAPON_TYPE{DEFAULT, RANGED, MELEE};
private:
	FLOAT3 m_nextPosition;
	FLOAT3 m_goalPosition;
	bool m_reachedPosition;
	bool m_reallyReachedPosition;

	unsigned int m_target;
	bool m_hasTarget;

	Path m_path;
	int m_pathCounter;

	HERO_TYPE m_heroType;
	int m_playerId;
public:
	Hero();
	Hero(HERO_TYPE _heroType, int _playerId);
	virtual ~Hero();
	
	void activateAllPassiveSkills();
	HERO_TYPE getHeroType()const;
	void updateSpecificUnitEntity(float dt);
	void setNextPosition(FLOAT3 _nextPosition);
	void setTarget(unsigned int _target);
	FLOAT3 getDirection();
};

#endif