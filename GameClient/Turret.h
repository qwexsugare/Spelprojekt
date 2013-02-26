#ifndef TOWER_H
#define TOWER_H

#include "ServerEntity.h"
#include "EntityHandler.h"
#include "Projectile.h"

class Turret : public ServerEntity
{
protected:
	float m_attackRange;
	float m_attackCooldown;
	float m_lifeTime;
public:
	Turret();
	Turret(FLOAT3 position);
	virtual ~Turret();
	void update(float dt);
};

#endif