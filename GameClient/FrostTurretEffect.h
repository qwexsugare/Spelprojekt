#pragma once

#include "serverentity.h"

class FrostTurretEffect : public ServerEntity
{
private:
	static vector<unsigned int> m_targetIds;
	unsigned int m_target;
public:
	FrostTurretEffect(unsigned int _targetId);
	~FrostTurretEffect();

	void update(float _dt);
};

