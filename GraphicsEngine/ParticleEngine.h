#pragma once

#include "Particle.h"
#include "d3dUtil.h"
#include "stdafx.h"
#include "DeviceHandler.h"
#include "Camera.h"
#include "ParticleEngineEffectFile.h"
#include "TextureHolder.h"

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

	D3DXMATRIX	worldMatrix;
	D3DXVECTOR4 position;
	D3DXQUATERNION rotation;
	D3DXVECTOR3 scale;

	ID3D10Buffer* vertexBuffer;
	ID3D10Buffer* drawVB;
	ID3D10Buffer* streamOutVB;

	UINT maxParticles;

	void CreateRandomTex();

	float totalTime;
	float dt;

	bool firstTime;

	void DrawGPUBased(ParticleEngineEffectFile* _particleRendering, Camera* _camera);
	
	bool isDead;
public:
	enum EngineType{CPUAndModels, CPUAndGShader, GPUBased};

	ParticleEngine(ID3D10Device* _device, TextureHolder* _textureHolder, EngineType _type, D3DXVECTOR4 _position, D3DXQUATERNION _rotation, D3DXVECTOR3 _scale);
	~ParticleEngine();

	const D3DXMATRIX&	getWorldMatrix()const { return worldMatrix; }
	const D3DXVECTOR4&	getPosition()const { return position; }
	const D3DXQUATERNION&	getRotation() const { return rotation; }
	const D3DXVECTOR3&	getScale()const { return scale; }
	const UINT&	getType()const { return type; }
	const BoundingSphere& getBs()const { return m_bs; }

	void setPosition(D3DXVECTOR3& _pos);
	void setRotation(D3DXVECTOR3& _rot);
	void setScale(D3DXVECTOR3& _scale);
	void Draw(ParticleEngineEffectFile* _particleRendering, Camera* _camera);
	void Update(float _dt);
	void Troll();
};
