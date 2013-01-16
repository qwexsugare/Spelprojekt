Texture2D positionTexture;
Texture2D normalTexture;
Texture2D diffuseTexture;

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
};

struct PSSceneIn
{
	float4 Pos  : SV_Position;		// SV_Position is a (S)ystem (V)ariable that denotes transformed position
	float2 UVCoord : UVCOORD;
};

//Variables that updated often
cbuffer cbEveryFrame
{
	//Transformation matrices
	//matrix viewMatrix;
	//matrix projectionMatrix;
	//matrix modelMatrix;
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
	FillMode = Solid;
	CullMode = BACK;
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



//-----------------------------------------------------------------------------------------
// Calculate the light intensity for a given point
//-----------------------------------------------------------------------------------------
float3 calcLight(float3 eyeCoord, float3 normal)
{
	//Variables
	float3 lightPos = float3(50.0f, 2.0f, 50.0f); //temp
	float3 la = float3(0.1f, 0.1f, 0.1f);
	float3 ka = float3(1.0f, 1.0f, 1.0f);
	float3 ld = float3(1.0f, 1.0f, 1.0f);
	float3 kd = float3(1.0f, 1.0f, 1.0f);
	float3 ls = float3(0.1f, 0.1f, 0.1f);
	float3 ks = float3(1.0f, 1.0f, 1.0f);
	float f = 1.0f;

	float3 n = normal;
	float3 s = normalize(lightPos - eyeCoord);
	float3 r = -1 * s + 2 * dot(s,n) * n;
	float3 v = -eyeCoord;

	//Ambient light
	float3 ambient = la * ka;

	//Diffuse light
	float3 diffuse = saturate(dot(s,n)) * ld * kd;

	//Specular light
	float3 specular = ls * ks * pow(max(dot(r,v), 0), f);
	
	return (/*ambient +*/ diffuse /* + specular*/);

	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}

PSSceneIn VSScene(VSSceneIn input)
{
	PSSceneIn output = (PSSceneIn)0;

	// transform the point into view space
	output.Pos = float4(input.Pos,1.0);
	output.UVCoord = input.UVCoord;

	return output;
}

float4 PSScene(PSSceneIn input) : SV_Target
{	
	float4 position = positionTexture.Sample(linearSampler, input.UVCoord);
	float4 normal = normalTexture.Sample(linearSampler, input.UVCoord);
	float4 diffuse = diffuseTexture.Sample(linearSampler, input.UVCoord);


	//return float4(normalize(normal).xyz, 1.0f);
	//float3 lightDir = float3(1.0f, 1.0f, 0.0f);
	//return saturate(dot(normal.xyz, normalize(lightDir))) * diffuse;

	float3 lightPos = float3(50.0f, 2.0f, 50.0f);
	return saturate(dot(normal.xyz, normalize(lightPos - position.xyz))) * diffuse;

	//return position/2 + float4(0.5f, 0.5f, 0.5f, 0.0f);;

	//return float4(calcLight(position.xyz, normal.xyz), 1.0f) * diffuse;
	//return float4(0.0f, 0.0f, 0.0f, 0.5f);
}

technique10 RenderModelDeferred
{
    pass p0
    {
		SetBlendState( SrcAlphaBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader( CompileShader( vs_4_0, VSScene() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSScene() ) );

	    SetDepthStencilState( DisableDepth, 0 );
	    SetRasterizerState( rs );
    }  
}