#include "Animation.h"

Animation::Animation()
{
	this->texPack = NULL;
	this->currentAnimation = "run";
	this->prioAnimation = "";
	D3DXMatrixIdentity(&this->hatMatrix);
	D3DXMatrixIdentity(&this->rightHandMatrix);
	D3DXMatrixIdentity(&this->leftHandMatrix);
	this->waitAtEnd = false;
	this->priority = 0;
}

Animation::~Animation()
{
	if(texPack)
		delete texPack;
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
	this->texPack = _texPack;
}

D3DXMATRIX* Animation::getHatMatrix()
{
	return &this->hatMatrix; 
}

D3DXMATRIX* Animation::getRightHandMatrix()
{
	return &this->rightHandMatrix; 
}

D3DXMATRIX* Animation::getLeftHandMatrix()
{
	return &this->leftHandMatrix; 
}

void Animation::Update(float dt)
{
	RandomAnimationFunc(dt);
	
	//vector<D3DXMATRIX> matrices;
	//for(int a = 0; a < currentAnimations.size(); a++)
	//{
	//	vector<vector<FishAnimationStuff>> fishAnimationStuff;
	//}

	//splitfactor

	//for currentAnimations
		//

		//splitfactor += currentAnimation[i].blend%
	//

}

void Animation::UpdateCurrAnimations()
{
	//DoSTUFF

	vector<vector<FishAnimationStuff>> annatStuff;
	
	map<string, AnimationFile*>::iterator it;
	//vector<FishAnimationStuff> blend;
	int c = 0;
	
	float lerping = 0;

	for(it = currentAnimations.begin(); it != currentAnimations.end(); it++, c++)
	{
		lerping += it->second->animationWeight;
		float fps = 24;
		vector<D3DXMATRIX> matrices;
		
		float offset = this->animations[currentAnimation].skeletons[0].keys[0].time;
		int maxKeys = this->animations[currentAnimation].skeletons[0].keys.size() - 1;

		float currKeyTime =  this->animations[currentAnimation].skeletons[0].keys[this->animations[currentAnimation].currentKey].time;
		float nextKeyTime = this->animations[currentAnimation].skeletons[0].keys[this->animations[currentAnimation].currentKey+1].time;

		if(this->animations[currentAnimation].time >= (this->animations[currentAnimation].skeletons[0].keys[this->animations[currentAnimation].skeletons[0].keys.size()-1].time-offset)/fps)
		{
			this->animations[currentAnimation].currentKey = 0;
			this->animations[currentAnimation].time = 0;
		}
		else
		{
			if(this->animations[currentAnimation].currentKey + 2 <= maxKeys)
			{
				if(this->animations[currentAnimation].time >= (nextKeyTime-offset)/fps)
				{
					this->animations[currentAnimation].currentKey++;
				}
			}
		}
		
		currKeyTime = this->animations[currentAnimation].skeletons[0].keys[this->animations[currentAnimation].currentKey].time;
		nextKeyTime = this->animations[currentAnimation].skeletons[0].keys[this->animations[currentAnimation].currentKey + 1].time;

		float timeInterval = ((nextKeyTime-offset)/fps) - ((currKeyTime-offset)/fps);
		float timePass = this->animations[currentAnimation].time - (currKeyTime-offset)/fps;
		float lerpValue = timePass/timeInterval;


		vector<FishAnimationStuff> stuff;

		for(int k = 0; k < currentAnimations[it->first]->skeletons[0].keys.size(); k++)
		{
			for(int j = 0; j < currentAnimations[it->first]->skeletons[0].keys[k].numJoints; j++)
			{					
				stuff.push_back(ANewWierdFunction(it->second, 0, j, lerpValue));
			}
		}

		/*for(int b = 0; b < blend.size(); b++)
		{

		}*/
		annatStuff.push_back(stuff);
	}

	for(int j = 0; j < animations[0].skeletons[0].keys[0].numJoints; j++)
	{
		vector<FishAnimationStuff> blending;
		for(int o = 0; o < annatStuff.size(); o++)
		{
			blending.push_back(annatStuff[o][j]);
		}
		FishAnimationStuff joint;
		for(int b = 0; b < blending.size(); b++)
		{

			//blending[b].rotation *= currentAnimations.
		}
	}
}

FishAnimationStuff Animation::ANewWierdFunction(AnimationFile* animationFile, int skeletonIndex, int jointIndex, float lerpValue)
{
	FishAnimationStuff f;

	D3DXQUATERNION tempQuat1;
	FFloat4ToD3DXQUATERNION(tempQuat1, animationFile->skeletons[skeletonIndex].keys[this->animations[currentAnimation].currentKey].joints[jointIndex].rotation);
	D3DXQUATERNION tempQuat2;
	FFloat4ToD3DXQUATERNION(tempQuat2, animationFile->skeletons[skeletonIndex].keys[this->animations[currentAnimation].currentKey + 1].joints[jointIndex].rotation);
	D3DXVECTOR3 tempTrans1;
	FFloat3ToD3DXVECTOR3(tempTrans1, animationFile->skeletons[skeletonIndex].keys[this->animations[currentAnimation].currentKey].joints[jointIndex].translation);
	D3DXVECTOR3 tempTrans2;
	FFloat3ToD3DXVECTOR3(tempTrans2, animationFile->skeletons[skeletonIndex].keys[this->animations[currentAnimation].currentKey + 1].joints[jointIndex].translation);
	D3DXVECTOR3 tempScale1;
	FFloat3ToD3DXVECTOR3(tempScale1, animationFile->skeletons[skeletonIndex].keys[this->animations[currentAnimation].currentKey].joints[jointIndex].scale);
	D3DXVECTOR3 tempScale2;
	FFloat3ToD3DXVECTOR3(tempScale2, animationFile->skeletons[skeletonIndex].keys[this->animations[currentAnimation].currentKey + 1].joints[jointIndex].scale);


	D3DXQuaternionSlerp(&f.rotation, &tempQuat1, &tempQuat2, lerpValue);
	D3DXVec3Lerp(&f.scale, &tempScale1, &tempScale2, lerpValue);
	D3DXVec3Lerp(&f.translation, &tempTrans1, &tempTrans2, lerpValue);

	return f;
}

void Animation::RandomAnimationFunc(float dt)
{
	string theAni = currentAnimation;
	if(prioAnimation != "")
		theAni = prioAnimation;
	if(getNumAnimations() > 0 && this->texPack->texture != NULL)
	{
		map<string, AnimationFile>::iterator itr = animations.begin();
		for(; itr != animations.end(); itr++)
		{
			if(itr->second.isAnimating)
			{
				if(theAni == itr->first)
				{
					this->matrices.clear();

					float fps = 24;
					float offset = itr->second.skeletons[0].keys[0].time;
					int maxKeys = itr->second.skeletons[0].keys.size() - 1;

					float currKeyTime =  itr->second.skeletons[0].keys[itr->second.currentKey].time;
					float nextKeyTime = itr->second.skeletons[0].keys[itr->second.currentKey + 1].time;

					if(itr->second.time >= (itr->second.skeletons[0].keys[itr->second.skeletons[0].keys.size()-1].time-offset)/fps)
					{
						if(waitAtEnd == false)
						{
							itr->second.currentKey = 0;
							itr->second.time = 0.0f;
							itr->second.numLoops--;
							if(itr->second.numLoops == 0)
							{
								itr->second.isAnimating = false;
								this->prioAnimation = "";
								this->priority = 0;
							}
						}
						else
						{
							itr->second.time  = (itr->second.skeletons[0].keys[itr->second.skeletons[0].keys.size()-1].time-offset)/fps;
						}
					}
					else
					{
						if(itr->second.currentKey + 2 <= maxKeys)
						{
							if(itr->second.time >= (nextKeyTime-offset)/fps)
							{
								itr->second.currentKey++;
							}
						}
					}
					currKeyTime = itr->second.skeletons[0].keys[itr->second.currentKey].time;
					nextKeyTime = itr->second.skeletons[0].keys[itr->second.currentKey + 1].time;

					float timeInterval = ((nextKeyTime-offset)/fps) - ((currKeyTime-offset)/fps);
					float timePass = itr->second.time - (currKeyTime-offset)/fps;

					if(timePass > itr->second.skeletons[0].keys[itr->second.skeletons[0].keys.size()-1].time)
					{
						timePass = itr->second.skeletons[0].keys[itr->second.skeletons[0].keys.size()-1].time;
					}

					float lerpValue = timePass/timeInterval;

					for(int i = 0; i < itr->second.skeletons[0].keys[itr->second.currentKey].joints.size(); i++)
					{
						D3DXMATRIX outMat;
						D3DXVECTOR3 outScale, outTrans;
						D3DXQUATERNION outQuat;
						D3DXQUATERNION tempQuat1;
						FFloat4ToD3DXQUATERNION(tempQuat1, itr->second.skeletons[0].keys[itr->second.currentKey].joints[i].rotation);
						D3DXQUATERNION tempQuat2;
						FFloat4ToD3DXQUATERNION(tempQuat2, itr->second.skeletons[0].keys[itr->second.currentKey + 1].joints[i].rotation);
						D3DXVECTOR3 tempTrans1;
						FFloat3ToD3DXVECTOR3(tempTrans1, itr->second.skeletons[0].keys[itr->second.currentKey].joints[i].translation);
						D3DXVECTOR3 tempTrans2;
						FFloat3ToD3DXVECTOR3(tempTrans2, itr->second.skeletons[0].keys[itr->second.currentKey + 1].joints[i].translation);
						D3DXVECTOR3 tempScale1;
						FFloat3ToD3DXVECTOR3(tempScale1, itr->second.skeletons[0].keys[itr->second.currentKey].joints[i].scale);
						D3DXVECTOR3 tempScale2;
						FFloat3ToD3DXVECTOR3(tempScale2, itr->second.skeletons[0].keys[itr->second.currentKey + 1].joints[i].scale);

						D3DXQuaternionSlerp(&outQuat, &tempQuat1, &tempQuat2, lerpValue);
						D3DXVec3Lerp(&outScale, &tempScale1, &tempScale2, lerpValue);
						D3DXVec3Lerp(&outTrans, &tempTrans1, &tempTrans2, lerpValue);
						D3DXMatrixTransformation(&outMat, NULL, NULL, &outScale, NULL, &outQuat, &outTrans);

						D3DXMATRIX locatorMatrix;
						D3DXVECTOR3 locateScale(1, 1, 1);
						D3DXQUATERNION locateRotate(0, 0, 0, 1);
						D3DXVECTOR3 locateTrans;
				
						if(i == itr->second.propsLocators.hatIndex)
						{
							locateTrans = D3DXVECTOR3(
								itr->second.propsLocators.hatPos[0], 
								itr->second.propsLocators.hatPos[1], 
								-itr->second.propsLocators.hatPos[2]+0.0038f);

							D3DXMatrixTransformation(&locatorMatrix, NULL, NULL, &locateScale, NULL, &locateRotate, &locateTrans);
							this->hatMatrix = locatorMatrix * outMat;
						}
						else if(i == itr->second.propsLocators.rightHandIndex)
						{
							locateTrans = D3DXVECTOR3(
								itr->second.propsLocators.rightHandPos[0], 
								itr->second.propsLocators.rightHandPos[1], 
								-itr->second.propsLocators.rightHandPos[2]);
							D3DXMatrixTransformation(&locatorMatrix, NULL, NULL, &locateScale, NULL, &locateRotate, &locateTrans);
								this->rightHandMatrix = locatorMatrix * outMat;
						}
						else if(i == itr->second.propsLocators.leftHandIndex)
						{
							locateTrans = D3DXVECTOR3(
								itr->second.propsLocators.leftHandPos[0], 
								itr->second.propsLocators.leftHandPos[1], 
								-itr->second.propsLocators.leftHandPos[2]);
							D3DXMATRIX outMatNoRot;
							D3DXMatrixTransformation(&outMatNoRot, NULL, NULL, &outScale, NULL, &locateRotate, &outTrans);
							D3DXMatrixTransformation(&locatorMatrix, NULL, NULL, &locateScale, NULL, &locateRotate, &locateTrans);
							this->leftHandMatrix = locatorMatrix * outMat;
						}
						//D3DXMATRIX scale;
						//D3DXMatrixScaling(&scale, 1.0f, 1.0f, 1.0f);
						//outMat = outMat * scale;
						matrices.push_back(outMat);
					}
					itr->second.time += dt * itr->second.speedMultiplier;
				}
			}
		}
	}
}

ID3D10ShaderResourceView* Animation::getResource()
{
	return this->texPack->resourceView;
}

void Animation::UpdateSkeletonTexture()
{	
	if(getNumAnimations() > 0 && this->texPack->texture != NULL)
	{
		D3DXMATRIX* mats;
	
		if(SUCCEEDED(this->texPack->texture->Map(0, D3D10_MAP_WRITE_DISCARD, 0, (void**)&mats)))
		{
			for(UINT m = 0; m < matrices.size(); m++)
			{
				mats[m] = matrices.at(m);
			}
		}
		this->texPack->texture->Unmap(0);
	}
}

void Animation::Play(string name, bool waitAtEnd, int priority, float speedMultiplier, Motion body)
{
	if(priority >= this->priority)
	{
		this->animations[name].numLoops = 1;
		this->animations[name].isAnimating = true;
		this->animations[name].speedMultiplier = speedMultiplier;
		this->prioAnimation = name;
		this->waitAtEnd = waitAtEnd;
		this->priority = priority;
	}
}

void Animation::PlayLoop(string name, int numberOfLoops, float speedMultiplier, Motion body, float overlapTime)
{
	this->animations[name].numLoops = numberOfLoops;
	this->animations[name].isAnimating = true;
	this->animations[name].overlapTime = overlapTime;
	this->animations[name].speedMultiplier = speedMultiplier;
	this->currentAnimation = name;
	this->waitAtEnd = false;
}

void Animation::Stop(string name, Motion body)
{
	this->animations[name].isAnimating = false;
}

void Animation::Stop()
{
	map<string, AnimationFile>::iterator it = this->animations.begin();

	while(it != this->animations.end())
	{
		it->second.isAnimating = false;
		it++;
	}
}

string Animation::getPrioAnimation()
{
	return this->prioAnimation;
}

string Animation::getCurrentAnimation()
{
	return this->currentAnimation;
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