#pragma once
#include "Enemy.h"
#include "Path.h"

class FrostDemon : public Enemy
{
public:
	FrostDemon(FLOAT3 _pos, Path _path);
	~FrostDemon(void);


	void attackHero(int heroIndex);
};

