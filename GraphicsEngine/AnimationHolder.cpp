#include "AnimationHolder.h"

AnimationHolder::AnimationHolder()
{

}

AnimationHolder::~AnimationHolder()
{

}

Animation AnimationHolder::getAnimation(string name)
{
	return this->animations[name];
}

void AnimationHolder::addAnimation(string name, Animation _animations)
{

	this->animations.insert(animations.begin(), pair<string, Animation>(name, _animations));
}