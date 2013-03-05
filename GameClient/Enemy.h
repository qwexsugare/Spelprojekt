#ifndef ENEMY_H
#define ENEMY_H

#include "ServerEntity.h"
#include "EntityHandler.h"
#include "Path.h"
#include "Graphics.h"

class Enemy : public UnitEntity
{
private:
	float lastDT;
protected:
	FLOAT3 m_nextPosition;
	bool m_reachedPosition;
	float m_aggroRange; 
	bool m_willPursue;
	int m_closestTargetId;
	FLOAT3 m_dir;
	FLOAT3 m_prevDir;
	FLOAT3 m_goalPosition;
	FLOAT3 m_goalDirection;
	Path m_path;
	int m_currentPoint;
	float m_staticBuffer;
	float avoidTimer;
	float avoidTimerDos;
	float m_distanceToStatic;
	FLOAT3 m_staticAvDir;
	FLOAT3 m_enemyAvDir;
	int m_lowResource;
	UnitEntity::Type m_targetType;
	int m_highRescource;
	FLOAT3 m_rotationAdding;
	float m_closestHero;
	FLOAT3 hoxit;
	ServerEntity *m_prevClosestStatic;
	ServerEntity *m_currClosestStatic;

	FLOAT3 m_destination;
	float m_destinationRadius;
	float m_distanceToPoint; 
public:
	Enemy();
	Enemy(FLOAT3 _pos, Path _path);
	virtual ~Enemy();
	void updateSpecificUnitEntity(float dt);
	//void setNextPosition(FLOAT3 _nextPosition);
	void setNextPosition(unsigned int _id, float dt);

	FLOAT3 getDirection();
	void checkPursue();
	FLOAT3 checkStatic(float dt);
	void checkCloseEnemies(float dt);
	bool checkDistanceToStatic(float firstFactor, float secondFactor);
	void attackHero();

	FLOAT3 crossProduct(FLOAT3 _first, FLOAT3 _second);
	bool outOfBounds(FLOAT3 _pt, int _offset);
	bool completelyOutOfBounds(FLOAT3 _pt);
	void setTargetType(UnitEntity::Type _type);
	void updateEnemyAvDir(FLOAT3 _val);
	FLOAT3 getEndPos();
};

#endif
