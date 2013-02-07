static const int MAX_LIGHTS = 8;

Texture2D positionTexture;
Texture2D normalTexture;
Texture2D diffuseTexture;
Texture2D shadowMaps[MAX_LIGHTS];

SamplerState linearSampler 
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

SamplerState pointSampler 
{
	Filter = MIN_MAG_MIP_POINT;
	AddressU = Wrap;
	AddressV = Wrap;
};

SamplerState shadowMapSampler 
{
	Filter = MIN_MAG_MIP_POINT;
	AddressU = Clamp;
	AddressV = Clamp;
};

struct VSSceneIn
{
	float3 Pos	: POS;
	float2 UVCoord : UVCOORD;
};

struct PSSceneIn
{
	float4 Pos  : SV_Position;
	float2 UVCoord : UVCOORD;
};

//Variables that updated often
cbuffer cbEveryFrame
{
	int nrOfPointLights;
	int nrOfDirectionalLights;
	int nrOfSpotLights;
	float3 lightPosition[100];
	float3 lightDirection[100];
	float3 la[150];
	float3 ld[150];
	float3 ls[150];
	float lightRadius[100];
	float2 lightAngle[50];
	matrix lightWvps[MAX_LIGHTS];

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

float calcShadow(float4 lightPos, int lightIndex)
{
	float shadowCoeff = 0.0f;
	float shadowEpsilon = 0.001f;

	// Project the texture_ coords and scale/offset to [0, 1].
	lightPos /= lightPos.w;
	
	// Check if the position is inside the lights unit cube.
	//if(lightPos.x > -1 && lightPos.y > -1 && lightPos.z > -1 && lightPos.x < 1 && lightPos.y < 1 && lightPos.z < 1 )//&& length(float2(lightPos.x, lightPos.y)) < 1)
	//{
		//Compute shadow map tex coord
		float2 smTex = float2(0.5f * lightPos.x, -0.5f * lightPos.y) + 0.5f;

		// Compute pixel depth for shadowing.
		float depth = lightPos.z;

		//Get the shadow map size
		int width;
		int height;
		shadowMaps[lightIndex].GetDimensions(width, height);

		// 2x2 percentage closest filter.
		float dx = 1.0f / width;
		float s0 = (shadowMaps[lightIndex].Sample(shadowMapSampler, smTex).r + shadowEpsilon < depth) ? 0.0f : 1.0f;
		float s1 = (shadowMaps[lightIndex].Sample(shadowMapSampler, smTex + float2(dx, 0.0f)).r + shadowEpsilon < depth) ? 0.0f : 1.0f;
		float s2 = (shadowMaps[lightIndex].Sample(shadowMapSampler, smTex + float2(0.0f, dx)).r + shadowEpsilon < depth) ? 0.0f : 1.0f;
		float s3 = (shadowMaps[lightIndex].Sample(shadowMapSampler, smTex + float2(dx, dx)).r + shadowEpsilon < depth) ? 0.0f : 1.0f;
		
		// Transform to texel space
		float2 texelPos = smTex * width;
		
		// Determine the lerp amounts.
		float2 lerps = frac( texelPos );
		shadowCoeff = lerp( lerp( s0, s1, lerps.x ), lerp( s2, s3, lerps.x ), lerps.y );
		shadowCoeff = s0;
	//}

	return shadowCoeff;
}

float4 PSScene(PSSceneIn input) : SV_Target
{	
	float4 position = positionTexture.Sample(linearSampler, input.UVCoord);
	float4 normal = normalTexture.Sample(linearSampler, input.UVCoord);
	float4 diffuse = diffuseTexture.Sample(linearSampler, input.UVCoord);
	
	float3 ambientLight = float3(0.0f, 0.0f, 0.0f);
	float3 diffuseLight = float3(0.0f, 0.0f, 0.0f);
	float3 specularLight = float3(0.0f, 0.0f, 0.0f);

	int i;
	float3 distVector;
	float distance;
	float cutoff = 0.005f;
	float attenuation;
	int nrOfPointAndDirectionalLights = nrOfPointLights + nrOfDirectionalLights;

	for(i = 0; i < nrOfPointLights; i++)
	{
		distVector = (lightPosition[i] - position);
		distance = length(distVector);
		attenuation = 1 / ((distance / lightRadius[i] + 1) * (distance / lightRadius[i] + 1));

		ambientLight = ambientLight + la[i];
		diffuseLight = diffuseLight + calcDiffuseLight(distVector, normal.xyz, ld[i]) * attenuation;
		specularLight = specularLight + calcSpecularLight(distVector, normal.xyz, ls[i]) * attenuation;
	}

	for(i = 0; i < nrOfDirectionalLights; i++)
	{
		ambientLight = ambientLight + la[nrOfPointLights + i];
		diffuseLight = diffuseLight + calcDiffuseLight(lightDirection[i], normal.xyz, ld[nrOfPointLights + i]);
		specularLight = specularLight + calcSpecularLight(lightDirection[i], normal.xyz, ls[nrOfPointLights + i]);
	}

	for(i = 0; i < nrOfSpotLights; i++)
	{
		distVector = (lightPosition[nrOfPointLights + i] - position.xyz);
		distance = length(distVector);
		attenuation = 1 / ((distance / lightRadius[nrOfPointLights + i] + 1) * (distance / lightRadius[nrOfPointLights + i] + 1));

		float3 s = normalize(distVector);
		float angle = max(acos(dot(s, normalize(lightDirection[nrOfDirectionalLights + i]))), 0.0f);
		float spotfactor = max(((cos(angle) - lightAngle[i].x) / (lightAngle[i].y - lightAngle[i].x)), 0.0f);

		ambientLight = ambientLight + la[nrOfPointAndDirectionalLights + i];
		diffuseLight = diffuseLight + (calcDiffuseLight(s, normal.xyz, ld[nrOfPointAndDirectionalLights + i]) * spotfactor * attenuation * calcShadow(mul(position, lightWvps[i]), i));
		specularLight = specularLight + (calcSpecularLight(s, normal.xyz, ls[nrOfPointAndDirectionalLights + i]) * spotfactor * attenuation * calcShadow(mul(position, lightWvps[i]), i));
	}
	
	/*float shad = nrOfSpotLights;
	for(i = 0; i < nrOfSpotLights; i++)
	{
		shad = max(shad-calcShadow(mul(position, lightWvps[i]), i), 0.0f);
	}*/

	/*float cowabunga = min(
		min(dot(normal, normalTexture.Sample(linearSampler, float2(input.UVCoord.x+1.0f/1920.0f, input.UVCoord.y+1.0f/1080.0f))), 
			dot(normal, normalTexture.Sample(linearSampler, float2(input.UVCoord.x-1.0f/1920.0f, input.UVCoord.y-1.0f/1080.0f)))),
		min(dot(normal, normalTexture.Sample(linearSampler, float2(input.UVCoord.x, input.UVCoord.y+1.0f/1080.0f))), 
			dot(normal, normalTexture.Sample(linearSampler, float2(input.UVCoord.x-1.0f/1920.0f, input.UVCoord.y)))));
	return (float4(ambientLight, 0.0f) + float4(diffuseLight, 1.0f)*diffuse + float4(specularLight, 0.0f))*cowabunga;*/
	
	return (float4(ambientLight, 0.0f)*diffuse + float4(diffuseLight, 1.0f)*diffuse + float4(specularLight, 0.0f)*diffuse);

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