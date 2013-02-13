#include "SSAOEffectFile.h"

SSAOEffectFile::SSAOEffectFile() : EffectFile()
{

}

SSAOEffectFile::SSAOEffectFile(ID3D10Device* _device) : EffectFile(_device, "SSAO.fx")
{
	this->m_depthTexture = this->m_effect->GetVariableByName("depthTexture")->AsShaderResource();


	D3D10_PASS_DESC passDescription;
	const D3D10_INPUT_ELEMENT_DESC vertexLayout[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "UVCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};

	this->m_techniqueVert = this->m_effect->GetTechniqueByName("VerticalBlur");
	this->m_techniqueHori = this->m_effect->GetTechniqueByName("HorizontalBlur");
	this->m_technique = this->m_effect->GetTechniqueByName("SSAO");

	this->m_technique->GetPassByIndex(0)->GetDesc(&passDescription);

	 _device->CreateInputLayout(vertexLayout,
		sizeof(vertexLayout) / sizeof(D3D10_INPUT_ELEMENT_DESC),
		passDescription.pIAInputSignature,
		passDescription.IAInputSignatureSize,
		&this->m_vertexLayout);
}

SSAOEffectFile::~SSAOEffectFile()
{

}

void SSAOEffectFile::setDepthTexture(ID3D10ShaderResourceView* _depthTexture)
{
	this->m_depthTexture->SetResource(_depthTexture);
}

ID3D10EffectTechnique *SSAOEffectFile::getTechniqueVert()
{
	return this->m_techniqueVert;
}

ID3D10EffectTechnique *SSAOEffectFile::getTechniqueHori()
{
	return this->m_techniqueHori;
}

ID3D10EffectTechnique *SSAOEffectFile::getTechnique()
{
	return this->m_technique;
}
