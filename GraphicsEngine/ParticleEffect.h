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
	D3DXVECTOR4 color;
	float rotateSpeed;

	vector<string> textures;

	ParticleEffect()
	{
		this->startBehavior = 0;
		this->behavior = 0;
		this->endBehavior = 0;
		this->startBehaviorTime = 0;
		this->behaviorTime = 0;
		this->endBehaviorTime = 0;
		this->scale = 1;
		this->emitRate = 1;
		this->lifeTime = 1;
		this->speed = 1;
		this->offset = 0;
		this->color = D3DXVECTOR4(1, 1, 1, 1);
		this->rotateSpeed = 0;
	}
};