#include "DeferredRenderingEffectFile.h"

DeferredRenderingEffectFile::DeferredRenderingEffectFile()
{

}

DeferredRenderingEffectFile::DeferredRenderingEffectFile(ID3D10Device* _device) : EffectFile(_device, "DeferredRendering.fx")
{
	this->m_positionTexture = this->m_effect->GetVariableByName("positionTexture")->AsShaderResource();
	this->m_normalTexture = this->m_effect->GetVariableByName("normalTexture")->AsShaderResource();
	this->m_diffuseTexture = this->m_effect->GetVariableByName("diffuseTexture")->AsShaderResource();

	this->m_nrOfPointLights = this->m_effect->GetVariableByName("nrOfPointLights")->AsScalar();
	this->m_nrOfDirectionalLights = this->m_effect->GetVariableByName("nrOfDirectionalLights")->AsScalar();
	this->m_nrOfSpotLights = this->m_effect->GetVariableByName("nrOfSpotLights")->AsScalar();
	this->m_lightPosition = this->m_effect->GetVariableByName("lightPosition")->AsVector();
	this->m_lightDirection = this->m_effect->GetVariableByName("lightDirection")->AsVector();
	this->m_lightAmbient = this->m_effect->GetVariableByName("la")->AsVector();
	this->m_lightDiffuse = this->m_effect->GetVariableByName("ld")->AsVector();
	this->m_lightSpecular = this->m_effect->GetVariableByName("ls")->AsVector();
	this->m_lightAngle = this->m_effect->GetVariableByName("lightAngle")->AsVector();
	this->m_lightRadius = this->m_effect->GetVariableByName("lightRadius")->AsScalar();

	this->m_cameraPosition = this->m_effect->GetVariableByName("cameraPosition")->AsVector();

	this->m_technique = this->m_effect->GetTechniqueByName("RenderModelDeferred");

	D3D10_PASS_DESC passDescription;
	const D3D10_INPUT_ELEMENT_DESC vertexLayout[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "UVCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};

	this->m_technique->GetPassByIndex(0)->GetDesc(&passDescription);

	 _device->CreateInputLayout(vertexLayout,
		sizeof(vertexLayout) / sizeof(D3D10_INPUT_ELEMENT_DESC),
		passDescription.pIAInputSignature,
		passDescription.IAInputSignatureSize,
		&this->m_vertexLayout);
	 
	m_shadowMaps = m_effect->GetVariableByName("shadowMaps")->AsShaderResource();
	m_lightWvps = m_effect->GetVariableByName("lightWvps")->AsMatrix();
}

DeferredRenderingEffectFile::~DeferredRenderingEffectFile()
{

}

void DeferredRenderingEffectFile::setPositionsTexture(ID3D10ShaderResourceView* _positionTexture)
{
	this->m_positionTexture->SetResource(_positionTexture);
}

void DeferredRenderingEffectFile::setNormalsTexture(ID3D10ShaderResourceView* _normalTexture)
{
	this->m_normalTexture->SetResource(_normalTexture);
}

void DeferredRenderingEffectFile::setDiffuseTexture(ID3D10ShaderResourceView* _diffuseTexture)
{
	this->m_diffuseTexture->SetResource(_diffuseTexture);
}

void DeferredRenderingEffectFile::setCameraPosition(D3DXVECTOR3 _lightPosition)
{
	this->m_cameraPosition->SetFloatVector(_lightPosition);
}

void DeferredRenderingEffectFile::updateLights(vector<PointLight*> pointLights, vector<DirectionalLight*> directionalLights, vector<SpotLight*> spotLights)
{
	D3DXVECTOR3 *tempPos = new D3DXVECTOR3[pointLights.size() + spotLights.size()];
	D3DXVECTOR3 *tempDir = new D3DXVECTOR3[directionalLights.size() + spotLights.size()];
	D3DXVECTOR3 *tempAmbient = new D3DXVECTOR3[pointLights.size() + directionalLights.size() + spotLights.size()];
	D3DXVECTOR3 *tempDiffuse = new D3DXVECTOR3[pointLights.size() + directionalLights.size() + spotLights.size()];
	D3DXVECTOR3 *tempSpecular = new D3DXVECTOR3[pointLights.size() + directionalLights.size() + spotLights.size()];
	D3DXVECTOR2 *tempAngle = new D3DXVECTOR2[spotLights.size()];
	float *tempRadius = new float[pointLights.size() + spotLights.size()];


	for(int i = 0; i < pointLights.size() && i < 50; i++)
	{
		tempPos[i] = pointLights[i]->getPosition().toD3DXVector();
		tempAmbient[i] = pointLights[i]->getAmbientColor().toD3DXVector();
		tempDiffuse[i] = pointLights[i]->getDiffuseColor().toD3DXVector();
		tempSpecular[i] = pointLights[i]->getSpecularColor().toD3DXVector();
		tempRadius[i] = pointLights[i]->getRadius();
	}

	for(int i = 0; i < directionalLights.size() && i < 50; i++)
	{
		tempDir[i] = directionalLights[i]->getDirection().toD3DXVector();
		tempAmbient[pointLights.size() + i] = directionalLights[i]->getAmbientColor().toD3DXVector();
		tempDiffuse[pointLights.size() + i] = directionalLights[i]->getDiffuseColor().toD3DXVector();
		tempSpecular[pointLights.size() + i] = directionalLights[i]->getSpecularColor().toD3DXVector();
	}

	for(int i = 0; i < spotLights.size() && i < 50; i++)
	{
		tempPos[pointLights.size() + i] = spotLights[i]->getPosition().toD3DXVector();
		tempDir[directionalLights.size() + i] = spotLights[i]->getDirection().toD3DXVector();
		tempAmbient[pointLights.size() + directionalLights.size() + i] = spotLights[i]->getAmbientColor().toD3DXVector();
		tempDiffuse[pointLights.size() + directionalLights.size() + i] = spotLights[i]->getDiffuseColor().toD3DXVector();
		tempSpecular[pointLights.size() + directionalLights.size() + i] = spotLights[i]->getSpecularColor().toD3DXVector();
		tempAngle[i] = spotLights[i]->getAngle().toD3DXVector();
		tempRadius[pointLights.size() + i] = spotLights[i]->getRange();
	}

	this->m_nrOfPointLights->SetInt(pointLights.size());
	this->m_nrOfDirectionalLights->SetInt(directionalLights.size());
	this->m_nrOfSpotLights->SetInt(spotLights.size());
	this->m_lightPosition->SetFloatVectorArray((float*)tempPos, 0, pointLights.size() + spotLights.size());
	this->m_lightDirection->SetFloatVectorArray((float*)tempDir, 0, directionalLights.size() + spotLights.size());
	this->m_lightAmbient->SetFloatVectorArray((float*)tempAmbient, 0, pointLights.size() + directionalLights.size() + spotLights.size());
	this->m_lightDiffuse->SetFloatVectorArray((float*)tempDiffuse, 0, pointLights.size() + directionalLights.size() + spotLights.size());
	this->m_lightSpecular->SetFloatVectorArray((float*)tempSpecular, 0, pointLights.size() + directionalLights.size() + spotLights.size());
	this->m_lightAngle->SetFloatVectorArray((float*)tempAngle, 0, spotLights.size());
	this->m_lightRadius->SetFloatArray((float*)tempRadius, 0, pointLights.size() + spotLights.size());

	delete tempPos;
	delete tempDir;
	delete tempAmbient;
	delete tempDiffuse;
	delete tempSpecular;
	delete tempAngle;
	delete tempRadius;
}

ID3D10EffectTechnique *DeferredRenderingEffectFile::getTechnique()
{
	return this->m_technique;
}

ID3D10InputLayout *DeferredRenderingEffectFile::getVertexLayout()
{
	return this->m_vertexLayout;
}

void DeferredRenderingEffectFile::setShadowMaps(ID3D10ShaderResourceView** _res, int _size)
{
	m_shadowMaps->SetResourceArray(_res, 0, _size);
}

void DeferredRenderingEffectFile::setLightWvps(D3DXMATRIX* _wvps, int _size)
{
	m_lightWvps->SetMatrixArray((float*)_wvps, 0, _size);
}