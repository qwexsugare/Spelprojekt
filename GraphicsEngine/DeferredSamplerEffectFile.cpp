#include "DeferredSamplerEffectFile.h"

DeferredSamplerEffectFile::DeferredSamplerEffectFile() : EffectFile()
{

}

DeferredSamplerEffectFile::DeferredSamplerEffectFile(ID3D10Device* _device) : EffectFile(_device, "DeferredSampler.fx")
{
	this->m_modelMatrix = this->m_effect->GetVariableByName("modelMatrix")->AsMatrix();
	this->m_viewMatrix = this->m_effect->GetVariableByName("viewMatrix")->AsMatrix();
	this->m_projectionMatrix = this->m_effect->GetVariableByName("projectionMatrix")->AsMatrix();
	this->m_modelAlpha = this->m_effect->GetVariableByName("modelAlpha")->AsScalar();
	this->m_texture = this->m_effect->GetVariableByName("tex2D")->AsShaderResource();
	this->m_boneTexture = this->m_effect->GetVariableByName("boneTex")->AsShaderResource();
	this->m_technique = this->m_effect->GetTechniqueByName("DeferredSample");
	this->m_animationTechnique = this->m_effect->GetTechniqueByName("DeferredAnimationSample");
	
	D3D10_PASS_DESC passDescription;
	this->m_technique->GetPassByIndex(0)->GetDesc(&passDescription);
	const D3D10_INPUT_ELEMENT_DESC vertexLayout[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "UVCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};
	 _device->CreateInputLayout(vertexLayout,
		sizeof(vertexLayout) / sizeof(D3D10_INPUT_ELEMENT_DESC),
		passDescription.pIAInputSignature,
		passDescription.IAInputSignatureSize,
		&this->m_vertexLayout);
	 
	//Animation
	 D3D10_PASS_DESC animationPassDescription;
	this->m_animationTechnique->GetPassByIndex(0)->GetDesc(&animationPassDescription);
	const D3D10_INPUT_ELEMENT_DESC vertexAnimationLayout[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "UVCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONE", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};
	 _device->CreateInputLayout(vertexAnimationLayout,
		sizeof(vertexAnimationLayout) / sizeof(D3D10_INPUT_ELEMENT_DESC),
		animationPassDescription.pIAInputSignature,
		animationPassDescription.IAInputSignatureSize,
		&this->m_vertexAnimationLayout);

	// Terrain
	this->m_renderTerrain = this->m_effect->GetTechniqueByName("RenderTerrain");
	this->m_terrainTextures = this->m_effect->GetVariableByName("terrainTextures")->AsShaderResource();
	this->m_terrainBlendMaps = this->m_effect->GetVariableByName("terrainBlendMaps")->AsShaderResource();
	 
	// Road
	this->m_renderRoad = this->m_effect->GetTechniqueByName("RenderRoad");
}


DeferredSamplerEffectFile::~DeferredSamplerEffectFile()
{

}

void DeferredSamplerEffectFile::setModelAlpha(float _modelAlpha)
{
	this->m_modelAlpha->SetFloat(_modelAlpha);
}

void DeferredSamplerEffectFile::setModelMatrix(D3DXMATRIX _matrix)
{
	this->m_modelMatrix->SetMatrix((float*)_matrix);
}

void DeferredSamplerEffectFile::setViewMatrix(D3DXMATRIX _matrix)
{
	this->m_viewMatrix->SetMatrix((float*)_matrix);
}

void DeferredSamplerEffectFile::setProjectionMatrix(D3DXMATRIX _matrix)
{
	this->m_projectionMatrix->SetMatrix((float*)_matrix);
}

void DeferredSamplerEffectFile::setTexture(ID3D10ShaderResourceView *_texture)
{
	this->m_texture->SetResource(_texture);
}

void DeferredSamplerEffectFile::setBoneTexture(ID3D10ShaderResourceView *_texture)
{
	this->m_boneTexture->SetResource(_texture);
}

ID3D10EffectTechnique *DeferredSamplerEffectFile::getTechnique()
{
	return this->m_technique;
}

ID3D10EffectTechnique *DeferredSamplerEffectFile::getAnimationTechnique()
{
	return this->m_animationTechnique;
}

ID3D10InputLayout *DeferredSamplerEffectFile::getInputLayout() const
{
	return this->m_vertexLayout;
}

ID3D10InputLayout *DeferredSamplerEffectFile::getInputAnimationLayout() const
{
	return this->m_vertexAnimationLayout;
}

ID3D10EffectTechnique* DeferredSamplerEffectFile::getRenderRoadTechnique()
{
	return m_renderRoad;
}

ID3D10EffectTechnique* DeferredSamplerEffectFile::getRenderTerrainTechnique()
{
	return this->m_renderTerrain;
}

void DeferredSamplerEffectFile::setTerrainTextures(ID3D10ShaderResourceView** _textures, int _size)
{
	this->m_terrainTextures->SetResourceArray(_textures, 0, _size);
}

void DeferredSamplerEffectFile::setTerrainBlendMaps(ID3D10ShaderResourceView** _blendMaps, int _size)
{
	this->m_terrainBlendMaps->SetResourceArray(_blendMaps, 0, _size);
}