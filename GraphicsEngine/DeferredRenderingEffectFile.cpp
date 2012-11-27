#include "DeferredRenderingEffectFile.h"

DeferredRenderingEffectFile::DeferredRenderingEffectFile()
{

}

DeferredRenderingEffectFile::DeferredRenderingEffectFile(ID3D10Device* _device) : EffectFile(_device, "DefferedRendering.fx")
{
	this->m_positionTexture = this->m_effect->GetVariableByName("positionTexture")->AsShaderResource();
	this->m_normalTexture = this->m_effect->GetVariableByName("normalTexture")->AsShaderResource();
	this->m_diffuseTexture = this->m_effect->GetVariableByName("diffuseTexture")->AsShaderResource();

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

ID3D10EffectTechnique *DeferredRenderingEffectFile::getTechnique()
{
	return this->m_technique;
}

ID3D10InputLayout *DeferredRenderingEffectFile::getVertexLayout()
{
	return this->m_vertexLayout;
}