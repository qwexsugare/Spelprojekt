#include "ParticleEngineEffectFile.h"

ParticleEngineEffectFile::ParticleEngineEffectFile() : EffectFile()
{

}

ParticleEngineEffectFile::ParticleEngineEffectFile(ID3D10Device* _device) : EffectFile(_device, "ParticleEngineRendering.fx")
{
	this->m_texture = this->m_effect->GetVariableByName("texture")->AsShaderResource();


	D3D10_PASS_DESC passDescription;
	const D3D10_INPUT_ELEMENT_DESC vertexLayout[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "VEL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "SIZE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "AGE", 0, DXGI_FORMAT_R32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TYPE", 0, DXGI_FORMAT_R32_UINT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};
	
	this->m_streamOutTechnique = this->m_effect->GetTechniqueByName("StreamOutTech");
	this->m_drawAddBlendTechnique = this->m_effect->GetTechniqueByName("DrawAddBlendTech");

	this->m_streamOutTechnique->GetPassByIndex(0)->GetDesc(&passDescription);

	 _device->CreateInputLayout(vertexLayout,
		sizeof(vertexLayout) / sizeof(D3D10_INPUT_ELEMENT_DESC),
		passDescription.pIAInputSignature,
		passDescription.IAInputSignatureSize,
		&this->m_vertexLayout);
}

ParticleEngineEffectFile::~ParticleEngineEffectFile()
{

}

void ParticleEngineEffectFile::setTexture(ID3D10ShaderResourceView* _texture)
{
	this->m_texture->SetResource(_texture);
}

ID3D10EffectTechnique *ParticleEngineEffectFile::getDrawAddBlendTechnique()
{
	return this->m_drawAddBlendTechnique;
}

ID3D10EffectTechnique *ParticleEngineEffectFile::getStreamOutTechnique()
{
	return this->m_streamOutTechnique;
}
