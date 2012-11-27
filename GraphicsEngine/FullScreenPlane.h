#ifndef FULL_SCREEN_PLANE_H
#define FULL_SCREEN_PLANE_H

#include "stdafx.h"
#include "Mesh.h"
#include "VertexStructs.h"

class FullScreenPlane
{
private:
	Mesh *m_mesh;
	ID3D10Texture2D *m_texture;
public:
	FullScreenPlane(ID3D10Device *device, ID3D10Texture2D *_texture);
	~FullScreenPlane();

	Mesh *getMesh();
	ID3D10Texture2D *getTexture();
};

#endif