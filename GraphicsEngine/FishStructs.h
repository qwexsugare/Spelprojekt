#pragma once

#include <string>
#include <vector>

#define _upperBody_ 1;
#define _lowerBody_ 0;
#define _rightHand_ 2;
#define _leftHand_ 3;
#define _hat_ 4;

using namespace std;

struct FFloat3
{
	float x;
	float y;
	float z;
};

struct FFloat4
{
	float x;
	float y;
	float z;
	float w;
};

struct FJoint
{
	FFloat4 rotation;
	FFloat3 translation;
	FFloat3 scale;
};

struct FBoundingVolume
{
	FFloat3 pos;
	FFloat3 size;
	int type;
};

struct FFloat2
{
	float u;
	float v;
};

struct FFileInfo
{
	int numSkeleton;
	int numMaterials;
	int numGeometry;
};

struct FVertex
{
	FFloat3 position;
	FFloat3 normal;
	FFloat3 tangent;
	FFloat2 uv;
	vector<float> weights;
	vector<int> boneIndex;
};

struct FMesh
{
	int skeletonId;
	int numInfluences;
	int numVertices;
	int materialIndex;
	vector<FVertex> vertices;
};

struct FTexture
{
	int pathSize;
	int typeSize;
	char path[50];
	char type[30];
};

struct FMaterial
{
	int numTextures;
	vector<FTexture> textures;
};

struct FKeys
{
	float time;
	int numJoints;
	vector<FJoint> joints;
};

struct FSkeleton
{
	vector<FKeys> keys;
	vector<int> jointTypes;
};


struct FishFile
{
	FFileInfo fFileInfo;
	FBoundingVolume boundingVol;
	vector<FMesh> FMeshes;
	vector<FMaterial> fMaterials;
};

struct FPropsLocators
{
	float hatPos[3];
	float rightHandPos[3];
	float leftHandPos[3];
	FPropsLocators()
	{
		this->hatPos[0] = 0;
		this->hatPos[1] = 0;
		this->hatPos[2] = 0;
		this->rightHandPos[0] = 0;
		this->rightHandPos[1] = 0;
		this->rightHandPos[2] = 0;
		this->leftHandPos[0] = 0;
		this->leftHandPos[1] = 0;
		this->leftHandPos[2] = 0;
	}
	~FPropsLocators()
	{

	}
};

struct AnimationFile
{
	FPropsLocators propsLocators;
	string name;
	int numKeys;
	vector<FSkeleton> skeletons;
};