#include "ParticleEngineEffectFile.h"

ParticleEngineEffectFile::ParticleEngineEffectFile() : EffectFile()
{

}

ParticleEngineEffectFile::ParticleEngineEffectFile(ID3D10Device* _device) : EffectFile(_device, "ParticleEngineRendering.fx", true)
{
	this->camPosW = this->m_effect->GetVariableByName("camPosW")->AsVector();
	this->emitPosW = this->m_effect->GetVariableByName("emitPosW")->AsVector();
	this->emitDirW = this->m_effect->GetVariableByName("emitDirW")->AsVector();
	this->totalTime = this->m_effect->GetVariableByName("totalTime")->AsScalar();
	this->dt = this->m_effect->GetVariableByName("dt")->AsScalar();
	this->size = this->m_effect->GetVariableByName("size")->AsVector();
	this->viewProj = this->m_effect->GetVariableByName("viewProj")->AsMatrix();
	this->isAlive = this->m_effect->GetVariableByName("isAlive")->AsScalar();

	this->m_randomTexture = this->m_effect->GetVariableByName("randomTex")->AsShaderResource();
	this->m_texture = this->m_effect->GetVariableByName("tex")->AsShaderResource();


	D3D10_PASS_DESC passDescription;
	D3D10_INPUT_ELEMENT_DESC vertexLayout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"VELOCITY", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"SIZE",     0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"AGE",      0, DXGI_FORMAT_R32_FLOAT,       0, 32, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"TYPE",     0, DXGI_FORMAT_R32_UINT,        0, 36, D3D10_INPUT_PER_VERTEX_DATA, 0},
	};
	
	this->m_beaconSOTechnique = this->m_effect->GetTechniqueByName("BeaconSO");
	this->m_drawBeaconTechnique = this->m_effect->GetTechniqueByName("DrawBeacon");
	this->m_upSideDownTwistSOTechnique = this->m_effect->GetTechniqueByName("UsDTwistSOTech");
	this->m_drawUpSideDownTwistTechnique = this->m_effect->GetTechniqueByName("DrawUsDTwist");
	this->m_circlePulsSOTechnique = this->m_effect->GetTechniqueByName("CirclePulsSOTech");
	this->m_drawCirclePulsTechnique = this->m_effect->GetTechniqueByName("DrawCirclePuls");
	this->m_sphereSOTechnique = this->m_effect->GetTechniqueByName("SphereSOTech");
	this->m_drawSphereTechnique = this->m_effect->GetTechniqueByName("DrawSphere");

	this->m_beaconSOTechnique->GetPassByIndex(0)->GetDesc(&passDescription);

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

void ParticleEngineEffectFile::setRandomTexture(ID3D10ShaderResourceView* _texture)
{
	this->m_randomTexture->SetResource(_texture);
}

void ParticleEngineEffectFile::setCameraPos(D3DXVECTOR4 _cameraPos)
{
	this->camPosW->SetFloatVector((float*)_cameraPos);
}

void ParticleEngineEffectFile::setEmitPos(D3DXVECTOR4 _emitPos)
{
	this->emitPosW->SetFloatVector((float*)_emitPos);
}

void ParticleEngineEffectFile::setEmitDir(D3DXVECTOR4 _emitDir)
{
	this->emitDirW->SetFloatVector((float*)_emitDir);
}

void ParticleEngineEffectFile::setTotalTime(float _time)
{
	this->totalTime->SetFloat((float)_time);
}

void ParticleEngineEffectFile::setDt(float _dt)
{
	this->dt->SetFloat(_dt);
}

void ParticleEngineEffectFile::setIsAlive(bool _alive)
{
	this->isAlive->SetBool(_alive);
}

void ParticleEngineEffectFile::setSize(D3DXVECTOR2 _size)
{
	this->size->SetFloatVector((float*)_size);
}

void ParticleEngineEffectFile::setViewProj(D3DXMATRIX _matrix)
{
	this->viewProj->SetMatrix(_matrix);
}

ID3D10EffectTechnique *ParticleEngineEffectFile::getBeaconSOTechnique()
{
	return this->m_beaconSOTechnique;
}

ID3D10EffectTechnique *ParticleEngineEffectFile::getDrawBeaconTechnique()
{
	return this->m_drawBeaconTechnique;
}

ID3D10EffectTechnique *ParticleEngineEffectFile::getUpSideDownTwistSOTechnique()
{
	return this->m_upSideDownTwistSOTechnique;
}

ID3D10EffectTechnique *ParticleEngineEffectFile::getDrawUpSideDownTwistTechnique()
{
	return this->m_drawUpSideDownTwistTechnique;
}

ID3D10EffectTechnique *ParticleEngineEffectFile::getCirclePulsSOTechnique()
{
	return this->m_circlePulsSOTechnique;
}

ID3D10EffectTechnique *ParticleEngineEffectFile::getDrawCirclePulsTechnique()
{
	return this->m_drawCirclePulsTechnique;
}

ID3D10EffectTechnique *ParticleEngineEffectFile::getSphereSOTechnique()
{
	return this->m_sphereSOTechnique;
}

ID3D10EffectTechnique *ParticleEngineEffectFile::getDrawSphereTechnique()
{
	return this->m_drawSphereTechnique;
}
