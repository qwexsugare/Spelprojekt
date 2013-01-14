Texture2D tex2D;
Texture2D terrainTextures[8];
Texture2D terrainBlendMaps[2];

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

	output.Pos = input.EyeCoord;
	output.Normal = float4(input.Normal, 1.0f);
	output.Diffuse = color;
	//output.Diffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);

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

PSSceneIn drawTerrainVs(VSSceneIn input)
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

PSSceneOut drawTerrainPs(PSSceneIn input) : SV_Target
{	
	PSSceneOut output = (PSSceneOut)0;

	output.Pos = input.Pos;
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
	
	float4 blendSample1 = terrainBlendMaps[0].Sample(linearSampler, input.UVCoord/32.0f); // 32.0f is the number of tiles for the terrain that you specified in the constructor
	float4 blendSample2 = terrainBlendMaps[1].Sample(linearSampler, input.UVCoord/32.0f); // 32.0f is the number of tiles for the terrain that you specified in the constructor
	
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
        SetVertexShader(CompileShader( vs_4_0, drawTerrainVs()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader( ps_4_0, drawTerrainPs()));

	    SetDepthStencilState(EnableDepth, 0);
	    SetRasterizerState(rs);
    }  
}