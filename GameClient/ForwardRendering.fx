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
	float3 Tangent : TANGENT;
};

struct PSSceneIn
{
	float4 Pos  : SV_Position;
	float2 UVCoord : UVCOORD;
	float4 EyeCoord : EYE_COORD;
	float4 Normal : NORMAL;
	float3 Tangent : TANGENT;
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
	CullMode = NONE;
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
	
	//float4 kattpiss = mul( float4(input.Pos,1.0), modelMatrix );
	////kattpiss.y = -kattpiss.y;
	//kattpiss = mul(kattpiss, worldViewProjection);
	////output.Pos.y = -output.Pos.y;
	//output.Pos = kattpiss;
	//output.UVCoord = input.UVCoord;

	//variables needed for lighting
	output.Normal = mul(float4(input.Normal, 1.0f), modelMatrix);
	output.EyeCoord = mul( float4(input.Pos,1.0), modelMatrix );

	return output;
}

float4 PSScene(PSSceneIn input) : SV_Target
{	
	float4 color = tex2D.Sample(linearSampler, input.UVCoord);
	color.w *= modelAlpha;

	return color;
}

float4 psFuckRoland(PSSceneIn input) : SV_Target
{	
	return float4(0.0f, 0.0f, 1.0f, 1.0f);
}

DepthStencilState stencilOpKeep
{
	DepthEnable = TRUE;
	StencilEnable = TRUE;

	DepthFunc = GREATER;
	DepthWriteMask = ZERO;
	
	//StencilReadMask = 1;

	FrontFaceStencilFunc = NEVER;
	FrontFaceStencilFail = KEEP;
	FrontFaceStencilPass = KEEP;
	FrontFaceStencilDepthFail = KEEP;

	BackFaceStencilFunc = EQUAL;
	BackFaceStencilFail = KEEP;
	BackFaceStencilPass = REPLACE;
	BackFaceStencilDepthFail = KEEP;
};

technique10 ForwardGubb
{
    pass p0
    {
		SetBlendState( SrcAlphaBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader( CompileShader( vs_4_0, VSScene() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, psFuckRoland() ) );
		
	    SetDepthStencilState( stencilOpKeep, 1 );
	    SetRasterizerState( rs );
    }
}

technique10 RenderModelForward
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