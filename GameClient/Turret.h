#ifndef TOWER_H
#define TOWER_H

#include "ServerEntity.h"

class Turret : public ServerEntity
{
private:
	float m_currentAttackCooldown;
	BoundingSphere m_range;
protected:
	float m_attackRangeProt;
	float m_attackCooldown;
	float m_lifeTime;
public:
	Turret();
	Turret(FLOAT3 position);
	Turret(FLOAT3 _position, float _attackCooldown, float _range, float _lifetime);
	virtual ~Turret();

	virtual void target(ServerEntity* _target) = 0;
	void update(float _dt);
};

#endif