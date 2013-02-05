#pragma once
#include "effectfile.h"
class DeferredSamplerEffectFile : public EffectFile
{
private:
	// Universal
	ID3D10EffectShaderResourceVariable* m_texture;
	ID3D10EffectMatrixVariable* m_modelMatrix;
	ID3D10EffectMatrixVariable* m_viewMatrix;
	ID3D10EffectMatrixVariable* m_projectionMatrix;
	ID3D10InputLayout *m_vertexLayout;

	// Model
	ID3D10EffectScalarVariable* m_modelAlpha;
	ID3D10EffectShaderResourceVariable* m_boneTexture;
	ID3D10EffectTechnique *m_technique;
	ID3D10EffectTechnique *m_animationTechnique;
	
	// Terrain
	ID3D10EffectTechnique* m_renderTerrain;
	ID3D10EffectShaderResourceVariable* m_terrainTextures;
	ID3D10EffectShaderResourceVariable* m_terrainBlendMaps;
	ID3D10EffectShaderResourceVariable* m_normalMaps;
	
	// Road
	ID3D10EffectTechnique* m_renderRoad;
	ID3D10InputLayout *m_vertexAnimationLayout;
	
	ID3D10EffectMatrixVariable* m_lightWvps;
public:
	ID3D10EffectTechnique* renderShadowMap;

	DeferredSamplerEffectFile();
	DeferredSamplerEffectFile(ID3D10Device* _device);
	~DeferredSamplerEffectFile();

	void setModelAlpha(float _modelAlpha);
	void setModelMatrix(D3DXMATRIX _matrix);
	void setViewMatrix(D3DXMATRIX _matrix);
	void setProjectionMatrix(D3DXMATRIX _matrix);

	void setTexture(ID3D10ShaderResourceView *_texture);
	void DeferredSamplerEffectFile::setBoneTexture(ID3D10ShaderResourceView *_texture);
	ID3D10InputLayout *getInputLayout()const;
	ID3D10InputLayout *getInputAnimationLayout() const;
	
	ID3D10EffectTechnique *getTechnique();
	ID3D10EffectTechnique *getAnimationTechnique();

	ID3D10EffectTechnique *getRenderTerrainTechnique();
	void setNormalMaps(ID3D10ShaderResourceView* _texture);
	void setTerrainTextures(ID3D10ShaderResourceView** _textures, int _size);
	void setTerrainBlendMaps(ID3D10ShaderResourceView** _blendMaps, int _size);
	
	ID3D10EffectTechnique* getRenderRoadTechnique();
	
	void setLightWvps(D3DXMATRIX* _wvps, int _size);
};

