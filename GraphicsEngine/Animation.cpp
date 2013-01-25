#include "Animation.h"

Animation::Animation()
{
	this->currentKey = 0;
	this->texPack.texture = NULL;
	this->time = 0;
	currentAnimation = "walk";
	pendingAnimation = "";
}

Animation::~Animation()
{

}

void Animation::addAnimation(string name, AnimationFile animationFile)
{
	this->animations.insert(animations.begin(), pair<string, AnimationFile>(name, animationFile));
}

int Animation::getNumAnimations()
{
	return this->animations.size();
}

void Animation::setTexturePack(TexturePack* _texPack)
{
	this->texPack = *_texPack;
}

void Animation::Update(float dt)
{
	RandomAnimationFunc(dt);
}

void Animation::RandomAnimationFunc(float dt)
{
	if(getNumAnimations() > 0 && this->texPack.texture != NULL)
	{
		for(int s = 0; s < this->animations[currentAnimation].skeletons.size(); s++)
		{
			float fps = 24;
			vector<D3DXMATRIX> matrices;
		
			float offset = this->animations[currentAnimation].skeletons[s].keys[0].time;
			int maxKeys = this->animations[currentAnimation].skeletons[s].keys.size() - 1;

			float currKeyTime =  this->animations[currentAnimation].skeletons[s].keys[currentKey].time;
			float nextKeyTime = this->animations[currentAnimation].skeletons[s].keys[currentKey+1].time;

			if(time >= (this->animations[currentAnimation].skeletons[s].keys[this->animations[currentAnimation].skeletons[s].keys.size()-1].time-offset)/fps)
			{
				currentKey = 0;
				time = 0;
			}
			else
			{
				if(currentKey + 2 <= maxKeys)
				{
					if(time >= (nextKeyTime-offset)/fps)
					{
						currentKey++;
					}
				}
			}
		
			currKeyTime = this->animations[currentAnimation].skeletons[s].keys[currentKey].time;
			nextKeyTime = this->animations[currentAnimation].skeletons[s].keys[currentKey + 1].time;

			float timeInterval = ((nextKeyTime-offset)/fps) - ((currKeyTime-offset)/fps);
			float timePass = time - (currKeyTime-offset)/fps;
			float lerpValue = timePass/timeInterval;

			for(int i = 0; i < this->animations[currentAnimation].skeletons[s].keys[currentKey].joints.size(); i++)
			{
				D3DXMATRIX outMat;
				D3DXVECTOR3 outScale, outTrans;
				D3DXQUATERNION outQuat;
				D3DXQUATERNION tempQuat1;
				FFloat4ToD3DXQUATERNION(tempQuat1, this->animations[currentAnimation].skeletons[s].keys[currentKey].joints[i].rotation);
				D3DXQUATERNION tempQuat2;
				FFloat4ToD3DXQUATERNION(tempQuat2, this->animations[currentAnimation].skeletons[s].keys[currentKey + 1].joints[i].rotation);
				D3DXVECTOR3 tempTrans1;
				FFloat3ToD3DXVECTOR3(tempTrans1, this->animations[currentAnimation].skeletons[s].keys[currentKey].joints[i].translation);
				D3DXVECTOR3 tempTrans2;
				FFloat3ToD3DXVECTOR3(tempTrans2, this->animations[currentAnimation].skeletons[s].keys[currentKey + 1].joints[i].translation);
				D3DXVECTOR3 tempScale1;
				FFloat3ToD3DXVECTOR3(tempScale1, this->animations[currentAnimation].skeletons[s].keys[currentKey].joints[i].scale);
				D3DXVECTOR3 tempScale2;
				FFloat3ToD3DXVECTOR3(tempScale2, this->animations[currentAnimation].skeletons[s].keys[currentKey + 1].joints[i].scale);

				D3DXQuaternionSlerp(&outQuat, &tempQuat1, &tempQuat2, lerpValue);
				D3DXVec3Lerp(&outScale, &tempScale1, &tempScale2, lerpValue);
				D3DXVec3Lerp(&outTrans, &tempTrans1, &tempTrans2, lerpValue);
				D3DXMatrixTransformation(&outMat, NULL, NULL, &outScale, NULL, &outQuat, &outTrans);

				matrices.push_back(outMat);
			}
			UpdateSkeletonTexture(&matrices);
		}
		time += dt;
	}
}

ID3D10ShaderResourceView* Animation::getResource()
{
	return this->texPack.resourceView;
}

void Animation::UpdateSkeletonTexture(vector<D3DXMATRIX>* mat)
{	
	D3DXMATRIX* matrices;
	
	if(SUCCEEDED(this->texPack.texture->Map(0, D3D10_MAP_WRITE_DISCARD, 0, (void**)&matrices)))
	{
		for(UINT m = 0; m < mat->size(); m++)
		{
			matrices[m] = mat->at(m);
		}
	}
	this->texPack.texture->Unmap(0);
	this->texPack.texture;
	int ui = 0;
}

void Animation::FFloat3ToD3DXVECTOR3(D3DXVECTOR3 &out, FFloat3 &in)
{
	out.x = in.x;
	out.y = in.y;
	out.z = in.z;
}

void Animation::FFloat4ToD3DXQUATERNION(D3DXQUATERNION &out, FFloat4 &in)
{
	out.x = in.x;
	out.y = in.y;
	out.z = in.z;
	out.w = in.w;
}