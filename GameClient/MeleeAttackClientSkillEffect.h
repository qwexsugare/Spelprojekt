#pragma once

#include "clientskilleffect.h"
#include "ClientEntityHandler.h"
#include "PlayerInfo.h"

class MeleeAttackClientSkillEffect : public ClientSkillEffect
{
private:
	int m_lifetime;
public:
	MeleeAttackClientSkillEffect(unsigned int masterId, unsigned int _targetId, PLAYER_INFO _playerInfo);
	~MeleeAttackClientSkillEffect();

	void update(float dt);
	bool getActive();
};