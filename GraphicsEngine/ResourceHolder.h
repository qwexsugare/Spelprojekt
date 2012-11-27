#pragma once

#include "stdafx.h"
#include <map>
#include "Mesh.h"
#include "MeshImporter.h"
#include "TextureHolder.h"

class ResourceHolder
{
private:
	map<string, Mesh*> m_meshes;
	ID3D10Device* m_device;
	TextureHolder* m_textureHolder;
public:
	ResourceHolder();
	ResourceHolder(ID3D10Device* _device);
	~ResourceHolder();

	Mesh* getMesh(string filename);
	TextureHolder *getTextureHolder();
};