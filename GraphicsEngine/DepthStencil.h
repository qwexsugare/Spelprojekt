#ifndef DEPTH_STENCIL_H
#define DEPTH_STENCIL_H

#include "stdafx.h"
#include "DataStructures.h"

class DepthStencil
{
private:
	INT2 m_size;
	ID3D10DepthStencilView* m_depthStencilView;
	ID3D10Texture2D* m_texture;
	ID3D10ShaderResourceView* m_shaderResource;

	void createDepthStencil(ID3D10Device *device);
	void createShadowMap(ID3D10Device *device);
public:
	DepthStencil(ID3D10Device *device, INT2 _size, bool stencil);
	~DepthStencil();
	ID3D10DepthStencilView *getDepthStencilView();
	ID3D10Texture2D *getTexture();
	ID3D10ShaderResourceView *getShaderResource();
	void clear(ID3D10Device* _device);
	const INT2& getSize()const { return m_size; }
};

#endif