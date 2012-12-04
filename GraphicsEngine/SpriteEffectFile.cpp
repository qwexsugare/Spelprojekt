#include "SpriteEffectFile.h"

SpriteEffectFile::SpriteEffectFile(ID3D10Device* _device) : EffectFile(_device, "SpriteRendering.fx")
{
	this->m_texture = this->m_effect->GetVariableByName("tex2D")->AsShaderResource();
	this->m_modelMatrix = this->m_effect->GetVariableByName("modelMatrix")->AsMatrix();
	this->m_technique = this->m_effect->GetTechniqueByName("RenderSprite");

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

SpriteEffectFile::~SpriteEffectFile(void)
{

}

void SpriteEffectFile::setTexture(ID3D10ShaderResourceView* _texture)
{
	this->m_texture->SetResource(_texture);
}

void SpriteEffectFile::setModelMatrix(D3DXMATRIX _modelMatrix)
{
	this->m_modelMatrix->SetMatrix((float*)_modelMatrix);
}

ID3D10EffectTechnique *SpriteEffectFile::getTechnique()
{
	return this->m_technique;
}

ID3D10InputLayout *SpriteEffectFile::getVertexLayout()
{
	return this->m_vertexLayout;
}