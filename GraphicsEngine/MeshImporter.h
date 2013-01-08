//*****************
//	- 16-12-12 - Anders och Alve -
//	- Added LoadFishMesh()
//	- Added ReadMaterials()
//*****************
#pragma once

#include "stdafx.h"
#include "Mesh.h"
#include "TextureHolder.h"
#include "VertexStructs.h"
#include <fstream>
#include <iostream>

class MeshImporter
{
private:
	static Material ReadMaterial( TextureHolder* textureHolder);
	static void ReadGeometry(Mesh* mesh, int meshId, ID3D10Device* device);
	static fstream m_fStream;
public:
	static Mesh* loadOBJMesh(ID3D10Device *_device, TextureHolder *textureHolder, string _filename);
	static Mesh* LoadFishMesh(ID3D10Device* device, TextureHolder* textureHolder, string filename);
	static ID3D10ShaderResourceView* getTexture(string _filename);
};