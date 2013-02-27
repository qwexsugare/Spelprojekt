Texture2D tex2D;
Texture2D normalMap;
Texture2D glowMap;
Texture2D specularMap;
Texture1D boneTex;
Texture2D terrainTextures[8];
Texture2D terrainNormalMaps[8];
Texture2D terrainSpecularMaps[8];
Texture2D terrainBlendMaps[2];

SamplerState linearSampler 
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

SamplerState pointSampler 
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

struct VSSuperSceneIn
{
	float3 Pos	: POS;
	float2 UVCoord : UVCOORD;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
};

struct PSSuperSceneIn
{
	float4 Pos  : SV_Position;
	float2 UVCoord : UVCOORD;
	float4 EyeCoord : EYE_COORD;
	float4 Normal : NORMAL;
	float3 Tangent : TANGENT;
};

struct VSAnimSceneIn
{
	float3 Pos		: POS;
	float2 UVCoord	: UVCOORD;
	float3 Normal	: NORMAL;
	float3 Tangent	: TANGENT;
	float4 Weight	: WEIGHT;
	float4 Bone		: BONE;
};

struct PSSceneIn
{
	float4 Pos  : SV_Position;
	float2 UVCoord : UVCOORD;
	float4 EyeCoord : EYE_COORD;
	float3 Normal : NORMAL;
};

struct PSSceneOut
{
	float4 Pos : SV_TARGET0;
	float4 Normal : SV_TARGET1;
	float4 Diffuse : SV_TARGET2;
	float4 Tangent : SV_TARGET3;
	float4 Glow : SV_TARGET4;
};

//Variables that updated often
cbuffer cbEveryFrame
{
	//Transformation matrices
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix modelMatrix;
	//Props Transformation Matrix
	matrix propsMatrix;

	float3 cameraPos;

	matrix lightWvp;

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
	//DepthFunc = GREATER;
};

DepthStencilState EnableDepthNoWrite
{
    DepthEnable = TRUE;
    DepthWriteMask = ZERO;
	DepthFunc = LESS_EQUAL;
};

DepthStencilState EnableDepthSM
{
	DepthEnable = TRUE;
	DepthWriteMask = ALL;
	DepthFunc = LESS_EQUAL;
};

DepthStencilState houseStencil
{
	DepthEnable = TRUE;
	StencilEnable = TRUE;
	
	//StencilWriteMask = 1;

	FrontFaceStencilFunc = ALWAYS;
	FrontFaceStencilPass = REPLACE;

	BackFaceStencilFunc = ALWAYS;
	BackFaceStencilPass = REPLACE;
};

DepthStencilState disableStencil
{
	StencilEnable=FALSE;
};

DepthStencilState gubbStencil
{
	StencilEnable = TRUE;
	DepthEnable = TRUE;
	//FrontFaceStencilFunc = EQUAL;

	BackFaceStencilFunc = ALWAYS;
	BackFaceStencilPass = ZERO;

	//DepthEnable = TRUE;
	//DepthWriteMask = ALL;
	//DepthFunc = LESS_EQUAL;
};

RasterizerState testRS
{
	FillMode = Solid;
	CullMode = BACK;
};

RasterizerState rs
{
	FillMode = Solid;
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
	color.w *= modelAlpha;

	output.Pos = input.EyeCoord;
	//output.Pos = float4(1.0f, 1.0f, 1.0f, 1.0f);
	output.Normal = float4(normalize(input.Normal), 1.0f);
	output.Diffuse = color;
	output.Tangent = float4(1, 0, 0, 0);
	output.Glow = float4(1, 1, 1, 1);
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

PSSuperSceneIn VSSuperScene(VSSuperSceneIn input)
{
	PSSuperSceneIn output = (PSSuperSceneIn)0;

	matrix worldViewProjection = mul(viewMatrix, projectionMatrix);
	
	// transform the point into view space
	output.Pos = mul( float4(input.Pos,1.0), mul(modelMatrix,worldViewProjection) );
	output.UVCoord = input.UVCoord;

	//variables needed for lighting
	float3 myNormal = input.Normal;

	output.Normal = normalize(mul(float4(myNormal, 0.0f), modelMatrix));
	output.EyeCoord = mul(float4(input.Pos,1.0), modelMatrix);

	return output;
}

PSSuperSceneIn VSPropsScene(VSSuperSceneIn input)
{
	PSSuperSceneIn output = (PSSuperSceneIn)0;
	//Lägg på CPU, optimera?
	matrix viewProjection = mul(viewMatrix, projectionMatrix);
	matrix newModelMatrix = mul(propsMatrix, modelMatrix);
	//matrix newModelMatrix = modelMatrix;

	// transform the point into view space
	output.Pos = mul( float4(input.Pos,1.0), mul(newModelMatrix, viewProjection) );
	output.UVCoord = input.UVCoord;

	//variables needed for lighting
	float3 myNormal = input.Normal;

	output.Normal = normalize(mul(float4(myNormal, 0.0f), newModelMatrix));
	//output.Tangent = normalize(mul(float4(myTangent, 0.0f), newModelMatrix));
	output.EyeCoord = mul(float4(input.Pos,1.0), newModelMatrix);

	return output;
}

float3x3 invert_3x3( float3x3 M )
{
	float D = determinant( M );		
	float3x3 T = transpose( M );	

	return float3x3(
		cross( T[1], T[2] ),
		cross( T[2], T[0] ),
		cross( T[0], T[1] ) ) / D;	
}

float3x3 compute_tangent_frame( float3 N, float3 p, float2 uv )
{
	// Implemenataion with full matrix inverse
	// straight from theory.

    // get edge vectors of the pixel triangle
    float3 dp1 = ddx( p );
    float3 dp2 = ddy( p );
    float2 duv1 = ddx( uv );
    float2 duv2 = ddy( uv );

    // solve the linear system
    float3x3 M = float3x3( dp1, dp2, cross( dp1, dp2 ) );
    float3x3 inverseM = invert_3x3( M );
    float3 T = mul( inverseM, float3( duv1.x, duv2.x, 0 ) );
    float3 B = mul( inverseM, float3( duv1.y, duv2.y, 0 ) );

    // construct tangent frame 
    float maxLength = max( length(T), length(B) );
    return float3x3( T / maxLength, B / maxLength, N );
}

PSSceneOut PSSuperScene(PSSuperSceneIn input)
{	
	PSSceneOut output = (PSSceneOut)0;
	float4 color = tex2D.Sample(linearSampler, input.UVCoord);
	float4 specularColor = specularMap.Sample(linearSampler, input.UVCoord);
	color.w *= modelAlpha;

	float3 sampNormal = (normalMap.Sample(linearSampler, input.UVCoord));

	sampNormal = (2.0f * sampNormal) - 1.0f;

	float3 n = normalize(input.Normal.xyz);

	float3 v = cameraPos - input.EyeCoord;

	float3x3 tbn = compute_tangent_frame(n, -v, input.UVCoord);

	float3 nNormal = normalize(mul(sampNormal, tbn));

	output.Pos = input.EyeCoord;
	output.Normal = float4(nNormal, 1);
	output.Diffuse = color;
	output.Tangent = float4(0.0f, 0.0f, 0.0f, specularMap.Sample(linearSampler, input.UVCoord).r);
	output.Glow = glowMap.Sample(linearSampler, input.UVCoord);

	return output;
}

technique10 DeferredSuperSample
{
	pass p0
	{
		SetBlendState( SrcAlphaBlendRoad, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader( CompileShader( vs_4_0, VSSuperScene() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSSuperScene() ) );
		
	    SetDepthStencilState( gubbStencil, 0 );
	    SetRasterizerState( rs );
	}
    pass p1
    {
		SetBlendState( SrcAlphaBlendRoad, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader( CompileShader( vs_4_0, VSSuperScene() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSSuperScene() ) );
		
	    SetDepthStencilState( houseStencil, 1 );
	    SetRasterizerState( rs );
    }
}

technique10 DeferredPropsSample
{
	pass p0
	{
		SetBlendState( SrcAlphaBlendRoad, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader( CompileShader( vs_4_0, VSPropsScene() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSSuperScene() ) );
		
	    SetDepthStencilState( gubbStencil, 0 );
	    SetRasterizerState( rs );
	}
	pass p1
	{
		SetBlendState( SrcAlphaBlendRoad, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader( CompileShader( vs_4_0, VSPropsScene() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSSuperScene() ) );
		
	    SetDepthStencilState( houseStencil, 0 );
	    SetRasterizerState( rs );
	}
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

PSSuperSceneIn VSAnimScene(VSAnimSceneIn input)
{
	PSSuperSceneIn output = (PSSuperSceneIn)0;

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

	//Normal
	float4 myNorm = float4(input.Normal, 0.0);
	output.Normal = float4(0,0,0,0);

	float _nweight = input.Weight[0];
	output.Normal += _nweight * mul(myNorm, _bone);

	_nweight = input.Weight[1];
	_bone = GetBoneMatrix(1, input.Bone);
	output.Normal += _nweight * mul(myNorm, _bone);

	_nweight = input.Weight[2];
	_bone = GetBoneMatrix(2, input.Bone);
	output.Normal += _nweight * mul(myNorm, _bone);

	_nweight = input.Weight[3];
	_bone = GetBoneMatrix(3, input.Bone);
	output.Normal += _nweight * mul(myNorm, _bone);
	//Normal End
	
	// transform the point into viewProjection space
	output.Pos = mul( output.Pos, mul(modelMatrix, viewProjection) );
	output.UVCoord = input.UVCoord;
	
	//variables needed for lighting
	output.Normal = normalize(mul(output.Normal, modelMatrix));
	output.EyeCoord = mul(float4(output.Pos.xyz,1.0), modelMatrix);
	output.Tangent = float4(0.0f, 0.0f, 0.0f, specularMap.Sample(linearSampler, input.UVCoord).r);
	//output.Tangent = float4(t, 0);

	return output;
}

technique10 DeferredAnimationSample
{
    pass p0
    {
		SetBlendState( SrcAlphaBlendRoad, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader( CompileShader( vs_4_0, VSAnimScene() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSSuperScene() ) );
		
	    SetDepthStencilState( gubbStencil, 0 );
	    SetRasterizerState( rs );
    }
    pass p1
    {
		SetBlendState( SrcAlphaBlendRoad, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader( CompileShader( vs_4_0, VSAnimScene() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSSuperScene() ) );
		
	    SetDepthStencilState( houseStencil, 0 );
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
	float4 norm = normalize(mul(input.Normal, modelMatrix));
	output.Normal = normalize(mul(input.Normal, modelMatrix));
	output.EyeCoord = mul(float4(input.Pos, 1.0f), modelMatrix);

	return output;
}

PSSceneOut drawTerrainPs(PSSceneIn input)
{	
	PSSceneOut output = (PSSceneOut)0;

	output.Pos = input.EyeCoord;
	output.Tangent = float4(0.0f, 0.0f, 0.0f, 1.0f);
	//output.Normal = float4(input.Normal, 1.0f);
	//output.Normal = normalize(mul(normalMap.Sample(pointSampler, input.UVCoord), modelMatrix));

	float4 texColors[8];
	texColors[0] = terrainTextures[0].Sample(linearSampler, input.UVCoord);
	texColors[1] = terrainTextures[1].Sample(linearSampler, input.UVCoord);
	texColors[2] = terrainTextures[2].Sample(linearSampler, input.UVCoord);
	texColors[3] = terrainTextures[3].Sample(linearSampler, input.UVCoord);
	texColors[4] = terrainTextures[4].Sample(linearSampler, input.UVCoord);
	texColors[5] = terrainTextures[5].Sample(linearSampler, input.UVCoord);
	texColors[6] = terrainTextures[6].Sample(linearSampler, input.UVCoord);
	texColors[7] = terrainTextures[7].Sample(linearSampler, input.UVCoord);

	float4 normals[8];
	normals[0] = terrainNormalMaps[0].Sample(linearSampler, input.UVCoord);
	normals[1] = terrainNormalMaps[1].Sample(linearSampler, input.UVCoord);
	normals[2] = terrainNormalMaps[2].Sample(linearSampler, input.UVCoord);
	normals[3] = terrainNormalMaps[3].Sample(linearSampler, input.UVCoord);
	normals[4] = terrainNormalMaps[4].Sample(linearSampler, input.UVCoord);
	normals[5] = terrainNormalMaps[5].Sample(linearSampler, input.UVCoord);
	normals[6] = terrainNormalMaps[6].Sample(linearSampler, input.UVCoord);
	normals[7] = terrainNormalMaps[7].Sample(linearSampler, input.UVCoord);

	float4 specular[8];
	specular[0] = terrainSpecularMaps[0].Sample(linearSampler, input.UVCoord);
	specular[1] = terrainSpecularMaps[1].Sample(linearSampler, input.UVCoord);
	specular[2] = terrainSpecularMaps[2].Sample(linearSampler, input.UVCoord);
	specular[3] = terrainSpecularMaps[3].Sample(linearSampler, input.UVCoord);
	specular[4] = terrainSpecularMaps[4].Sample(linearSampler, input.UVCoord);
	specular[5] = terrainSpecularMaps[5].Sample(linearSampler, input.UVCoord);
	specular[6] = terrainSpecularMaps[6].Sample(linearSampler, input.UVCoord);
	specular[7] = terrainSpecularMaps[7].Sample(linearSampler, input.UVCoord);
	
	float2 newUvCoord = float2(input.UVCoord.x/8.0f, 8.0f-input.UVCoord.y/8.0f);
	float4 blendSample1 = terrainBlendMaps[0].Sample(linearSampler, newUvCoord); // /x is the number of tiles for the terrain that you specified in the constructor
	float4 blendSample2 = terrainBlendMaps[1].Sample(linearSampler, newUvCoord); // /x is the number of tiles for the terrain that you specified in the constructor
	
	output.Diffuse =  texColors[0]* blendSample1.x;
	output.Diffuse += texColors[1]* blendSample1.y;
	output.Diffuse += texColors[2]* blendSample1.z;
	output.Diffuse += texColors[3]* blendSample1.w;
	output.Diffuse += texColors[4]* blendSample2.x;
	output.Diffuse += texColors[5]* blendSample2.y;
	output.Diffuse += texColors[6]* blendSample2.z;
	output.Diffuse += texColors[7]* blendSample2.w;

	output.Normal.xyz =  normals[0] * blendSample1.x;
	output.Normal.xyz += normals[1] * blendSample1.y;
	output.Normal.xyz += normals[2] * blendSample1.z;
	output.Normal.xyz += normals[3] * blendSample1.w;
	output.Normal.xyz += normals[4] * blendSample2.x;
	output.Normal.xyz += normals[5] * blendSample2.y;
	output.Normal.xyz += normals[6] * blendSample2.z;
	output.Normal.xyz += normals[7] * blendSample2.w;

	output.Normal = normalize(mul(output.Normal, modelMatrix));

	output.Tangent.w =  specular[0].w * blendSample1.x;
	output.Tangent.w += specular[1].w * blendSample1.y;
	output.Tangent.w += specular[2].w * blendSample1.z;
	output.Tangent.w += specular[3].w * blendSample1.w;
	output.Tangent.w += specular[4].w * blendSample2.x;
	output.Tangent.w += specular[5].w * blendSample2.y;
	output.Tangent.w += specular[6].w * blendSample2.z;
	output.Tangent.w += specular[7].w * blendSample2.w;


	output.Normal.w = terrainNormalMaps[0].Sample(linearSampler, input.UVCoord).w;

	output.Normal = (2.0f * output.Normal) - 1.0f;

	float3 n = float3(0, 1, 0);

	float3 v = cameraPos - input.EyeCoord;

	float3x3 tbn = compute_tangent_frame(n, -v, input.UVCoord);

	float3 nNormal = normalize(mul(output.Normal, tbn));
	output.Normal.xyz = nNormal;

	//output.Normal.z *= -1;


	//output.Diffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);
	//output.Tangent = float4(1, 0, 0, 0);

	return output;
}

technique10 RenderTerrain
{
    pass p0
    {
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

	output.Pos = input.EyeCoord;
	output.Normal = float4(normalize(input.Normal), 1.0f);
	output.Diffuse = tex2D.Sample(linearSampler, input.UVCoord);
	output.Tangent = float4(0.0f, 0.0f, 0.0f, 1.0f);

	//output.Glow = float4(0, 1, 0, 1);

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

	    SetDepthStencilState(EnableDepthNoWrite, 0);
	    SetRasterizerState(rs);
    }
}

float4 vsShadowMap(float3 _pos : POS) : SV_POSITION
{
	// Render from light's perspective.
	return mul(float4(_pos, 1.0f), mul(modelMatrix, lightWvp));
}

technique10 RenderShadowMap
{
	pass p0
	{
		SetVertexShader(CompileShader(vs_4_0, vsShadowMap()));
		SetGeometryShader(NULL);
		SetPixelShader(NULL);

		SetDepthStencilState(EnableDepthSM, 0);
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
		SetRasterizerState(testRS);
	}
}