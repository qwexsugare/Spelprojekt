#pragma once

#include "stdafx.h"
#include "Mesh.h"
#include "TextureHolder.h"
#include "AnimationHolder.h"
#include "Animation.h"
#include "VertexStructs.h"
#include "FishStructs.h"
#include <fstream>
#include <DirectXCollision.h>
#include <DirectXMath.h>
#include <iostream>
#include <map>

using namespace DirectX;

class MeshImporter
{
private:
	static Material ReadMaterial( TextureHolder* textureHolder);
	static void ReadGeometry(Mesh* mesh, int meshId, ID3D10Device* device);
	static fstream m_fStream;
	static void MapFishFile(FishFile* fishFile, char* memblock);
	static void ReadFish(FishFile* fishFile, TextureHolder* textureHolder, string filename, string folderPath);
	static void ReadFishAnimation(AnimationFile* animationFile, string filepath, int numSkeletons);
	static void MapAnimationFile(AnimationFile* animationFile, char* memblock, int numSkeletons);
	static Mesh* CreateMesh(ID3D10Device *_device, FishFile* fishFile, bool isAnimated, TextureHolder* textureHolder, string folderPath);
public:
	static Mesh* loadOBJMesh(ID3D10Device *_device, TextureHolder *textureHolder, string _filename);
	static Mesh* LoadFishes(ID3D10Device* device, TextureHolder* textureHolder, AnimationHolder* animationHolder, string filename);
	static ID3D10ShaderResourceView* getTexture(string _filename);
};