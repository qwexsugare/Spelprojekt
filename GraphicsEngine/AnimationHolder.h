#pragma once

#include "Animation.h"
#include <map>

using namespace std;

class AnimationHolder
{
private:
	map<string, Animation> animations;
public:
	AnimationHolder();
	~AnimationHolder();
	Animation getAnimation(string name);
	void addAnimation(string name, Animation _animations);
};