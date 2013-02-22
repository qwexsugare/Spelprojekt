#pragma once

#include "ServerEntity.h"

class TeleportEffect : public ServerEntity
{
private:
	float m_currentDuration;
	unsigned int m_casterId;
public:
	static const int DURATION = 5;
	static const float BOOST;

	TeleportEffect(unsigned int _casterId);
	~TeleportEffect();

	void update(float _dt);
};