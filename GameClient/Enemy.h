#ifndef ENEMY_H
#define ENEMY_H

#include "ServerEntity.h"
#include "EntityHandler.h"
#include "Hero.h"
#include "MeleeAttack.h"
#include "Path.h"

class Enemy : public UnitEntity
{
private:
	FLOAT3 m_nextPosition;
	bool m_reachedPosition;
	float m_movementSpeed;
	float m_aggroRange; 
	bool m_willPursue;
	int m_closestHero;
	float m_attackCooldown;
	FLOAT3 m_dir;
	FLOAT3 m_goalPosition;
	Path m_path;
	int m_currentPoint;

	ServerEntity *m_closestStatic;
public:
	Enemy();
	Enemy(FLOAT3 _pos, Path _path);

	void updateSpecificUnitEntity(float dt);
	void setNextPosition(FLOAT3 _nextPosition);
	void setNextPosition(int index, float dt);

	void checkPursue();
	FLOAT3 checkStatic(float dt, FLOAT3 _pPos);

	FLOAT3 crossProduct(FLOAT3 _first, FLOAT3 _second);

};

#endif
