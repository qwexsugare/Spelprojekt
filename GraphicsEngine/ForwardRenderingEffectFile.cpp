#include "ForwardRenderingEffectFile.h"

ForwardRenderingEffectFile::ForwardRenderingEffectFile(void) : EffectFile()
{

}

ForwardRenderingEffectFile::ForwardRenderingEffectFile(ID3D10Device* _device) : EffectFile(_device, "ForwardRendering.fx")
{
	this->m_modelMatrix = this->m_effect->GetVariableByName("modelMatrix")->AsMatrix();
	this->m_viewMatrix = this->m_effect->GetVariableByName("viewMatrix")->AsMatrix();
	this->m_projectionMatrix = this->m_effect->GetVariableByName("projectionMatrix")->AsMatrix();
	this->m_modelAlpha = this->m_effect->GetVariableByName("modelAlpha")->AsScalar();

	this->m_texture = this->m_effect->GetVariableByName("tex2D")->AsShaderResource();
	
	this->m_renderModelForward = this->m_effect->GetTechniqueByName("RenderModelForward");
	
	m_forwardGubb = m_effect->GetTechniqueByName("ForwardGubb");

	D3D10_PASS_DESC passDescription;

	const D3D10_INPUT_ELEMENT_DESC vertexLayout[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "UVCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};

	this->m_renderModelForward->GetPassByIndex(0)->GetDesc(&passDescription);

	 _device->CreateInputLayout(vertexLayout,
		sizeof(vertexLayout) / sizeof(D3D10_INPUT_ELEMENT_DESC),
		passDescription.pIAInputSignature,
		passDescription.IAInputSignatureSize,
		&this->m_vertexLayout);
}


ForwardRenderingEffectFile::~ForwardRenderingEffectFile(void)
{

}

void ForwardRenderingEffectFile::setModelAlpha(float _modelAlpha)
{
	this->m_modelAlpha->SetFloat(_modelAlpha);
}

void ForwardRenderingEffectFile::setModelMatrix(D3DXMATRIX _matrix)
{
	this->m_modelMatrix->SetMatrix((float*)_matrix);
}

void ForwardRenderingEffectFile::setViewMatrix(D3DXMATRIX _matrix)
{
	this->m_viewMatrix->SetMatrix((float*)_matrix);
}

void ForwardRenderingEffectFile::setProjectionMatrix(D3DXMATRIX _matrix)
{
	this->m_projectionMatrix->SetMatrix((float*)_matrix);
}

void ForwardRenderingEffectFile::setTexture(ID3D10ShaderResourceView *_texture)
{
	this->m_texture->SetResource(_texture);
}

ID3D10EffectTechnique *ForwardRenderingEffectFile::getTechniqueRenderModelForward()
{
	return this->m_renderModelForward;
}

ID3D10InputLayout *ForwardRenderingEffectFile::getInputLayout() const
{
	return this->m_vertexLayout;
}