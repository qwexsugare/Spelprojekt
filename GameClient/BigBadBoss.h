#pragma once
#include "Enemy.h"
#include "Path.h"
#include "MeleeAttack.h"
class BigBadBoss
	:public Enemy
{
public:

	
	BigBadBoss(FLOAT3 _pos);
	~BigBadBoss(void);
	FLOAT3 m_origPos; 
	bool m_isHeadingBack;
	float m_allowedMovement;
	virtual void attackHero(int heroIndex);
	void updateSpecificUnitEntity(float dt);
	void tellBossToDropGold();
	
};

