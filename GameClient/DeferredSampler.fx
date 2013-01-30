Texture2D tex2D;
Texture1D boneTex;
Texture2D terrainTextures[8];
Texture2D terrainBlendMaps[2];

SamplerState linearSampler 
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VSSceneIn
{
	float3 Pos	: POS;
	float2 UVCoord : UVCOORD;
	float3 Normal : NORMAL;
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
	float3 EyeCoord : EYE_COORD;
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

BlendState SrcAlphaBlendRoad
{
   BlendEnable[2]           = TRUE;
   SrcBlend                 = SRC_ALPHA;
   DestBlend                = INV_SRC_ALPHA;
   BlendOp                  = ADD;
   SrcBlendAlpha            = ONE;
   DestBlendAlpha           = ONE;
   BlendOpAlpha             = ADD;
   RenderTargetWriteMask[2] = 0x0F;
};


PSSceneIn VSScene(VSSceneIn input)
{
	PSSceneIn output = (PSSceneIn)0;

	matrix worldViewProjection = mul(viewMatrix, projectionMatrix);
	
	// transform the point into view space
	output.Pos = mul( float4(input.Pos,1.0), mul(modelMatrix,worldViewProjection) );
	output.UVCoord = input.UVCoord;

	//variables needed for lighting
	output.Normal = normalize(mul(input.Normal, modelMatrix));
	output.EyeCoord = mul(float4(input.Pos,1.0), modelMatrix);

	return output;
}

PSSceneOut PSScene(PSSceneIn input)
{
	PSSceneOut output = (PSSceneOut)0;
	float4 color = tex2D.Sample(linearSampler, input.UVCoord);
	color.w = modelAlpha;

	output.Pos = float4(input.EyeCoord, 1.0f);
	//output.Pos = float4(1.0f, 1.0f, 1.0f, 1.0f);
	output.Normal = float4(normalize(input.Normal), 1.0f);
	output.Diffuse = color * float4(3,3, 3, 1.0f);

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

float4x4 GetBoneMatrix(int boneIndex, float4 _bone)
{
	float4x4 bone;
	for(int row = 0; row < 4; row++)
	{
		bone[row] = boneTex.Load(int2((_bone[boneIndex]) * 4 + row, 0), 0); // int2(x, mipMapLevel), int(offset)
	}
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
	
	//output.Pos.w = 1;
	//output.Pos.y += 15;
	
	// transform the point into viewProjection space
	output.Pos = mul( output.Pos, mul(modelMatrix, viewProjection) );
	output.UVCoord = input.UVCoord;
	
	//variables needed for lighting
	output.Normal = normalize(mul(input.Normal, modelMatrix));
	output.EyeCoord = mul(float4(input.Pos,1.0), modelMatrix);

	return output;

}

technique10 DeferredAnimationSample
{
    pass p0
    {
		SetBlendState( SrcAlphaBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader( CompileShader( vs_4_0, VSAnimScene() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSScene() ) );

	    SetDepthStencilState( EnableDepth, 0 );
	    SetRasterizerState( rs );
    }
}

PSSceneIn drawTerrainVs(VSSceneIn input)
{
	PSSceneIn output = (PSSceneIn)0;

	matrix worldViewProjection = mul(viewMatrix, projectionMatrix);
	
	// transform the point into view space
	output.Pos = mul( float4(input.Pos,1.0), mul(modelMatrix,worldViewProjection) );
	output.UVCoord = input.UVCoord;

	//variables needed for lighting
	output.Normal = normalize(mul(input.Normal, modelMatrix));
	output.EyeCoord = mul(input.Pos, modelMatrix);

	return output;
}

PSSceneOut drawTerrainPs(PSSceneIn input)
{	
	PSSceneOut output = (PSSceneOut)0;

	output.Pos = float4(input.EyeCoord, 1.0f);
	output.Normal = float4(input.Normal, 1.0f);

	float4 texColors[8];
	texColors[0] = terrainTextures[0].Sample(linearSampler, input.UVCoord);
	texColors[1] = terrainTextures[1].Sample(linearSampler, input.UVCoord);
	texColors[2] = terrainTextures[2].Sample(linearSampler, input.UVCoord);
	texColors[3] = terrainTextures[3].Sample(linearSampler, input.UVCoord);
	texColors[4] = terrainTextures[4].Sample(linearSampler, input.UVCoord);
	texColors[5] = terrainTextures[5].Sample(linearSampler, input.UVCoord);
	texColors[6] = terrainTextures[6].Sample(linearSampler, input.UVCoord);
	texColors[7] = terrainTextures[7].Sample(linearSampler, input.UVCoord);
	
	float4 blendSample1 = terrainBlendMaps[0].Sample(linearSampler, input.UVCoord/8.0f); // 32.0f is the number of tiles for the terrain that you specified in the constructor
	float4 blendSample2 = terrainBlendMaps[1].Sample(linearSampler, input.UVCoord/8.0f); // 32.0f is the number of tiles for the terrain that you specified in the constructor
	
	output.Diffuse =  texColors[0]* blendSample1.x;
	output.Diffuse += texColors[1]* blendSample1.y;
	output.Diffuse += texColors[2]* blendSample1.z;
	output.Diffuse += texColors[3]* blendSample1.w;
	output.Diffuse += texColors[4]* blendSample2.x;
	output.Diffuse += texColors[5]* blendSample2.y;
	output.Diffuse += texColors[6]* blendSample2.z;
	output.Diffuse += texColors[7]* blendSample2.w;

	return output;
}

technique10 RenderTerrain
{
    pass p0
    { 
		SetBlendState( SrcAlphaBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader(CompileShader( vs_4_0, drawTerrainVs()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader( ps_4_0, drawTerrainPs()));

	    SetDepthStencilState(EnableDepth, 0);
	    SetRasterizerState(rs);
    }
}

PSSceneIn drawRoadVs(VSSceneIn input)
{
	PSSceneIn output = (PSSceneIn)0;

	matrix worldViewProjection = mul(viewMatrix, projectionMatrix);
	
	// transform the point into view space
	output.Pos = mul( float4(input.Pos,1.0), mul(modelMatrix,worldViewProjection) );
	output.UVCoord = input.UVCoord;

	//variables needed for lighting
	output.Normal = normalize(mul(input.Normal, modelMatrix));
	output.EyeCoord = mul(float4(input.Pos, 1.0f), modelMatrix);

	return output;
}

PSSceneOut drawRoadPs(PSSceneIn input)
{	
	PSSceneOut output = (PSSceneOut)0;

	output.Pos = float4(input.EyeCoord, 1.0f);
	output.Normal = float4(normalize(input.Normal), 1.0f);
	output.Diffuse = tex2D.Sample(linearSampler, input.UVCoord);

	return output;
}

technique10 RenderRoad
{
    pass p0
    { 
		SetBlendState( SrcAlphaBlendRoad, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader(CompileShader( vs_4_0, drawRoadVs()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader( ps_4_0, drawRoadPs()));

	    SetDepthStencilState(DisableDepth, 0);
	    SetRasterizerState(rs);
    }  
}