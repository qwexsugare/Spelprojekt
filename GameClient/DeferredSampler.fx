Texture2D tex2D;

SamplerState linearSampler 
{
	Filter = MIN_MAG_MIP_LINEAR; // coming up after the break!
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VSSceneIn
{
	float3 Pos	: POS;
	float2 UVCoord : UVCOORD;
	float3 Normal : NORMAL;
};

struct PSSceneIn
{
	float4 Pos  : SV_Position;		// SV_Position is a (S)ystem (V)ariable that denotes transformed position
	float2 UVCoord : UVCOORD;
	float4 EyeCoord : EYE_COORD;
	float3 Normal : NORMAL;
};

struct PSSceneOut
{
	float4 Pos : SV_TARGET0;
	float4 Normal : SV_TARGET1;
	float4 Diffuse : SV_TARGET2;
};

//Variables that updated often
cbuffer cbEveryFrame
{
	//Transformation matrices
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix modelMatrix;

	float modelAlpha;
};

// State Structures
DepthStencilState DisableDepth
{
    DepthEnable = FALSE;
    DepthWriteMask = ZERO;
};

DepthStencilState EnableDepth
{
    DepthEnable = TRUE;
    DepthWriteMask = ALL;
};

RasterizerState rs
{
	//FillMode = Solid;
	CullMode = FRONT;
};

BlendState NoBlend
{
	BlendEnable[0] = FALSE;
};

BlendState SrcAlphaBlend
{
   BlendEnable[0]           = TRUE;
   SrcBlend                 = SRC_ALPHA;
   DestBlend                = INV_SRC_ALPHA;
   BlendOp                  = ADD;
   SrcBlendAlpha            = ONE;
   DestBlendAlpha           = ONE;
   BlendOpAlpha             = ADD;
   RenderTargetWriteMask[0] = 0x0F;
};

PSSceneIn VSScene(VSSceneIn input)
{
	PSSceneIn output = (PSSceneIn)0;

	matrix worldViewProjection = mul(viewMatrix, projectionMatrix);
	
	// transform the point into view space
	output.Pos = mul( float4(input.Pos,1.0), mul(modelMatrix,worldViewProjection) );
	output.UVCoord = input.UVCoord;

	//variables needed for lighting
	output.Normal = input.Normal;
	output.EyeCoord = mul( float4(input.Pos,1.0), mul(modelMatrix,viewMatrix) );

	return output;
}

PSSceneOut PSScene(PSSceneIn input) : SV_Target
{	
	PSSceneOut output = (PSSceneOut)0;
	float4 color = tex2D.Sample(linearSampler, input.UVCoord);
	color.w = modelAlpha;

	output.Pos = input.Pos;
	output.Normal = float4(input.Normal, 1.0f);
	//output.Diffuse = color;
	output.Diffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);

	return output;
}

technique10 DeferredSample
{
    pass p0
    {
		SetBlendState( SrcAlphaBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader( CompileShader( vs_4_0, VSScene() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSScene() ) );

	    SetDepthStencilState( EnableDepth, 0 );
	    SetRasterizerState( rs );
    }  
}