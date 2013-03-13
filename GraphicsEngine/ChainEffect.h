#pragma once

#include "ChainFXEffectFile.h"
#include "VertexStructs.h"

class ChainEffect
{
private:
	D3DXVECTOR3 m_orig;
	D3DXVECTOR3 m_target;
	D3DXMATRIX m_viewProj;
	ID3D10Device* m_device;
	ID3D10Buffer* m_vertexBuffer;
	void CreateVertexBuffer();
public:
	ChainEffect(ID3D10Device* _device);
	~ChainEffect();
	void update(float _dt);
	void draw(ChainFXEffectFile* fxFile);
	DECLDIR void setViewProj(D3DXMATRIX _viewProj);
};

