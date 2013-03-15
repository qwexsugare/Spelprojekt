#include "ChainFXEffectFile.h"

ChainFXEffectFile::ChainFXEffectFile() : EffectFile()
{

}

ChainFXEffectFile::ChainFXEffectFile(ID3D10Device* _device) : EffectFile(_device, "ChainEffectRendering.fx")
{
	this->m_texture = this->m_effect->GetVariableByName("tex2D")->AsShaderResource();
	this->m_viewProj = this->m_effect->GetVariableByName("viewProj")->AsMatrix();
	this->m_orig = this->m_effect->GetVariableByName("origW")->AsVector();
	this->m_target = this->m_effect->GetVariableByName("targetW")->AsVector();
	this->m_camPos = this->m_effect->GetVariableByName("camPosW")->AsVector();


	D3D10_PASS_DESC passDescription;
	const D3D10_INPUT_ELEMENT_DESC vertexLayout[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "UVCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};

	this->m_technique = this->m_effect->GetTechniqueByName("ChainTech");

	this->m_technique->GetPassByIndex(0)->GetDesc(&passDescription);

	 _device->CreateInputLayout(vertexLayout,
		sizeof(vertexLayout) / sizeof(D3D10_INPUT_ELEMENT_DESC),
		passDescription.pIAInputSignature,
		passDescription.IAInputSignatureSize,
		&this->m_vertexLayout);
}

ChainFXEffectFile::~ChainFXEffectFile()
{

}
ID3D10EffectTechnique *ChainFXEffectFile::getTechnique()
{
	return this->m_technique;
}

void ChainFXEffectFile::setTexture(ID3D10ShaderResourceView* _texture)
{
	this->m_texture->SetResource(_texture);
}

void ChainFXEffectFile::setOrig(D3DXVECTOR3 _vec)
{
	this->m_orig->SetFloatVector((float*)_vec);
}

void ChainFXEffectFile::setTarget(D3DXVECTOR3 _vec)
{
	this->m_target->SetFloatVector((float*)_vec);
}

void ChainFXEffectFile::setViewProj(D3DXMATRIX _mat)
{
	this->m_viewProj->SetMatrix(_mat);
}

void ChainFXEffectFile::setCamPos(D3DXVECTOR3 _vec)
{
	this->m_camPos->SetFloatVector((float*)_vec);
}