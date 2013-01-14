#ifndef MELEE_ATTACK_H
#define MELEE_ATTACK_H

#include "ServerEntity.h"
#include "DataStructures.h"
#include "EntityHandler.h"

class MeleeAttack : public ServerEntity
{
private:
	float m_damage;
	float m_range;
	unsigned int m_targetId;
public:
	MeleeAttack(FLOAT3 _position, float _damage, unsigned int _targetId);
	virtual ~MeleeAttack();

	void update(float dt);
};

#endif