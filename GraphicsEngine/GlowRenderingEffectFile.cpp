#include "GlowRenderingEffectFile.h"

GlowRenderingEffectFile::GlowRenderingEffectFile() : EffectFile()
{

}

GlowRenderingEffectFile::GlowRenderingEffectFile(ID3D10Device* _device) : EffectFile(_device, "GlowRendering.fx")
{
	this->m_glowTexture = this->m_effect->GetVariableByName("glowTexture")->AsShaderResource();


	D3D10_PASS_DESC passDescription;
	const D3D10_INPUT_ELEMENT_DESC vertexLayout[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "UVCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};

	this->m_techniqueVert = this->m_effect->GetTechniqueByName("VerticalBlur");
	this->m_techniqueHori = this->m_effect->GetTechniqueByName("HorizontalBlur");
	this->m_technique = this->m_effect->GetTechniqueByName("GlowBlending");

	this->m_technique->GetPassByIndex(0)->GetDesc(&passDescription);

	 _device->CreateInputLayout(vertexLayout,
		sizeof(vertexLayout) / sizeof(D3D10_INPUT_ELEMENT_DESC),
		passDescription.pIAInputSignature,
		passDescription.IAInputSignatureSize,
		&this->m_vertexLayout);
}

GlowRenderingEffectFile::~GlowRenderingEffectFile()
{

}

void GlowRenderingEffectFile::setGlowTexture(ID3D10ShaderResourceView* _glowTexture)
{
	this->m_glowTexture->SetResource(_glowTexture);
}

ID3D10EffectTechnique *GlowRenderingEffectFile::getTechniqueVert()
{
	return this->m_techniqueVert;
}

ID3D10EffectTechnique *GlowRenderingEffectFile::getTechniqueHori()
{
	return this->m_techniqueHori;
}

ID3D10EffectTechnique *GlowRenderingEffectFile::getTechnique()
{
	return this->m_technique;
}
