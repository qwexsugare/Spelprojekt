#ifndef RENDER_TARGET_H
#define RENDER_TARGET_H

#include "stdafx.h"
#include "DataStructures.h"

class RenderTarget
{
private:
	INT2 m_size;
	ID3D10RenderTargetView *m_renderTargetView;
	ID3D10Texture2D *m_texture;
	ID3D10ShaderResourceView *m_shaderResource;
public:
	RenderTarget(ID3D10Device *device, INT2 _size);
	RenderTarget(ID3D10Device *device, ID3D10Texture2D *backBuffer);
	~RenderTarget();
	ID3D10RenderTargetView **getRenderTargetView();
	ID3D10Texture2D *getTexture();
	ID3D10ShaderResourceView *getShaderResource();
	void clear(ID3D10Device *device);
};

#endif