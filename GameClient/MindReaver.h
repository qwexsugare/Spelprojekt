#pragma once
#include "Enemy.h"
#include "Path.h"
#include "MeleeAttack.h"
class MindReaver
	:public Enemy
{
public:
	MindReaver(FLOAT3 _pos);
	~MindReaver(void);

	bool m_isHeadingBack;
	FLOAT3 m_origPos; 
	float m_allowedMovement;
	virtual void attackHero(int heroIndex);
	void updateSpecificUnitEntity(float dt);
	void tellBossToDropGold();
};

