#pragma once

#include "effectfile.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"

class DeferredRenderingEffectFile : public EffectFile
{
private:
	ID3D10EffectShaderResourceVariable* m_positionTexture;
	ID3D10EffectShaderResourceVariable* m_normalTexture;
	ID3D10EffectShaderResourceVariable* m_diffuseTexture;
	ID3D10EffectShaderResourceVariable* m_tangentTexture;

	ID3D10EffectScalarVariable* m_nrOfPointLights;
	ID3D10EffectScalarVariable* m_nrOfShadowedPointLights;
	ID3D10EffectScalarVariable* m_nrOfDirectionalLights;
	ID3D10EffectScalarVariable* m_nrOfSpotLights;
	ID3D10EffectVectorVariable* m_lightPosition;
	ID3D10EffectVectorVariable* m_lightDirection;
	ID3D10EffectVectorVariable* m_lightAmbient;
	ID3D10EffectVectorVariable* m_lightDiffuse;
	ID3D10EffectVectorVariable* m_lightSpecular;
	ID3D10EffectVectorVariable* m_lightAngle;
	ID3D10EffectScalarVariable* m_lightRadius;

	ID3D10EffectVectorVariable* m_cameraPosition;

	ID3D10EffectTechnique *m_technique;
	ID3D10InputLayout *m_vertexLayout;

	ID3D10EffectShaderResourceVariable* m_pointLightShadowMaps;
	ID3D10EffectShaderResourceVariable* m_spotLightShadowMaps;
	ID3D10EffectMatrixVariable* m_pointLightWvps;
	ID3D10EffectMatrixVariable* m_spotLightWvps;
public:
	DeferredRenderingEffectFile();
	DeferredRenderingEffectFile(ID3D10Device* _device);
	~DeferredRenderingEffectFile();

	void setPositionsTexture(ID3D10ShaderResourceView* _positionTexture);
	void setNormalsTexture(ID3D10ShaderResourceView* _normalTexture);
	void setDiffuseTexture(ID3D10ShaderResourceView* _diffuseTexture);
	void setTangentTexture(ID3D10ShaderResourceView* _tangentTexture);
	void setCameraPosition(D3DXVECTOR3 _cameraPosition);
	void updateLights(vector<PointLight*> pointLights, vector<DirectionalLight*> directionalLights, vector<SpotLight*> spotLights);

	ID3D10EffectTechnique *getTechnique();
	ID3D10InputLayout *getVertexLayout();
	void setPointLightShadowMaps(ID3D10ShaderResourceView** _res, int _size);
	void setSpotLightShadowMaps(ID3D10ShaderResourceView** _res, int _size);
	void setPointLightWvps(D3DXMATRIX* _wvps, int _size);
	void setSpotLightWvps(D3DXMATRIX* _wvps, int _size);
};
