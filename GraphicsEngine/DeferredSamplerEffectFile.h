#pragma once
#include "effectfile.h"
class DeferredSamplerEffectFile : public EffectFile
{
private:
	// Model
	ID3D10EffectScalarVariable* m_modelAlpha;
	ID3D10EffectShaderResourceVariable* m_texture;
	ID3D10EffectTechnique *m_technique;
	
	// Terrain
	//ID3D10EffectShaderResourceVariable* m_texture;
	ID3D10EffectTechnique* m_renderTerrain;

	// Universal
	ID3D10EffectMatrixVariable* m_modelMatrix;
	ID3D10EffectMatrixVariable* m_viewMatrix;
	ID3D10EffectMatrixVariable* m_projectionMatrix;
	ID3D10InputLayout *m_vertexLayout;
public:
	DeferredSamplerEffectFile();
	DeferredSamplerEffectFile(ID3D10Device* _device);
	~DeferredSamplerEffectFile();

	void setModelAlpha(float _modelAlpha);
	void setModelMatrix(D3DXMATRIX _matrix);
	void setViewMatrix(D3DXMATRIX _matrix);
	void setProjectionMatrix(D3DXMATRIX _matrix);

	void setTexture(ID3D10ShaderResourceView *_texture);
	ID3D10InputLayout *getInputLayout()const;
	
	ID3D10EffectTechnique *getTechnique();
	ID3D10EffectTechnique *getRenderTerrainTechique();
};

