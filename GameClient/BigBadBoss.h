#pragma once
#include "Enemy.h"
#include "Path.h"
#include "MeleeAttack.h"
class BigBadBoss
	:public Enemy
{
public:

	FLOAT3 m_origPos; 
	float m_allowedMovement;
	BigBadBoss(FLOAT3 _pos);
	~BigBadBoss(void);
	virtual void attackHero(int heroIndex);
	void updateSpecificUnitEntity(float dt);
	void tellBossToDropGold();
	
};

