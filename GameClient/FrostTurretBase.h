#pragma once

#include "ServerEntity.h"

class FrostTurretBase : public ServerEntity
{
private:
	float m_lifeTime;
public:
	FrostTurretBase(FLOAT3 _pos, float _lifetime);
	~FrostTurretBase();

	void update(float _dt);
};

