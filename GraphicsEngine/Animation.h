#pragma once

#include <vector>
#include "FishStructs.h"
#include "TexturePack.h"
#include "stdafx.h"
#include <map>

enum Motion{UpperBody, LowerBody, FullBody};

#define _INF_Fisk_ -1

using namespace std;


class Animation
{
private:
	map<string, AnimationFile> animations;
	map<string, AnimationFile*> currentAnimations;
	map<string, AnimationFile*> currentAnimationsAdd;
	vector<D3DXMATRIX> matrices;
	TexturePack* texPack;
	string currentAnimation;
	string prioAnimation;
	void RandomAnimationFunc(float dt);
	void FFloat3ToD3DXVECTOR3(D3DXVECTOR3 &out, FFloat3 &in);
	void FFloat4ToD3DXQUATERNION(D3DXQUATERNION &out, FFloat4 &in);
	D3DXMATRIX hatMatrix;
	D3DXMATRIX rightHandMatrix;
	D3DXMATRIX leftHandMatrix;
	bool waitAtEnd;
	int priority;
	void UpdateCurrAnimations();

public:
	Animation();
	~Animation();
	void addAnimation(string name, AnimationFile animationFile);
	int getNumAnimations();
	void Update(float dt);
	void setTexturePack(TexturePack* _texPack);
	ID3D10ShaderResourceView* getResource();
	void UpdateSkeletonTexture();

	D3DXMATRIX* getHatMatrix();
	D3DXMATRIX* getRightHandMatrix();
	D3DXMATRIX* getLeftHandMatrix();
	
	DECLDIR void PlayLoop(string name, int numberOfLoops = _INF_Fisk_, float speedMultiplier = 1.0f, Motion body = Motion::FullBody, float overlapTime = 0.5f);
	DECLDIR void Stop(string name, Motion body = Motion::FullBody);
	DECLDIR void Stop();
	DECLDIR void Play(string name, bool waitAtEnd = false, int priority = 0, float speedMultiplier = 1.0f, Motion body = Motion::FullBody);
	DECLDIR string getPrioAnimation();
	DECLDIR string getCurrentAnimation();
	FishAnimationStuff ANewWierdFunction(AnimationFile* animationFile, int skeletonIndex, int jointIndex, float lerpValue);
};