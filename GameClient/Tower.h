#ifndef TOWER_H
#define TOWER_H

#include "ServerEntity.h"
#include "EntityHandler.h"
#include "Projectile.h"

class Tower : public ServerEntity
{
protected:
	float m_attackRange;
	float m_attackCooldown;
	float m_lifeTime;
public:
	Tower();
	Tower(FLOAT3 position);
	virtual ~Tower();
	void update(float dt);
};

#endif