Texture2D tex2D;
Texture1D boneTex;

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

struct VSAnimSceneIn
{
	float3 Pos		: POS;
	float2 UVCoord	: UVCOORD;
	float3 Normal	: NORMAL;
	float4 Weight	: WEIGHT;
	float4 Bone		: BONE;
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

float4x4 GetBoneMatrix(int boneIndex, float4 _bone)
{
	float4x4 bone;
	
	bone[0] = boneTex.Load(int2((_bone[boneIndex]) * 4 + 0, 0), 0); // int2(x, mipMapLevel), int(offset)
	bone[1] = boneTex.Load(int2((_bone[boneIndex]) * 4 + 1, 0), 0); // int2(x, mipMapLevel), int(offset)
	bone[2] = boneTex.Load(int2((_bone[boneIndex]) * 4 + 2, 0), 0); // int2(x, mipMapLevel), int(offset)
	bone[3] = boneTex.Load(int2((_bone[boneIndex]) * 4 + 3, 0), 0); // int2(x, mipMapLevel), int(offset)
	
	return bone;
}

PSSceneIn VSAnimScene(VSAnimSceneIn input)
{
	PSSceneIn output = (PSSceneIn)0;

	matrix viewProjection = mul(viewMatrix, projectionMatrix);
	
	//Animation
	float4 myPos = float4(input.Pos, 1.0);
	output.Pos = float4(0,0,0,0);

	float _weight = input.Weight[0];
	float4x4 _bone = GetBoneMatrix(0, input.Bone);
	output.Pos += _weight * mul(myPos, _bone);

	_weight = input.Weight[1];
	_bone = GetBoneMatrix(1, input.Bone);
	output.Pos += _weight * mul(myPos, _bone);

	_weight = input.Weight[2];
	_bone = GetBoneMatrix(2, input.Bone);
	output.Pos += _weight * mul(myPos, _bone);

	_weight = input.Weight[3];
	_bone = GetBoneMatrix(3, input.Bone);
	output.Pos += _weight * mul(myPos, _bone);
	
	// transform the point into viewProjection space
	output.Pos = mul( output.Pos, mul(modelMatrix, viewProjection) );

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
	return float4(0.0f, 1.0f, 1.0f, 0.4f);
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
	BackFaceStencilPass = ZERO;
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

technique10 ForwardAnimation
{
    pass p0
    {
		SetBlendState( SrcAlphaBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader( CompileShader( vs_4_0, VSAnimScene() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, psFuckRoland() ) );

		SetDepthStencilState( stencilOpKeep, 1 );
	    SetRasterizerState( rs );
    }  
}