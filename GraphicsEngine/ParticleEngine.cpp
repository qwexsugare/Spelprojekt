#include "ParticleEngine.h"

ParticleEngine::ParticleEngine(ID3D10Device* _device, TextureHolder* _textureHolder, EngineType _type, D3DXVECTOR4 _position, D3DXQUATERNION _rotation, D3DXVECTOR3 _scale)
{
	this->device = _device;
	this->type = _type;
	this->position = _position;
	this->rotation = _rotation;
	this->scale = _scale;
	this->textureHolder = _textureHolder;

	this->maxParticles = 100;

	this->isDead = false;

	this->totalTime = 0;
	this->dt = 0;

	this->firstTime = true;

	//this->particles = NULL;
	//this->geoParticles = NULL;
	this->shaderParticles = NULL;

	this->texture = this->textureHolder->getTexture("./particles/light.png");

	CreateVertexBuffer();
	CreateRandomTex();
}

ParticleEngine::~ParticleEngine()
{
	if(shaderParticles)
		shaderParticles->Release();
}
void ParticleEngine::CreateVertexBuffer()
{
	HRESULT hr;

	D3D10_BUFFER_DESC vbd;
	vbd.Usage			= D3D10_USAGE_DEFAULT;
	vbd.ByteWidth		= sizeof(Particle);
	vbd.BindFlags		= D3D10_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags	= 0;
	vbd.MiscFlags		= 0;

	Particle p;
	ZeroMemory(&p, sizeof(Particle));
	p.age = 0.0f;
	p.type = 0;
	p.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3D10_SUBRESOURCE_DATA initData;
	initData.pSysMem = &p;

	hr = device->CreateBuffer(&vbd, &initData, &vertexBuffer);
	if(FAILED(hr))
		MessageBox(NULL, "( ParticleEngine ) Failed to create Vertex Buffer", NULL, NULL);

	vbd.ByteWidth = sizeof(Particle) * maxParticles;
	vbd.BindFlags = D3D10_BIND_VERTEX_BUFFER | D3D10_BIND_STREAM_OUTPUT;

	hr = device->CreateBuffer(&vbd, 0, &drawVB);
	if(FAILED(hr))
		MessageBox(NULL, "( ParticleEngine ) Failed to create Draw Vertex Buffer", NULL, NULL);
	hr = device->CreateBuffer(&vbd, 0, &streamOutVB);
	if(FAILED(hr))
		MessageBox(NULL, "( ParticleEngine ) Failed to create StreamOut Vertex Buffer", NULL, NULL);

}

void ParticleEngine::CreateRandomTex()
{
	HRESULT hr;

	D3DXVECTOR4 randomValues[1024];

	for(int i = 0; i < 1024; i++)
	{
		randomValues[i].x = RandF(-1.0f, 1.f);
		randomValues[i].y = RandF(-1.0f, 1.f);
		randomValues[i].z = RandF(-1.0f, 1.f);
		randomValues[i].w = RandF(-1.0f, 1.f);
	}

	D3D10_SUBRESOURCE_DATA initData;
	initData.pSysMem			= randomValues;
	initData.SysMemPitch		= sizeof(D3DXVECTOR4)*1024;
	initData.SysMemSlicePitch	= sizeof(D3DXVECTOR4)*1024;

	D3D10_TEXTURE1D_DESC texDesc;
	texDesc.Width			= 1024;
	texDesc.MipLevels		= 1;
	texDesc.Format			= DXGI_FORMAT_R32G32B32A32_FLOAT;
	texDesc.Usage			= D3D10_USAGE_IMMUTABLE;
	texDesc.BindFlags		= D3D10_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags	= 0;
	texDesc.MiscFlags		= 0;
	texDesc.ArraySize		= 1;

	ID3D10Texture1D* randTex = 0;
	hr = device->CreateTexture1D(&texDesc, &initData, &randTex);
	if(FAILED(hr))
		MessageBox(NULL, "( ParticleEngine ) Failed to create Random Texture", NULL, NULL);

	D3D10_SHADER_RESOURCE_VIEW_DESC rViewDesc;
	rViewDesc.Format					= texDesc.Format;
	rViewDesc.ViewDimension				= D3D10_SRV_DIMENSION_TEXTURE1D;
	rViewDesc.Texture1D.MipLevels		= texDesc.MipLevels;
	rViewDesc.Texture1D.MostDetailedMip = 0;

	hr = device->CreateShaderResourceView(randTex, &rViewDesc, &randomTex);
	if(FAILED(hr))
		MessageBox(NULL, "( ParticleEngine ) Failed to create Random Texture ResourceView", NULL, NULL);

	randTex->Release();
}

void ParticleEngine::Draw(ParticleEngineEffectFile* _particleRendering, Camera* _camera)
{
	switch(this->type)
	{
	case EngineType::GPUBased:
		DrawGPUBased(_particleRendering, _camera);
		break;
	}
}

void ParticleEngine::Update(float _dt)
{
	this->dt = _dt;
	this->totalTime += _dt;
}

void ParticleEngine::Troll()
{

}

void ParticleEngine::DrawGPUBased(ParticleEngineEffectFile* _particleRendering, Camera* _camera)
{
	_particleRendering->setCameraPos(D3DXVECTOR4(_camera->getPos(), 1.0f));
	_particleRendering->setEmitPos(this->position);
	_particleRendering->setEmitDir(D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.0f));
	_particleRendering->setTotalTime(this->totalTime);
	_particleRendering->setDt(this->dt);
	D3DXMATRIX viewProj = _camera->getViewMatrix() * _camera->getProjectionMatrix();
	_particleRendering->setViewProj(viewProj);
	_particleRendering->setRandomTexture(randomTex);
	_particleRendering->setTexture(texture);


	device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);
	
	device->IASetInputLayout(_particleRendering->getInputLayout());


	UINT stride = sizeof(Particle);
	UINT offset = 0;

	if(firstTime)
		device->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	else
		device->IASetVertexBuffers(0, 1, &drawVB, &stride, &offset);
	


	//StreamOut
	device->SOSetTargets(1, &streamOutVB, &offset);
	
	D3D10_TECHNIQUE_DESC techDesc;
	_particleRendering->getUpSideDownTwistSOTechnique()->GetDesc(&techDesc);
	for(UINT p = 0; p < techDesc.Passes; p++)
	{
		_particleRendering->getUpSideDownTwistSOTechnique()->GetPassByIndex(p)->Apply(0);
		if(firstTime)
		{
			device->Draw(1, 0);
			firstTime = false;
		}
		else
		{
			device->DrawAuto();
		}
	}
	
	ID3D10Buffer* bufferArray[1] = {0};
	device->SOSetTargets(1, bufferArray, &offset);

	swap(drawVB, streamOutVB);

	//Draw
	device->IASetVertexBuffers(0, 1, &drawVB, &stride, &offset);

	_particleRendering->getDrawUpSideDownTwistTechnique()->GetDesc(&techDesc);
	for(UINT p = 0; p < techDesc.Passes; p++)
	{
		_particleRendering->getDrawUpSideDownTwistTechnique()->GetPassByIndex(p)->Apply(0);
		device->DrawAuto();
	}

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