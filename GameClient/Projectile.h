#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "ServerEntity.h"
#include "UnitEntity.h"
#include "DataStructures.h"
#include "EntityHandler.h"

class Projectile : public UnitEntity
{
private:
	FLOAT3 m_direction;
	float m_movementSpeed;
	float m_lifetime;

	UnitEntity *m_creator;
public:
	Projectile(FLOAT3 _position, FLOAT3 _direction, float _lifetime, float _movementSpeed, UnitEntity *_creator);
	virtual ~Projectile();

	void updateSpecificUnitEntity(float dt);
};

#endif