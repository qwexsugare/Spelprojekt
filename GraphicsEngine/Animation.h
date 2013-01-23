#pragma once

#include <vector>
#include "FishStructs.h"
#include "TexturePack.h"
#include "stdafx.h"

using namespace std;

//struct AnimationT

class Animation
{
private:
	vector<string> names;
	vector<AnimationFile> animations;
	TexturePack texPack;
	float time;
	int currentKey;
	float nextKey;
	void UpdateSkeletonTexture(vector<D3DXMATRIX>* mat);
public:
	Animation();
	~Animation();
	void addAnimation(string name, AnimationFile animationFile);
	int getNumAnimations();
	void Update(float dt);
	void setTexturePack(TexturePack* _texPack);
	ID3D10ShaderResourceView* getResource();
};