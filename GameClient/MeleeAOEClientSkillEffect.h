#pragma once
#include "clientskilleffect.h"
#include "ClientEntityHandler.h"
#include "PlayerInfo.h"
class MeleeAOEClientSkillEffect : public ClientSkillEffect
{
private:
	int m_lifetime;
	static const int TIME_BETWEEN_DAMAGE_SOUNDS = 5;
	static float timeToNextDamageSound;
public:
	MeleeAOEClientSkillEffect(unsigned int masterId, unsigned int _targetId, PLAYER_INFO _playerInfo);
	~MeleeAOEClientSkillEffect();
	
	static void decreaseTimeBetweenDamageSounds(float _dt);
	void update(float dt);
	bool getActive();
};