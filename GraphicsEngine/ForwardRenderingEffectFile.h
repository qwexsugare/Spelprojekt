#pragma once
#include "EffectFile.h"

class ForwardRenderingEffectFile : public EffectFile
{
private:
	ID3D10EffectMatrixVariable* m_modelMatrix;
	ID3D10EffectMatrixVariable* m_viewMatrix;
	ID3D10EffectMatrixVariable* m_projectionMatrix;

	ID3D10EffectShaderResourceVariable* m_texture;

	ID3D10EffectTechnique *m_renderModelForward;
	ID3D10InputLayout *m_vertexLayout;
public:
	ForwardRenderingEffectFile();
	ForwardRenderingEffectFile(ID3D10Device* _device);
	~ForwardRenderingEffectFile();

	void setModelMatrix(D3DXMATRIX _matrix);
	void setViewMatrix(D3DXMATRIX _matrix);
	void setProjectionMatrix(D3DXMATRIX _matrix);

	void setTexture(ID3D10ShaderResourceView *_texture);
	ID3D10InputLayout *getInputLayout()const;

	ID3D10EffectTechnique *getTechniqueRenderModelForward();
};

