#ifndef PARTICLESTRUCTS
#define PARTICLESTRUCTS


struct Particle
{
	float3 pos	: POSITION;
	float3 vel	: VELOCITY;
	float2 size	: SIZE;
	float age	: AGE;
	uint type	: TYPE;
};

struct VS_OUT
{
	float3 pos	: POSITION;
	float2 size	: SIZE;
	float4 color: COLOR;
	uint type	: TYPE;
};

struct GS_OUT
{
	float4 pos	: SV_POSITION;
	float4 color: COLOR;
	float2 texC	: TEXCOORD;
};

cbuffer cb
{
	float4 camPosW;
	float4 emitPosW;
	float4 emitDirW;

	float totalTime;
	float dt;
	float4x4 viewProj;
};

cbuffer cbFixed
{
	//Used to accelrate particles
	float3 accel = {0.0f, 0.08f, 0.0f};

	//TextureQuad
	float2 quadTexC[4] =
	{
		float2(0.0f, 1.0f),
		float2(1.1f, 1.0f),
		float2(0.0f, 0.0f),
		float2(1.0f, 0.0f)
	};
};

Texture2D tex;
Texture1D randomTex;

SamplerState triLinearSam
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

DepthStencilState DisableDepth
{
	DepthEnable		= FALSE;
	DepthWriteMask	= ZERO;
};

DepthStencilState NoDepthWrites
{
    DepthEnable = TRUE;
    DepthWriteMask = ZERO;
};

BlendState AdditiveBlending
{
	AlphaToCoverageEnable	= FALSE;
	BlendEnable[0]			= TRUE;
	SrcBlend				= SRC_ALPHA;
	DestBlend				= ONE;
	BlendOp					= ADD;
	SrcBlendAlpha			= ZERO;
	DestBlendAlpha			= ZERO;
	BlendOpAlpha			= ADD;
	RenderTargetWriteMask[0]= 0x0F;
};

float3 RandUnitVec3(float offset)
{
	//Use game time plus offset to sample random texture.
	float u = (totalTime + offset);
	
	//coordinates in [-1,1]
	float3 v = randomTex.SampleLevel(triLinearSam, u, 0);
	
	// project onto unit sphere
	return normalize(v);
}

#define EMITTER 0
#define PARTICLE 1

#endif