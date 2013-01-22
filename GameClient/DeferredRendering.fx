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

	int nrOfPointLights;
	int nrOfDirectionalLights;
	float3 lightPosition[50];
	float3 lightDirection[50];
	float3 la[100];
	float3 ld[100];
	float3 ls[100];
	float lightRadius[50];

	float3 cameraPos;
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
float3 calcAmbientLight()
{
	float3 la = float3(0.1f, 0.1f, 0.1f);
	float3 ka = float3(1.0f, 1.0f, 1.0f);

	//Ambient light
	float3 ambient = la * ka;

	return ambient;
}

float3 calcDiffuseLight(float3 lightDir, float3 normal, float3 color)
{
	//Variables
	float3 n = normal;
	float3 s = normalize(lightDir);

	//Diffuse light
	float3 diffuse = saturate(dot(s,n)) * color;

	return diffuse;
}

float3 calcSpecularLight(float3 lightDir, float3 normal, float3 color)
{
	float3 ks = float3(1.0f, 1.0f, 1.0f);
	float f = 30.0f;

	lightDir = -normalize(lightDir);
	float3 reflection = reflect(lightDir, normal);

	//Specular light
	float3 specular = color * pow(saturate(dot(normal,(-lightDir + cameraPos))), f);

	return specular;
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

	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float3 diffuseLight = float3(0.0f, 0.0f, 0.0f);
	float3 specularLight = float3(0.0f, 0.0f, 0.0f);

	int i;

	for(i = 0; i < nrOfPointLights; i++)
	{
		float3 distVector = (lightPosition[i] - position.xyz);
		float distance = length(distVector);
		float cutoff = 0.005f;

		float attenuation = 1 / ((distance / lightRadius[i] + 1) * (distance / lightRadius[i] + 1));

		if(attenuation > 0.005f)
		{
			diffuseLight = diffuseLight + calcDiffuseLight(distVector, normal.xyz, ld[i]) * attenuation;
			specularLight = specularLight + calcSpecularLight(distVector, normal.xyz, ls[i]) * attenuation;
		}
	}

	for(i = 0; i < nrOfDirectionalLights; i++)
	{
		diffuseLight = diffuseLight + calcDiffuseLight(lightDirection[i], normal.xyz, ld[nrOfPointLights + i]);
		specularLight = specularLight + calcSpecularLight(lightDirection[i], normal.xyz, ls[nrOfPointLights + i]);
	}

	//float3 pos = float3(50.0f, 5.0f, 50.0f);
	//float s = normalize((pos - position.xyz));
	//float3 dir = normalize(float3(1.0f, 1.0f, 0.0f));

	//float angle = max(acos(dot(s, dir)), 0.0f);

	//float max = 0.22f;
	//float min = 0.02f;

	//float spotfactor = smoothstep(min,max,angle);

	//diffuseLight = diffuseLight + calcDiffuseLight(s, normal.xyz, float3(1.0f, 1.0f, 1.0f)) * spotfactor;
	//specularLight = specularLight + calcSpecularLight(s, normal.xyz, float3(1.0f, 1.0f, 1.0f)) * spotfactor;

	color = float4(diffuseLight, 1.0f) * diffuse + float4(specularLight, 0.0f);

	//return float4(normalize(normal).xyz, 1.0f);
	//float3 lightDir = float3(1.0f, 1.0f, 0.0f);
	//return saturate(dot(normal.xyz, normalize(lightDir))) * diffuse;

	//float3 lightPos = float3(50.0f, 3.0f, 50.0f);
	//return saturate(dot(normal.xyz, normalize(lightPos - position.xyz))) * diffuse;

	//return position/2 + float4(0.5f, 0.5f, 0.5f, 0.0f);;

	return color;
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