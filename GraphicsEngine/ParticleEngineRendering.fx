Texture2D myTexture;

cbuffer cBuffer
{

}

struct VSIn
{
	float3 Pos	: POS;
	float2 UVCoord : UVCOORD;
};


struct PSIn
{
	float4 Pos  : SV_Position;
	float2 UVCoord : UVCOORD;
};

SamplerState linearSampler 
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

BlendState NoBlend
{
   BlendEnable[0]           = FALSE;
   SrcBlend                 = SRC_ALPHA;
   DestBlend                = INV_SRC_ALPHA;
   BlendOp                  = ADD;
   SrcBlendAlpha            = ONE;
   DestBlendAlpha           = ZERO;
   BlendOpAlpha             = ADD;
   RenderTargetWriteMask[0] = 0x0F;
};

BlendState SrcAlphaBlend
{
   BlendEnable[0]           = TRUE;
   SrcBlend                 = SRC_ALPHA;
   DestBlend                = INV_SRC_ALPHA;
   BlendOp                  = ADD;
   SrcBlendAlpha            = ONE;
   DestBlendAlpha           = ZERO;
   BlendOpAlpha             = ADD;
   RenderTargetWriteMask[0] = 0x0F;
};

BlendState AdditiveBlending
{
	AlphaToCoverageEnable	= FALSE;
	BlendEnable[0]			= TRUE;
	SrcBlend				= SRC_ALPHA;
	DestBlend				= ONE;
	BlendOp					= ADD;
	SrcBlendAlpha			= 1;
	DestBlendAlpha			= ZERO;
	BlendOpAlpha			= ADD;
	RenderTargetWriteMask[0]= 0x0F;
};

DepthStencilState DisableDepth
{
    DepthEnable = FALSE;
    DepthWriteMask = ZERO;
};

DepthStencilState EnableDeapth
{
    DepthEnable = TRUE;
    DepthWriteMask = ALL;
};

RasterizerState rs
{
	FillMode = Solid;
	CullMode = None;
};


PSIn VSGlow( VSIn input )
{
	PSIn output = (PSIn)0;
	output.Pos = float4(input.Pos, 1.0f);
	output.UVCoord = input.UVCoord;
	return output;
}

float4 PSUpSample(PSIn input) : SV_Target
{
	float4 color = myTexture.Sample(linearSampler, input.UVCoord);
	return color;
}

technique10 ParticleTech
{
	pass p0
	{
		SetBlendState( NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

		SetVertexShader( CompileShader( vs_4_0, VSGlow() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSUpSample() ) );

	    SetDepthStencilState( EnableDepth, 0 );
	    SetRasterizerState( rs );
	}	
}