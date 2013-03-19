#pragma once

#include "stdafx.h"

enum SpawnShape{ Circle };

struct Behavior
{
	float spawnRate;
	float lifeTime;
	SpawnShape ss;
	unsigned int minEmit;
	unsigned int maxEmit;
	bool staticFollow;
	bool yRotate;
	bool xRotate;
	bool zRotate;
	bool fadeIn;
	bool fadeOut;
	bool isLit;
};

struct CirclePuls : Behavior
{
	
};

struct ParticleEffect
{
	int startBehavior;
	int behavior;
	int endBehavior;

	float startBehaviorTime;
	float behaviorTime;
	float endBehaviorTime;

	float scale;
	float emitRate;
	float lifeTime;
	float speed;
	float offset;

	vector<string> textures;
};