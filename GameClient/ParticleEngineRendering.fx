cbuffer cb
{
	float4 camPosW;
	float4 emitPosW;
	float4 emitDirW;

	float totalTime;
	float dt;
	float4x4 VP;
};

cbuffer cbFixed
{
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

Texture2D tex2D;
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
	float u = (totalTime + offset);
	
	//coordinates in [-1,1]
	float3 v = randomTex.SampleLevel(triLinearSam, u, 0);
	
	return normalize(v);
}

#define EMITTER 0
#define PARTICLE 1

struct Particle
{
	float3 pos	: POSITION;
	float3 vel	: VELOCITY;
	float2 size	: SIZE;
	float age	: AGE;
	uint type	: TYPE;
};

Particle StreamOutVS(Particle input)
{
	return input;
}

[maxvertexcount(2)]
void StreamOutGS(point Particle input[1], inout PointStream<Particle> pStream)
{
	input[0].age += dt;

	if(input[0].type == EMITTER)
	{
		if(input[0].age > 1.0f)
		{
			float3 randVe = RandUnitVec3(0.0f);
			randVe.x *= 0.5f;
			randVe.y *= 0.5f;
		
			Particle p;
			p.pos = emitPosW.xyz;
			p.vel = 4.0f*randVe;
			p.size = float2(15.0f, 15.0f);
			p.age = 0.0f;
			p.type = PARTICLE;

			pStream.Append(p);

			input[0].age = 0.0f;
		}
		pStream.Append(input[0]);
	}
	else
	{
		if(input[0].age <= 10.0f)
			pStream.Append(input[0]);
	}
}

GeometryShader gsStreamOut = ConstructGSWithSO(
	CompileShader( gs_4_0, StreamOutGS() ),
	"POSITION.xyz; VELOCITY.xyz; SIZE.xy; AGE.x; TYPE.x");


technique10 StreamOutTech
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, StreamOutVS() ) );
		SetGeometryShader( gsStreamOut );
		SetPixelShader ( NULL );
		SetDepthStencilState( DisableDepth, 0 );
	}
}

//*********
// DrawTech
//*********

struct VS_OUT
{
	float3 pos	: POSITION;
	float2 size	: SIZE;
	float4 color: COLOR;
	uint type	: TYPE;
};

VS_OUT DrawVS(Particle input)
{
	VS_OUT output;

	float t = input.age;
	output.pos = input.pos;
	output.pos = input.pos +  5.5f*(t*t*accel);//0.5f*t*t*accel + t*input.vel + input.pos;

	float opacity = 1.0f - smoothstep(0.0f, 1.0f, t/10.0f);

	output.color = float4(1.0f, 1.0f, 1.0f, opacity);

	output.size = input.size;
	output.type = input.type;

	return output;
}

struct GS_OUT
{
	float4 pos	: SV_POSITION;
	float4 color: COLOR;
	float2 texC	: TEXCOORD;
};

[maxvertexcount(4)]
void DrawGS(point VS_OUT input[1], inout TriangleStream<GS_OUT> triStream)
{
	if(input[0].type =! EMITTER)
	{
		float3 look = normalize(camPosW.xyz - input[0].pos);
		float3 right = normalize(cross(float3(0,1,0), look));
		float3 up = cross(look, right);

		float4x4 W;
		W[0] = float4(right,		0.0f);
		W[1] = float4(up,			0.0f);
		W[2] = float4(look,			0.0f);
		W[3] = float4(input[0].pos,	1.0f);
		
		float4x4 WVP = mul(W, VP);

		// Creating Quad
		float halfWidth = 0.5f*input[0].size.x;
		float halfHeight = 0.5f*input[0].size.y;

		float4 v[4];
		v[0] = float4(-halfWidth, -halfHeight, 0.0f, 1.0f);
		v[1] = float4(+halfWidth, -halfHeight, 0.0f, 1.0f);
		v[2] = float4(-halfWidth, +halfHeight, 0.0f, 1.0f);
		v[3] = float4(+halfWidth, +halfHeight, 0.0f, 1.0f);

		GS_OUT output;
		[unroll]
		for(int i = 0; i < 4; ++i)
		{
			output.pos = mul(v[i], WVP);
			output.texC = quadTexC[i];
			output.color = input[0].color;
			triStream.Append(output);
		}
	}
}

float4 DrawPS(GS_OUT input) : SV_TARGET
{
	return tex2D.Sample(triLinearSam, float3(input.texC, 0))*input.color;
}


technique10 DrawAddBlendTech
{
	pass P0
	{
		SetVertexShader(	CompileShader( vs_4_0, DrawVS() ) );
		SetGeometryShader(	CompileShader( gs_4_0, DrawGS() ) );
		SetPixelShader (	CompileShader( ps_4_0, DrawPS() ) );
		SetBlendState( AdditiveBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff );
		SetDepthStencilState( NoDepthWrites, 0 );
	}
}