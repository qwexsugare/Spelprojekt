#include "ForwardRenderingEffectFile.h"

ForwardRenderingEffectFile::ForwardRenderingEffectFile(void) : EffectFile()
{

}

ForwardRenderingEffectFile::ForwardRenderingEffectFile(ID3D10Device* _device) : EffectFile(_device, "ForwardRendering.fx")
{
	this->m_modelMatrix = this->m_effect->GetVariableByName("modelMatrix")->AsMatrix();
	this->m_viewMatrix = this->m_effect->GetVariableByName("viewMatrix")->AsMatrix();
	this->m_projectionMatrix = this->m_effect->GetVariableByName("projectionMatrix")->AsMatrix();

	this->m_renderModelForward = this->m_effect->GetTechniqueByName("RenderModelForward");
}


ForwardRenderingEffectFile::~ForwardRenderingEffectFile(void)
{

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