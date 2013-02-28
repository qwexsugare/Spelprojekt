#pragma once
#include "effectfile.h"
class DeferredSamplerEffectFile : public EffectFile
{
private:
	// Universal
	ID3D10EffectShaderResourceVariable* m_texture;
	ID3D10EffectShaderResourceVariable* m_normalMap;
	ID3D10EffectShaderResourceVariable* m_glowMap;
	ID3D10EffectShaderResourceVariable* m_specularMap;
	ID3D10EffectMatrixVariable* m_modelMatrix;
	ID3D10EffectMatrixVariable* m_viewMatrix;
	ID3D10EffectMatrixVariable* m_projectionMatrix;
	ID3D10EffectMatrixVariable* m_propsMatrix;
	ID3D10InputLayout *m_vertexLayout;

	// Model
	ID3D10EffectScalarVariable* m_modelAlpha;
	ID3D10EffectShaderResourceVariable* m_boneTexture;
	ID3D10EffectTechnique *m_technique;
	ID3D10EffectTechnique *m_animationTechnique;
	
	// Terrain
	ID3D10EffectTechnique* m_renderTerrain;
	ID3D10EffectShaderResourceVariable* m_terrainTextures;
	ID3D10EffectShaderResourceVariable* m_terrainNormalMaps;
	ID3D10EffectShaderResourceVariable* m_terrainSpecularMaps;
	ID3D10EffectShaderResourceVariable* m_terrainBlendMaps;
	
	//Anders
	ID3D10InputLayout *m_vertexAnimationLayout;
	ID3D10InputLayout *m_vertexSuperLayout;
	ID3D10EffectTechnique *m_superTechnique;
	ID3D10EffectVectorVariable* m_cameraPosition;
	ID3D10EffectTechnique *m_propsTechnique;

	// Road
	ID3D10EffectTechnique* m_renderRoad;
	
	//Shadows
	ID3D10EffectMatrixVariable* m_lightWvp;
	ID3D10EffectTechnique* m_renderShadowMap;
	ID3D10EffectTechnique* m_renderShadowMapAnimation;
	ID3D10EffectTechnique* m_renderShadowMapProps;
public:

	DeferredSamplerEffectFile();
	DeferredSamplerEffectFile(ID3D10Device* _device);
	~DeferredSamplerEffectFile();

	void setModelAlpha(float _modelAlpha);
	void setModelMatrix(D3DXMATRIX _matrix);
	void setViewMatrix(D3DXMATRIX _matrix);
	void setProjectionMatrix(D3DXMATRIX _matrix);
	void setPropsMatrix(D3DXMATRIX* _matrix);

	void setTexture(ID3D10ShaderResourceView *_texture);
	void setNormalMap(ID3D10ShaderResourceView *_texture);
	void setGlowMap(ID3D10ShaderResourceView *_texture);
	void setSpecularMap(ID3D10ShaderResourceView *_texture);
	void DeferredSamplerEffectFile::setBoneTexture(ID3D10ShaderResourceView *_texture);
	ID3D10InputLayout *getInputLayout()const;
	ID3D10InputLayout *getInputAnimationLayout() const;
	ID3D10InputLayout *getSuperInputLayout() const;
	
	ID3D10EffectTechnique *getTechnique();
	ID3D10EffectTechnique *getAnimationTechnique();
	ID3D10EffectTechnique *getSuperTechnique();
	ID3D10EffectTechnique *getPropsTechnique();

	ID3D10EffectTechnique *getShadowTechnique();
	ID3D10EffectTechnique *getShadowAnimationTechnique();
	ID3D10EffectTechnique *getShadowPropsTechnique();

	void setCameraPosition(D3DXVECTOR3 _cameraPos);


	ID3D10EffectTechnique *getRenderTerrainTechnique();
	void setTerrainTextures(ID3D10ShaderResourceView** _textures, int _size);
	void setTerrainNormalMaps(ID3D10ShaderResourceView** _normalMaps, int _size);
	void setTerrainSpecularMaps(ID3D10ShaderResourceView** _specularMaps, int _size);
	void setTerrainBlendMaps(ID3D10ShaderResourceView** _blendMaps, int _size);
	
	ID3D10EffectTechnique* getRenderRoadTechnique();
	
	void setLightWvp(const D3DXMATRIX& _wvp);
};

