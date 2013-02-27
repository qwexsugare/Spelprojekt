#pragma once

#include "Particle.h"
#include "stdafx.h"
#include "DeviceHandler.h"

using namespace std;

class ParticleEngine
{
private:
	vector<Particle> particles;
	ID3D10Buffer* shaderParticles;
	vector<GeoParticle> geoParticles;
	BoundingSphere m_bs;
	UINT type;
	DeviceHandler* deviceHandler;
	void CreateVertexBuffer();

	D3DXMATRIX	worldMatrix;
	D3DXVECTOR3 position;
	D3DXQUATERNION rotation;
	D3DXVECTOR3 scale;
	
	bool isDead;
public:
	enum EngineType{CPUAndModels, CPUAndGShader, GPUBased};

	ParticleEngine(DeviceHandler* _deviceHandler, EngineType _type, D3DXVECTOR3 _position, D3DXQUATERNION _rotation, D3DXVECTOR3 _scale);
	~ParticleEngine();

	const D3DXMATRIX&	getWorldMatrix()const { return worldMatrix; }
	const D3DXVECTOR3&	getPosition()const { return position; }
	const D3DXQUATERNION&	getRotation() const { return rotation; }
	const D3DXVECTOR3&	getScale()const { return scale; }
	const UINT&	getType()const { return type; }
	const BoundingSphere& getBs()const { return m_bs; }

	void setPosition(D3DXVECTOR3& _pos);
	void setRotation(D3DXVECTOR3& _rot);
	void setScale(D3DXVECTOR3& _scale);
	void Draw(ID3D10Device* _device);
	void Update(float _dt);
	void Troll();
};
