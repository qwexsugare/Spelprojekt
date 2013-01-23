#include "Animation.h"

Animation::Animation()
{
	this->currentKey = 0;
	this->texPack.texture = NULL;
	this->time = 0;
}

Animation::~Animation()
{
	int y = 0;
}

void Animation::addAnimation(string name, AnimationFile animationFile)
{
	this->names.push_back(name);
	this->animations.push_back(animationFile);
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
	if(getNumAnimations() > 0 && this->texPack.texture != NULL)
	{
		float fps = 24;
		vector<D3DXMATRIX> matrices;
		
		float offset = this->animations[0].skeletons[0].keys[0].time;
		int maxKeys = this->animations[0].skeletons[0].keys.size() - 1;

		float currKeyTime =  this->animations[0].skeletons[0].keys[currentKey].time;
		float nextKeyTime = this->animations[0].skeletons[0].keys[currentKey+1].time;

		if(time >= (this->animations[0].skeletons[0].keys[this->animations[0].skeletons[0].keys.size()-1].time-offset)/fps)
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
	
		currKeyTime = this->animations[0].skeletons[0].keys[currentKey].time;
		nextKeyTime = this->animations[0].skeletons[0].keys[currentKey + 1].time;

		float timeInterval = ((nextKeyTime-offset)/fps) - ((currKeyTime-offset)/fps);
		float timePass = time - (currKeyTime-offset)/fps;
		float lerpValue = timePass/timeInterval;

		/*currentKey = 1;
		lerpValue = 1;*/
		for(int i = 0; i < this->animations[0].skeletons[0].keys[currentKey].joints.size(); i++)
		{
			D3DXMATRIX outMat;
			D3DXVECTOR3 outScale, outTrans;
			D3DXQUATERNION outQuat;
			D3DXQUATERNION tempQuat1;
			tempQuat1.x = this->animations[0].skeletons[0].keys[currentKey].joints[i].rotation.x;
			tempQuat1.y = this->animations[0].skeletons[0].keys[currentKey].joints[i].rotation.y;
			tempQuat1.z = this->animations[0].skeletons[0].keys[currentKey].joints[i].rotation.z;
			tempQuat1.w = this->animations[0].skeletons[0].keys[currentKey].joints[i].rotation.w;
			D3DXQUATERNION tempQuat2;
			tempQuat2.x = this->animations[0].skeletons[0].keys[currentKey + 1].joints[i].rotation.x;
			tempQuat2.y = this->animations[0].skeletons[0].keys[currentKey + 1].joints[i].rotation.y;
			tempQuat2.z = this->animations[0].skeletons[0].keys[currentKey + 1].joints[i].rotation.z;
			tempQuat2.w = this->animations[0].skeletons[0].keys[currentKey + 1].joints[i].rotation.w;
			D3DXVECTOR3 tempTrans1;
			tempTrans1.x = this->animations[0].skeletons[0].keys[currentKey].joints[i].translation.x;
			tempTrans1.y = this->animations[0].skeletons[0].keys[currentKey].joints[i].translation.y;
			tempTrans1.z = this->animations[0].skeletons[0].keys[currentKey].joints[i].translation.z;
			D3DXVECTOR3 tempTrans2;
			tempTrans2.x = this->animations[0].skeletons[0].keys[currentKey + 1].joints[i].translation.x;
			tempTrans2.y = this->animations[0].skeletons[0].keys[currentKey + 1].joints[i].translation.y;
			tempTrans2.z = this->animations[0].skeletons[0].keys[currentKey + 1].joints[i].translation.z;
			D3DXVECTOR3 tempScale1;
			tempScale1.x = this->animations[0].skeletons[0].keys[currentKey].joints[i].scale.x;
			tempScale1.y = this->animations[0].skeletons[0].keys[currentKey].joints[i].scale.y;
			tempScale1.z = this->animations[0].skeletons[0].keys[currentKey].joints[i].scale.z;
			D3DXVECTOR3 tempScale2;
			tempScale2.x = this->animations[0].skeletons[0].keys[currentKey + 1].joints[i].scale.x;
			tempScale2.y = this->animations[0].skeletons[0].keys[currentKey + 1].joints[i].scale.y;
			tempScale2.z = this->animations[0].skeletons[0].keys[currentKey + 1].joints[i].scale.z;

			D3DXQuaternionSlerp(&outQuat, &tempQuat1, &tempQuat2, lerpValue);
			D3DXVec3Lerp(&outScale, &tempScale1, &tempScale2, lerpValue);
			D3DXVec3Lerp(&outTrans, &tempTrans1, &tempTrans2, lerpValue);
			D3DXMatrixTransformation(&outMat, NULL, NULL, &outScale, NULL, &outQuat, &outTrans);

			matrices.push_back(outMat);
			if(i == 67)
				int yolo = 0;
		}
		time += dt;
	UpdateSkeletonTexture(&matrices);
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