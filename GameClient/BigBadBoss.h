#pragma once
#include "Enemy.h"
#include "Path.h"
class BigBadBoss
	:public Enemy
{
public:
	BigBadBoss(FLOAT3 _pos);
	~BigBadBoss(void);
	virtual void attackHero(int heroIndex);
	void update(float dt);
};

