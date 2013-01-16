#pragma once

#include "effectfile.h"
#include "PointLight.h"

class DeferredRenderingEffectFile : public EffectFile
{
private:
	ID3D10EffectShaderResourceVariable* m_positionTexture;
	ID3D10EffectShaderResourceVariable* m_normalTexture;
	ID3D10EffectShaderResourceVariable* m_diffuseTexture;

	ID3D10EffectScalarVariable* m_nrOfLights;
	ID3D10EffectVectorVariable* m_lightPosition;
	ID3D10EffectVectorVariable* m_lightAmbient;
	ID3D10EffectVectorVariable* m_lightDiffuse;
	ID3D10EffectVectorVariable* m_lightSpecular;

	ID3D10EffectTechnique *m_technique;
	ID3D10InputLayout *m_vertexLayout;
public:
	DeferredRenderingEffectFile();
	DeferredRenderingEffectFile(ID3D10Device* _device);
	~DeferredRenderingEffectFile();

	void setPositionsTexture(ID3D10ShaderResourceView* _positionTexture);
	void setNormalsTexture(ID3D10ShaderResourceView* _normalTexture);
	void setDiffuseTexture(ID3D10ShaderResourceView* _diffuseTexture);
	void updateLights(vector<PointLight*> lights);

	ID3D10EffectTechnique *getTechnique();
	ID3D10InputLayout *getVertexLayout();
};

