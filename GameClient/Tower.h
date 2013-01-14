#ifndef TOWER_H
#define TOWER_H

#include "ServerEntity.h"
#include "EntityHandler.h"
#include "Projectile.h"

class Tower : public ServerEntity
{
private:
	float m_attackRange;
	float m_attackCooldown;
public:
	Tower();
	virtual ~Tower();
	void update(float dt);
};

#endif