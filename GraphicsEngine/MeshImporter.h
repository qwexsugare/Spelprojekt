#pragma once

#include "stdafx.h"
#include "Mesh.h"
#include "TextureHolder.h"
#include "VertexStructs.h"
#include <fstream>

class MeshImporter
{
public:
	static Mesh* loadOBJMesh(ID3D10Device *_device, TextureHolder *textureHolder, string _filename);
	static ID3D10ShaderResourceView* getTexture(string _filename);
};

