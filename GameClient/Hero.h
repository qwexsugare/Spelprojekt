#ifndef HERO_H
#define HERO_H

#include "Datastructures.h"
#include "UnitEntity.h"
#include "ServerEntity.h"
#include "EntityHandler.h"
#include "Pathfinder.h"
#include "Path.h"
#include "Skills.h"
#include "Statistics.h"

class Hero : public UnitEntity
{
public:
	static enum HERO_TYPE {OFFICER, RED_KNIGHT, ENGINEER, DOCTOR, THE_MENTALIST, NONE};
	static enum WEAPON_TYPE{NO_WEAPON, RANGED, MELEE, AOE};
protected:
	FLOAT3 m_nextPosition;
	FLOAT3 m_goalPosition;
	FLOAT3 m_startPos;
	bool m_reachedPosition;
	bool m_reallyReachedPosition;

	unsigned int m_target;
	bool m_hasTarget;

	Path m_path;
	int m_pathCounter;

	HERO_TYPE m_heroType;
	WEAPON_TYPE m_weaponType;
	int m_playerId;
	float m_attackRange;
	bool m_alive;
public:
	Hero();
	Hero(HERO_TYPE _heroType, int _playerId);
	virtual ~Hero();
	
	void activateAllPassiveSkills();
	void alterSpecificUnitEntityMentalResistance();
	void alterSpecificUnitEntityPhysicalResistance();
	HERO_TYPE getHeroType()const;
	void updateSpecificUnitEntity(float dt);
	void setNextPosition(FLOAT3 _nextPosition);
	void setTarget(unsigned int _target);
	FLOAT3 getDirection();
	FLOAT3 getEndPos();
	unsigned short getWeaponType();
	void respawn(FLOAT3 _position);
	UpdateEntityMessage* getUpdateEntityMessage();
	bool getAlive();
};

#endif