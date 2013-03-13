#pragma once

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
	float m_originalRange;
	bool m_active;
	unsigned int m_ownerId;
	int m_turretUpgrade;
public:
	Turret(FLOAT3 _position, float _attackCooldown, float _range, float _lifetime, unsigned int _ownerId, int _turretUpgrade);
	virtual ~Turret();
	
	const BoundingSphere& getRange()const;
	int getTurretUpgrade()const;
	virtual void target(ServerEntity* _target) = 0;
	void update(float _dt);
	virtual void updateSpecificTurret(float _dt);

	void addLifetime(float _dt);
	void setReadyAimFire(float _readyAimFire);
	void setActive(bool _active);
	unsigned int getOwnerId();

	virtual int getCost() = 0;
};