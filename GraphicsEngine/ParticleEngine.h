#pragma once

#include "Particle.h"
#include "stdafx.h"

using namespace std;

class ParticleEngine
{
private:
	vector<Particle>* particles;
	ID3D10Buffer* shaderParticles;
	vector<GeoParticle>* geoParticles;

	enum EngineType{CPUAndModels, CPUAndGShader, GPUBased};
	EngineType type;

	D3DXMATRIX	worldMatrix;
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;
public:
	ParticleEngine(EngineType _type, D3DXVECTOR3 _position, D3DXVECTOR3 _rotation, D3DXVECTOR3 _scale);
	~ParticleEngine();

	D3DXMATRIX*		getWorldMatrix();
	D3DXVECTOR3*	getPosition;
	D3DXVECTOR3*	getRotation;
	D3DXVECTOR3*	getScale;
	EngineType*		getType();

	void			setPosition();
	void			setRotation();
	void			setScale();
};
