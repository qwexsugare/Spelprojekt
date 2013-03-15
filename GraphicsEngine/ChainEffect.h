#pragma once

#include "ChainFXEffectFile.h"
#include "VertexStructs.h"
#include "TextureHolder.h"

class ChainEffect
{
private:
	D3DXVECTOR3 m_orig;
	D3DXVECTOR3 m_target;
	D3DXVECTOR3 m_camPos;
	D3DXMATRIX m_viewProj;
	ID3D10Device* m_device;
	ID3D10Buffer* m_vertexBuffer;
	ID3D10ShaderResourceView* m_texture;
	void CreateVertexBuffer();
public:
	ChainEffect(ID3D10Device* _device, TextureHolder* _textureHolder);
	~ChainEffect();
	void update(float _dt);
	void draw(ChainFXEffectFile* fxFile);
	DECLDIR void setViewProj(D3DXMATRIX _viewProj);
	DECLDIR void setOrig(D3DXVECTOR3 _vec);
	DECLDIR void setTarget(D3DXVECTOR3 _vec);
	DECLDIR void setCamPos(D3DXVECTOR3 _vec);
};

