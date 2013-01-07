#ifndef HERO_H
#define HERO_H

#include "Datastructures.h"
#include "ServerEntity.h"

class Hero : public ServerEntity
{
private:
	FLOAT3 m_nextPosition;
	bool m_reachedPosition;
	float m_movementSpeed;

	unsigned int m_hp;
public:
	Hero();

	void update(float dt);
	void setNextPosition(FLOAT3 _nextPosition);
};

#endif