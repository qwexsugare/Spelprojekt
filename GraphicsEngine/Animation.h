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
	TexturePack texPack;
	float time;
	int currentKey;
	float nextKey;
	void UpdateSkeletonTexture(vector<D3DXMATRIX>* mat);
	string currentAnimation;
	string pendingAnimation;
	void RandomAnimationFunc(float dt);
	void FFloat3ToD3DXVECTOR3(D3DXVECTOR3 &out, FFloat3 &in);
	void FFloat4ToD3DXQUATERNION(D3DXQUATERNION &out, FFloat4 &in);
	D3DXMATRIX hatMatrix;
	D3DXMATRIX rightHandMatrix;
	D3DXMATRIX leftHandMatrix;
	void UpdateCurrAnimations();

public:
	Animation();
	~Animation();
	void addAnimation(string name, AnimationFile animationFile);
	int getNumAnimations();
	void Update(float dt);
	void setTexturePack(TexturePack* _texPack);
	ID3D10ShaderResourceView* getResource();

	D3DXMATRIX* getHatMatrix();
	D3DXMATRIX* getRightHandMatrix();
	D3DXMATRIX* getLeftHandMatrix();
	
	// number of loops: -1 = infinite
	void PlayLoop(string name, Motion body, int numberOfLoops, float overlapTime);
	void Stop(string name, Motion body);
	void Play(string name, Motion body);
	FishAnimationStuff ANewWierdFunction(AnimationFile* animationFile, int skeletonIndex, int jointIndex, float lerpValue);
};