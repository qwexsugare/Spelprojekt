#pragma once

#include "stdafx.h"
#include "Mesh.h"

enum ParticleType{EMITTER, PARTICLE};

struct Particle
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity;
	D3DXVECTOR2 size;
	float age;
	UINT type;
};

struct GeoParticle
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity;
	D3DXVECTOR3 size;
	ParticleType type;
	float age;
	Mesh* m_mesh;
};