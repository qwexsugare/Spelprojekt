#pragma once
#include "Enemy.h"
#include "Path.h"
class BigBadBoss
	:public Enemy
{
public:
	BigBadBoss(FLOAT3 _pos, Path _path);
	~BigBadBoss(void);
};

