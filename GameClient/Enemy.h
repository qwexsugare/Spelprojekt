#ifndef ENEMY_H
#define ENEMY_H

#include "ServerEntity.h"
#include "EntityHandler.h"
#include "Hero.h"

class Enemy : public ServerEntity
{
private:
	FLOAT3 m_nextPosition;
	bool m_reachedPosition;
	float m_movementSpeed;

	unsigned int m_hp;
public:
	Enemy();

	void update(float dt);
	void setNextPosition(FLOAT3 _nextPosition);
	void setNextPosition(FLOAT3 _nextPosition, float dt);

};

#endif


