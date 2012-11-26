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

//Variables that updated often
cbuffer cbEveryFrame
{
	//Transformation matrices
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix modelMatrix;
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
	CullMode = Front;
};

BlendState NoBlend
{
	BlendEnable[0] = FALSE;
};



//-----------------------------------------------------------------------------------------
// Calculate the light intensity for a given point
//-----------------------------------------------------------------------------------------
//float3 calcLight(float3 eyeCoord, float3 normal)
//{
//	//Variables
//	float3 n = normalize(mul(normal, mul(modelMatrix,viewMatrix)));
//	float3 s = normalize(lightPos - eyeCoord);
//	float3 r = -1 * s + 2 * dot(s,n) * n;
//	float3 v = -eyeCoord;
//
//	//Ambient light
//	float3 ambient = la * ka;
//
//	//Diffuse light
//	float3 diffuse = max(dot(s,n), 0) * ld * kd;
//
//	//Specular light
//	float3 specular = ls * ks * pow(max(dot(r,v), 0), f);
//
//	return (ambient + diffuse + specular);
//}

PSSceneIn VSScene(VSSceneIn input)
{
	PSSceneIn output = (PSSceneIn)0;

	matrix worldViewProjection = mul(mul(modelMatrix, viewMatrix), projectionMatrix);
	
	// transform the point into view space
	output.Pos = mul( float4(input.Pos,1.0), mul(modelMatrix,worldViewProjection) );
	output.UVCoord = input.UVCoord;

	//variables needed for lighting
	output.Normal = input.Normal;
	output.EyeCoord = mul( float4(input.Pos,1.0), mul(modelMatrix,viewMatrix) );

	return output;
}

float4 PSScene(PSSceneIn input) : SV_Target
{	
	//float3 texColor = tex2D.Sample(linearSampler, input.UVCoord);
	//float3 li = calcLight(input.EyeCoord, input.Normal);

	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}

technique10 RenderModelForward
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_4_0, VSScene() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSScene() ) );

	    SetDepthStencilState( EnableDepth, 0 );
	    SetRasterizerState( rs );
    }  
}