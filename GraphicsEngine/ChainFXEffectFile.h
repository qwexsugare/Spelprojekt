#pragma once
#include "effectfile.h"

class ChainFXEffectFile : public EffectFile
{
private:
	ID3D10EffectShaderResourceVariable* m_texture;
	ID3D10EffectVectorVariable* m_orig;
	ID3D10EffectVectorVariable* m_target;
	ID3D10EffectMatrixVariable* m_viewProj;
	ID3D10EffectVectorVariable* m_camPos;
	ID3D10EffectTechnique *m_technique;
	ID3D10InputLayout *m_vertexLayout;
public:
	ChainFXEffectFile();
	ChainFXEffectFile(ID3D10Device* _device);
	~ChainFXEffectFile();

	ID3D10EffectTechnique *getTechnique();
	ID3D10InputLayout* getInputLayout(){return this->m_vertexLayout;}

	DECLDIR void setTexture(ID3D10ShaderResourceView* _texture);
	DECLDIR void setOrig(D3DXVECTOR3 _vec);
	DECLDIR void setTarget(D3DXVECTOR3 _vec);
	DECLDIR void setViewProj(D3DXMATRIX _matrix);
	DECLDIR void setCamPos(D3DXVECTOR3 _vec);
};