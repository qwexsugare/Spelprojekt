static const int MAX_SPOT_LIGHTS = 10;
static const int MAX_POINT_LIGHT_SHADOWS = 100;

Texture2D positionTexture;
Texture2D normalTexture;
Texture2D diffuseTexture;
Texture2D viewCoordTexture;
Texture2D spotLightShadowMaps[MAX_SPOT_LIGHTS];
Texture2D pointLightShadowMaps[MAX_POINT_LIGHT_SHADOWS];
Texture2D randomTex;

float aoScale = 2;
float aoRadius = 0.03f;
float aoBias = 0;
float aoIntensity = 0.5;

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
	int nrOfShadowedPointLights;
	int nrOfDirectionalLights;
	int nrOfSpotLights;
	float3 lightPosition[150];
	float3 lightDirection[100];
	float3 la[200];
	float3 ld[200];
	float3 ls[200];
	float lightRadius[150];
	float2 lightAngle[50];
	matrix pointLightWvps[MAX_SPOT_LIGHTS];
	matrix spotLightWvps[MAX_POINT_LIGHT_SHADOWS];

	float3 cameraPos;
	float screenWidth = 1920;
	float screenHeight = 1080;
	float2 screenSize;
	matrix viewMatrix;
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
	//color = float3(0.0, 0.0f, 1.0f);
	//Variables
	float3 n = normal;
	float3 s = normalize(lightDir);

	//Diffuse light
	float3 diffuse = saturate(dot(s,n)) * color;

	return diffuse;
}

float3 calcSpecularLight(float3 lightDir, float3 normal, float3 color)
{
	//color = float3(0.0, 0.0f, 1.0f);
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

float calcShadow(float4 lightPos, Texture2D shadowmap, float radius)
{
	float shadowCoeff = 0.0f;
	float shadowEpsilon = 0.001f;

	// Project the texture_ coords and scale/offset to [0, 1].
	lightPos /= lightPos.w;
	
	//Check if the position is inside the lights unit cube.
	if(lightPos.x > -1 && lightPos.y > -1 && lightPos.z > -1 && lightPos.x < 1 && lightPos.y < 1 && lightPos.z < 1 && length(float2(lightPos.x, lightPos.y)) < radius)
	{
		//Compute shadow map tex coord
		float2 smTex = float2(0.5f * lightPos.x, -0.5f * lightPos.y) + 0.5f;

		// Compute pixel depth for shadowing.
		float depth = lightPos.z;

		//Get the shadow map size
		int width;
		int height;
		shadowmap.GetDimensions(width, height);

		// 2x2 percentage closest filter.
		float dx = 1.0f / width;
		float s0 = (shadowmap.Sample(shadowMapSampler, smTex).r + shadowEpsilon < depth) ? 0.0f : 1.0f;
		float s1 = (shadowmap.Sample(shadowMapSampler, smTex + float2(dx, 0.0f)).r + shadowEpsilon < depth) ? 0.0f : 1.0f;
		float s2 = (shadowmap.Sample(shadowMapSampler, smTex + float2(0.0f, dx)).r + shadowEpsilon < depth) ? 0.0f : 1.0f;
		float s3 = (shadowmap.Sample(shadowMapSampler, smTex + float2(dx, dx)).r + shadowEpsilon < depth) ? 0.0f : 1.0f;
		
		// Transform to texel space
		float2 texelPos = smTex * width;
		
		// Determine the lerp amounts.
		float2 lerps = frac( texelPos );
		shadowCoeff = lerp( lerp( s0, s1, lerps.x ), lerp( s2, s3, lerps.x ), lerps.y );
	}

	//return 1.0f;
	return shadowCoeff;
}

float doAmbientOcclusion(in float2 tcoord, in float2 uv, in float3 pos, in float3 vNormal)
{
	float3 diff = viewCoordTexture.Sample(linearSampler, tcoord + uv) - pos;
	const float3 v = normalize(diff);
	const float d = length(diff) * aoScale;
	return max(0.0f, dot(vNormal, v) * (1.0f/(1.0f + d))) * aoIntensity;
}

float ssao(float2 uv, float3 pos, float3 normal)
{
	float radius = aoRadius; 
	const float2 vec[4] = {float2(1,0), float2(-1,0), float2(0,1), float2(0,-1)};
	float2 rand = normalize(randomTex.Sample(linearSampler, screenSize * uv / (64 * 64)));
	float ao = 0;
	int iterations = 4;
	for(int j = 0; j < iterations; ++j)
	{
		float2 coord1 = reflect(vec[j], rand) * radius;
		float2 coord2 = float2(coord1.x * 0.707f - coord1.y * 0.707, coord1.x * 0.707 + coord1.y * 0.707);

		ao += doAmbientOcclusion(uv, coord1 * 0.25f, pos, normal);
		ao += doAmbientOcclusion(uv, coord2 * 0.5f, pos, normal);
		ao += doAmbientOcclusion(uv, coord1 * 0.75f, pos, normal);
		ao += doAmbientOcclusion(uv, coord2, pos, normal);
	}

	return ao /= (float)iterations * 4;
}

float4 PSScene(PSSceneIn input) : SV_Target
{	
	float4 position = positionTexture.Sample(linearSampler, input.UVCoord);
	float4 normal = normalTexture.Sample(linearSampler, input.UVCoord);
	float4 diffuse = diffuseTexture.Sample(linearSampler, input.UVCoord);
	float4 viewCoord = viewCoordTexture.Sample(linearSampler, input.UVCoord);
	
	float3 ambientLight = float3(0.0f, 0.0f, 0.0f);
	float3 diffuseLight = float3(0.0f, 0.0f, 0.0f);
	float3 specularLight = float3(0.0f, 0.0f, 0.0f);

	int i;
	//float3 distVector;
	//float distance;
	float cutoff = 0.005f;
	//float attenuation;
	int nrOfPointAndDirectionalLights = nrOfPointLights + nrOfShadowedPointLights + nrOfDirectionalLights;

	for(i = 0; i < nrOfPointLights; i++)
	{
		float3 distVector = (lightPosition[nrOfShadowedPointLights + i] - position);
		float distance = length(distVector);
		float attenuation = 1 / ((distance / lightRadius[nrOfShadowedPointLights + i] + 1) * (distance / lightRadius[nrOfShadowedPointLights + i] + 1));

		ambientLight = ambientLight + la[nrOfShadowedPointLights + i];
		diffuseLight = diffuseLight + calcDiffuseLight(distVector, normal.xyz, ld[nrOfShadowedPointLights + i]) * attenuation;
		specularLight = specularLight + calcSpecularLight(distVector, normal.xyz, ls[nrOfShadowedPointLights + i]) * attenuation;
	}

	for(i = 0; i < nrOfShadowedPointLights; i++)
	{
		float3 distVector = (lightPosition[i] - position);
		float distance = length(distVector);
		float attenuation = 1 / ((distance / lightRadius[i] + 1) * (distance / lightRadius[i] + 1));

		float shadowCoeff = calcShadow(mul(position, pointLightWvps[i * 6]), pointLightShadowMaps[i * 6], lightRadius[i]);
		shadowCoeff += calcShadow(mul(position, pointLightWvps[i * 6 + 1]), pointLightShadowMaps[i * 6 + 1], lightRadius[i]);
		shadowCoeff += calcShadow(mul(position, pointLightWvps[i * 6 + 2]), pointLightShadowMaps[i * 6 + 2], lightRadius[i]);
		shadowCoeff += calcShadow(mul(position, pointLightWvps[i * 6 + 3]), pointLightShadowMaps[i * 6 + 3], lightRadius[i]);
		shadowCoeff += calcShadow(mul(position, pointLightWvps[i * 6 + 4]), pointLightShadowMaps[i * 6 + 4], lightRadius[i]);
		shadowCoeff += calcShadow(mul(position, pointLightWvps[i * 6 + 5]), pointLightShadowMaps[i * 6 + 5], lightRadius[i]);

		ambientLight = ambientLight + la[i];
		diffuseLight = diffuseLight + calcDiffuseLight(distVector, normal.xyz, ld[i]) * attenuation * shadowCoeff;
		specularLight = specularLight + calcSpecularLight(distVector, normal.xyz, ls[i]) * attenuation * shadowCoeff;
	}

	for(i = 0; i < nrOfDirectionalLights; i++)
	{
		ambientLight = ambientLight + la[nrOfPointLights + nrOfShadowedPointLights + i];
		diffuseLight = diffuseLight + calcDiffuseLight(lightDirection[i], normal.xyz, ld[nrOfPointLights + nrOfShadowedPointLights + i]);
		specularLight = specularLight + calcSpecularLight(lightDirection[i], normal.xyz, ls[nrOfPointLights + nrOfShadowedPointLights + i]);
	}

	for(i = 0; i < nrOfSpotLights; i++)
	{
		float3 distVector = (lightPosition[nrOfPointLights + nrOfShadowedPointLights + i] - position.xyz);
		float distance = length(distVector);
		float attenuation = 1 / ((distance / lightRadius[nrOfPointLights + nrOfShadowedPointLights + i] + 1) * (distance / lightRadius[nrOfPointLights + nrOfShadowedPointLights + i] + 1));

		float3 s = normalize(distVector);
		float angle = max(acos(dot(s, normalize(lightDirection[nrOfDirectionalLights + i]))), 0.0f);
		float spotfactor = max(((cos(angle) - lightAngle[i].x) / (lightAngle[i].y - lightAngle[i].x)), 0.0f);
		float shadowCoeff = calcShadow(mul(position, spotLightWvps[i]), spotLightShadowMaps[i], lightRadius[nrOfPointLights + nrOfShadowedPointLights + i]);

		ambientLight = ambientLight + la[nrOfPointAndDirectionalLights + i];
		diffuseLight = diffuseLight + (calcDiffuseLight(s, normal.xyz, ld[nrOfPointAndDirectionalLights + i]) * spotfactor * attenuation * shadowCoeff);
		specularLight = specularLight + (calcSpecularLight(s, normal.xyz, ls[nrOfPointAndDirectionalLights + i]) * spotfactor * attenuation * shadowCoeff);
	}

	/*float cowabunga = min(
		min(dot(normal, normalTexture.Sample(linearSampler, float2(input.UVCoord.x+1.0f/1920.0f, input.UVCoord.y+1.0f/1080.0f))), 
			dot(normal, normalTexture.Sample(linearSampler, float2(input.UVCoord.x-1.0f/1920.0f, input.UVCoord.y-1.0f/1080.0f)))),
		min(dot(normal, normalTexture.Sample(linearSampler, float2(input.UVCoord.x, input.UVCoord.y+1.0f/1080.0f))), 
			dot(normal, normalTexture.Sample(linearSampler, float2(input.UVCoord.x-1.0f/1920.0f, input.UVCoord.y)))));
	return (float4(ambientLight, 0.0f)*diffuse + float4(diffuseLight, 1.0f)*diffuse + float4(specularLight, 0.0f))*cowabunga;*/
	
	//return float4(0.5f*diffuseLight.xyz*diffuse + specularLight, diffuse.w);

	//SSAO stuff


	float ao = 0.0f;
	ao = ssao( input.UVCoord, viewCoord, normal);

	//return float4(0, 0, , diffuse.w);

	return ((float4(ambientLight - ao, 0.0f) * diffuse + float4(diffuseLight - ao, 1.0f) * diffuse + float4(specularLight, 0.0f) * viewCoord.w));

	
	float3 fiskLight = normalize(float3(1, -1, 0));
	float fiskDiff = dot(normal.xyz, -fiskLight);

	diffuse *= fiskDiff;
	float trollx = saturate(normal.x);
	float trolly = saturate(normal.y);
	float trollz = saturate(normal.z);

	//had to do this to commiut

	//return float4(trollx, trolly, trollz, normal.w);
	//return float4(fiskDiff, fiskDiff, fiskDiff, diffuse.w);
	return float4(diffuse.xyz, diffuse.w);
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