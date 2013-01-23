#include "DeferredRenderingEffectFile.h"

DeferredRenderingEffectFile::DeferredRenderingEffectFile()
{

}

DeferredRenderingEffectFile::DeferredRenderingEffectFile(ID3D10Device* _device) : EffectFile(_device, "DeferredRendering.fx")
{
	this->m_positionTexture = this->m_effect->GetVariableByName("positionTexture")->AsShaderResource();
	this->m_normalTexture = this->m_effect->GetVariableByName("normalTexture")->AsShaderResource();
	this->m_diffuseTexture = this->m_effect->GetVariableByName("diffuseTexture")->AsShaderResource();

	this->m_nrOfLights = this->m_effect->GetVariableByName("nrOfLights")->AsScalar();
	this->m_lightPosition = this->m_effect->GetVariableByName("lightPosition")->AsVector();
	this->m_lightAmbient = this->m_effect->GetVariableByName("la")->AsVector();
	this->m_lightDiffuse = this->m_effect->GetVariableByName("ld")->AsVector();
	this->m_lightSpecular = this->m_effect->GetVariableByName("ls")->AsVector();

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

void DeferredRenderingEffectFile::updateLights(vector<PointLight*> lights)
{
	this->m_nrOfLights->SetInt(lights.size());

	D3DXVECTOR3 *tempPos = new D3DXVECTOR3[lights.size()];
	D3DXVECTOR3 *tempAmbient = new D3DXVECTOR3[lights.size()];
	D3DXVECTOR3 *tempDiffuse = new D3DXVECTOR3[lights.size()];
	D3DXVECTOR3 *tempSpecular = new D3DXVECTOR3[lights.size()];

	for(int i = 0; i < lights.size() && i < 50; i++)
	{
		tempPos[i] = lights[i]->getPosition().toD3DXVector();
		tempAmbient[i] = lights[i]->getAmbientColor().toD3DXVector();
		tempDiffuse[i] = lights[i]->getDiffuseColor().toD3DXVector();
		tempSpecular[i] = lights[i]->getSpecularColor().toD3DXVector();
	}

	this->m_lightPosition->SetFloatVectorArray((float*)tempPos, 0, lights.size());
	this->m_lightAmbient->SetFloatVectorArray((float*)tempAmbient, 0, lights.size());
	this->m_lightDiffuse->SetFloatVectorArray((float*)tempDiffuse, 0, lights.size());
	this->m_lightSpecular->SetFloatVectorArray((float*)tempSpecular, 0, lights.size());

	delete tempPos;
	delete tempAmbient;
	delete tempDiffuse;
	delete tempSpecular;
}

ID3D10EffectTechnique *DeferredRenderingEffectFile::getTechnique()
{
	return this->m_technique;
}

ID3D10InputLayout *DeferredRenderingEffectFile::getVertexLayout()
{
	return this->m_vertexLayout;
}