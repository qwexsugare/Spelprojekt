cbuffer cb
{
	matrix viewProj;
	float3 camPosW;
	float3 origW;
	float3 targetW;
};

cbuffer cbFixed
{
	//TextureQuad
	float2 quadTexC[4] =
	{
		float2(0.0f, 1.0f),
		float2(1.1f, 1.0f),
		float2(0.0f, 0.0f),
		float2(1.0f, 0.0f)
	};
};

texture2D tex2D;

struct VSIn
{
	float3 Pos		: POS;
	float2 UVCoord	: UVCOORD;
};

struct GSIn
{
	float4 Pos		: SV_Position;
	float2 UVCoord	: UVCOORD;
};

struct GS_OUT
{
	float4 Pos		: SV_POSITION;
	float4 Color	: COLOR;
	float2 UVCoord	: TEXCOORD;
};

SamplerState linearSampler 
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


GSIn VS(VSIn input)
{
	GSIn output = (GSIn)0;
	return output;
}

[maxvertexcount(4)]
void GS(point GSIn input[1], inout TriangleStream<GS_OUT> triStream)
{
	float3 look = normalize(camPosW.xyz - input[0].Pos);
	float3 right = normalize(cross(float3(0,1,0), look));
	float3 up = cross(look, right);

	float4x4 W;
	W[0] = float4(right,		0.0f);
	W[1] = float4(up,			0.0f);
	W[2] = float4(look,			0.0f);
	W[3] = float4(input[0].Pos.xyz,	1.0f);

	// Creating Quad
	float halfWidth = 0.5f;
	float halfHeight = 0.5f;

	float4 v[4];
	v[0] = float4(-halfWidth, -halfHeight, 0.0f, 1.0f);
	v[1] = float4(+halfWidth, -halfHeight, 0.0f, 1.0f);
	v[2] = float4(-halfWidth, +halfHeight, 0.0f, 1.0f);
	v[3] = float4(+halfWidth, +halfHeight, 0.0f, 1.0f);

	GS_OUT output;
	[unroll]
	for(int i = 0; i < 4; ++i)
	{
		output.Pos = mul(v[i], viewProj);
		output.UVCoord = quadTexC[i];
		output.Color = float4(1, 1, 1, 1);
		triStream.Append(output);
	}
}

float4 PS(GS_OUT input) : SV_TARGET
{
	return float4(1, 1, 1, 1);//tex2D.Sample(linearSampler, input.UVCoord)*input.color;
}

technique10 ChainTech
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
		SetGeometryShader( CompileShader( gs_4_0, GS() ) );
		SetPixelShader ( CompileShader( ps_4_0, PS() ) );
		SetDepthStencilState( DisableDepth, 0 );
	}
}