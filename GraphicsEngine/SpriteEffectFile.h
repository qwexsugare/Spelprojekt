#pragma once
#include "effectfile.h"

class SpriteEffectFile : public EffectFile
{
private:
	ID3D10EffectMatrixVariable* m_modelMatrix;
	ID3D10EffectMatrixVariable* m_projectionMatrix;
	ID3D10EffectShaderResourceVariable* m_texture;

	ID3D10EffectTechnique *m_technique;
	ID3D10InputLayout *m_vertexLayout;
public:
	SpriteEffectFile(ID3D10Device* _device);
	~SpriteEffectFile(void);

	void setTexture(ID3D10ShaderResourceView* _texture);
	void setModelMatrix(D3DXMATRIX _modelMatrix);
	void setProjectionMatrix(D3DXMATRIX _projectionMatrix);

	ID3D10EffectTechnique *getTechnique();
	ID3D10InputLayout *getVertexLayout();
};

