#pragma once
#include "EffectFile.h"

class ForwardRenderingEffectFile : public EffectFile
{
private:
	ID3D10EffectMatrixVariable* m_modelMatrix;
	ID3D10EffectMatrixVariable* m_viewMatrix;
	ID3D10EffectMatrixVariable* m_projectionMatrix;
	ID3D10EffectMatrixVariable* m_propsMatrix;
	ID3D10EffectScalarVariable* m_modelAlpha;

	ID3D10EffectVectorVariable* m_color;

	ID3D10EffectShaderResourceVariable* m_texture;
	ID3D10EffectShaderResourceVariable* m_boneTexture;
	
	ID3D10EffectTechnique *m_renderModelForward;
	ID3D10InputLayout *m_vertexLayout;
	
	ID3D10EffectTechnique *m_animationTechnique;
	ID3D10InputLayout *m_vertexAnimationLayout;

	ID3D10EffectTechnique *m_propTechnique;
public:
	ID3D10EffectTechnique* m_forwardGubb;

	ForwardRenderingEffectFile();
	ForwardRenderingEffectFile(ID3D10Device* _device);
	~ForwardRenderingEffectFile();

	void setModelAlpha(float _modelAlpha);
	void setModelMatrix(D3DXMATRIX _matrix);
	void setViewMatrix(D3DXMATRIX _matrix);
	void setPropsMatrix(D3DXMATRIX _matrix);
	void setProjectionMatrix(D3DXMATRIX _matrix);
	void setColor(D3DXVECTOR4 _color);
	
	void setBoneTexture(ID3D10ShaderResourceView *_texture);

	void setTexture(ID3D10ShaderResourceView *_texture);
	ID3D10InputLayout *getInputLayout()const;
	ID3D10InputLayout *getInputAnimationLayout() const;

	ID3D10EffectTechnique *getTechniqueRenderModelForward();
	ID3D10EffectTechnique *getAnimationTechnique();
	ID3D10EffectTechnique *getPropsTechnique();
};

