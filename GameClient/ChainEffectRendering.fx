cbuffer cb
{
	float4x4 viewProj;
	float3 camPosW;
	float3 origW;
	float3 targetW;
};

cbuffer cbFixed
{
	//TextureQuad
	float2 quadTexC[4] =
	{
		float2(0.0f, 0.0f),
		float2(0.0f, 1.0f),
		float2(1.0f, 0.0f),
		float2(1.1f, 1.0f),
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

RasterizerState raster
{
	FillMode = Solid;
	CullMode = NONE;
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


GSIn VS(VSIn input)
{
	GSIn output = (GSIn)0;
	return output;
}

[maxvertexcount(4)]
void GS(point GSIn input[1], inout LineStream<GS_OUT> triStream)
{
	float halfWidth = 0.5f;
	float halfHeight = 0.5f;

	float3 look0 = float3(0, 1, 0);//normalize(camPosW.xyz - origW.xyz);
	float3 look1 = float3(0, 1, 0);//normalize(camPosW.xyz - targetW.xyz);

	float3 a = normalize(origW.xyz - targetW.xyz);

	float3 cr0 = cross(look0, a);
	float3 cr1 = cross(look1, a);

	float4 v[4];
	v[0] = float4(origW + (cr0 * halfWidth) , 1);
	//v[1] = float4(origW - (cr0 * halfWidth) , 1);
	v[1] = float4(1, 0, 0 , 1);
	v[2] = float4(targetW + (cr1 * halfWidth) , 1);
	//v[3] = float4(targetW - (cr1 * halfWidth) , 1);
	v[3] = float4(0, 0, 0, 1);

	GS_OUT output = (GS_OUT)0;/*

	output.Pos = mul(v[0], viewProj);
	output.UVCoord = quadTexC[0];
	triStream.Append(output);*/
			
	output.Pos = v[1];//mul(v[1], viewProj);
	output.UVCoord = quadTexC[1];
	triStream.Append(output);
/*
	output.Pos = mul(v[2], viewProj);
	output.UVCoord = quadTexC[2];
	triStream.Append(output);*/

	output.Pos = v[3];//mul(v[3], viewProj);
	output.UVCoord = quadTexC[3];
	triStream.Append(output);


}

float4 PS(GS_OUT input) : SV_TARGET
{
	return float4(1,1,1,1);//tex2D.Sample(linearSampler, input.UVCoord);
}

technique10 ChainTech
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
		SetGeometryShader( CompileShader( gs_4_0, GS() ) );
		SetPixelShader ( CompileShader( ps_4_0, PS() ) );
		SetDepthStencilState( DisableDepth, 0 );
		SetRasterizerState(raster);
		SetBlendState( AdditiveBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff );
	}
}