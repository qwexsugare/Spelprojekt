#pragma once

#include "Particle.h"
#include "d3dUtil.h"
#include "stdafx.h"
#include "DeviceHandler.h"
#include "Camera.h"
#include "ParticleEngineEffectFile.h"
#include "TextureHolder.h"
#include "ParticleEffect.h"

using namespace std;

class ParticleEngine
{
private:
	vector<Particle> particles;
	ID3D10Buffer* shaderParticles;
	vector<GeoParticle> geoParticles;
	BoundingSphere m_bs;
	UINT type;
	ID3D10Device* device;
	void CreateVertexBuffer();
	TextureHolder* textureHolder;

	ID3D10ShaderResourceView* randomTex;
	ID3D10ShaderResourceView* texture;

	ID3D10BlendState* addBlend;
	ID3D10BlendState* alphBlend;

	D3DXMATRIX	worldMatrix;
	D3DXVECTOR4 position;
	D3DXQUATERNION rotation;
	D3DXVECTOR2 scale;

	ID3D10Buffer* vertexBuffer;
	ID3D10Buffer* drawVB;
	ID3D10Buffer* streamOutVB;
	UINT maxParticles;
	void CreateRandomTex();
	float totalTime;
	float dt;
	float emitRate;
	float lifeTime;
	float speed;
	float offset;
	float rotateSpeed;

	D3DXVECTOR4 color;

	bool firstTime;

	void DrawGPUBased(ParticleEngineEffectFile* _particleRendering, Camera* _camera);
	void DrawGPUBeacon(ParticleEngineEffectFile* _particleRendering);
	void DrawGPUCirclePuls(ParticleEngineEffectFile* _particleRendering);
	void DrawGPUSphere(ParticleEngineEffectFile* _particleRendering);
	void DrawGPUUpSideDownTwist(ParticleEngineEffectFile* _particleRendering);
	void DrawGPUFire(ParticleEngineEffectFile* _particleRendering);
	void DrawGPUElectric(ParticleEngineEffectFile* _particleRendering);
	void DrawGPUAura(ParticleEngineEffectFile* _particleRendering);
	
	enum ParticleBehavior{	Beacon,
							CirclePuls, 
							Sphere, 
							UpSideDownTwist,
							Fire,
							Electric,
							Aura};

	ParticleBehavior behavior;

	bool isAlive;
public:
	enum EngineType{CPUAndModels, CPUAndGShader, GPUBased};

	ParticleEngine(ParticleEffect* _pe, ID3D10Device* _device, TextureHolder* _textureHolder, EngineType _type, D3DXVECTOR4 _position, D3DXQUATERNION _rotation, D3DXVECTOR2 _scale);
	~ParticleEngine();

	const D3DXMATRIX&	getWorldMatrix()const { return worldMatrix; }
	const D3DXVECTOR4&	getPosition()const { return position; }
	const D3DXQUATERNION&	getRotation() const { return rotation; }
	const D3DXVECTOR2&	getScale()const { return scale; }
	const UINT&	getType()const { return type; }
	const BoundingSphere& getBs()const { return m_bs; }

	DECLDIR void setPosition(D3DXVECTOR3& _pos);
	DECLDIR void setRotation(D3DXQUATERNION& _rot);
	DECLDIR void setScale(D3DXVECTOR2& _scale);
	DECLDIR void setAlive(bool _alive);
	void Draw(ParticleEngineEffectFile* _particleRendering, Camera* _camera);
	void Update(float _dt);
	void Troll();
};
