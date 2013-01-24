#pragma once

#include "Entity.h"
#include "DataStructures.h"

class ClientSkill
{
protected:
	bool m_active;

public:
	ClientSkill();
	ClientSkill(const Entity& user, FLOAT3 pos);
	ClientSkill(const Entity& user, const Entity& target);
	ClientSkill(const Entity& user);
	~ClientSkill();

	void update(float dt);
	bool getActive();
};