#include "ParticleEngine.h"

ParticleEngine::ParticleEngine(DeviceHandler* _deviceHandler, EngineType _type, D3DXVECTOR3 _position, D3DXQUATERNION _rotation, D3DXVECTOR3 _scale)
{
	this->deviceHandler = _deviceHandler;
	this->type = _type;
	this->position = _position;
	this->rotation = _rotation;
	this->scale = _scale;

	this->isDead = false;

	//this->particles = NULL;
	//this->geoParticles = NULL;
	this->shaderParticles = NULL;
}

ParticleEngine::~ParticleEngine()
{
	if(shaderParticles)
		shaderParticles->Release();
}

void ParticleEngine::CreateVertexBuffer()
{
	
}

void ParticleEngine::Draw(ID3D10Device* _device)
{
	switch(this->type)
	{
	case EngineType::GPUBased:
		
		break;
	}
}

void ParticleEngine::Update(float _dt)
{

}

void ParticleEngine::Troll()
{

}

void ParticleEngine::setPosition(D3DXVECTOR3& _pos)
{

}

void ParticleEngine::setRotation(D3DXVECTOR3& _rot)
{

}

void ParticleEngine::setScale(D3DXVECTOR3& _scale)
{

}