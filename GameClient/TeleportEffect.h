#pragma once

#include "ServerEntity.h"
#include "Hero.h"

class TeleportEffect : public ServerEntity
{
private:
	float m_currentDuration;
	float m_castingDelay;
	unsigned int m_casterId;

	FLOAT3 m_newPosition;
public:
	static const float BOOST;

	TeleportEffect(unsigned int _casterId, FLOAT3 _newPosition);
	~TeleportEffect();

	void update(float _dt);
};