#pragma once

#include "ServerEntity.h"
#include "EntityHandler.h"
#include "Graphics.h"

class WallEffect : public ServerEntity
{
private:
	float m_duration;
public:
	WallEffect(unsigned int _senderId, FLOAT3 _position, float rotation, float _duration);
	~WallEffect();

	void update(float _dt);	
};

