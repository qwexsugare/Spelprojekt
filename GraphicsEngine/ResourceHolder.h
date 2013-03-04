#pragma once

#include "stdafx.h"
#include <map>
#include "Mesh.h"
#include "MeshImporter.h"
#include "TextureHolder.h"
#include "AnimationHolder.h"

class ResourceHolder
{
private:
	map<string, Mesh*> m_meshes;
	ID3D10Device* m_device;
	TextureHolder* m_textureHolder;
	AnimationHolder* m_animationHolder;
public:
	ResourceHolder();
	ResourceHolder(ID3D10Device* _device);
	~ResourceHolder();

	Mesh* getMesh(string filename);
	TextureHolder *getTextureHolder();
	AnimationHolder *getAnimationHolder();
	Animation getAnimation(string name);
	string getFilename(Mesh *_mesh);
};