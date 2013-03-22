#ifndef PARTICLERENDERER
#define PARTICLERENDERER

#include "ParticleSystemStructs.fx"
#include "UpSideDownTwist.fx"
#include "Beacon.fx"
#include "CirclePuls.fx"
#include "Sphere.fx"
#include "Fire.fx"
#include "Electric.fx"
#include "Aura.fx"

Particle StreamOutVS(Particle input)
{
	return input;
}

[maxvertexcount(4)]
void DrawGS(point VS_OUT input[1], inout TriangleStream<GS_OUT> triStream)
{
	if(input[0].type =! EMITTER)
	{
		float3 normVel = normalize(input[0].vel);
		float3 look = normalize(camPosW.xyz - input[0].pos);
		float3 right = normalize(cross(normVel, look));
		float3 up = cross(look, right);

		float4x4 W;
		W[0] = float4(right,		0.0f);
		W[1] = float4(up,			0.0f);
		W[2] = float4(look,			0.0f);
		W[3] = float4(input[0].pos,	1.0f);
		
		float4x4 WVP = mul(W, viewProj);


		// Creating Quad
		float halfWidth = 0.5f*input[0].size.x;
		float halfHeight = 0.5f*input[0].size.y;


		float4 v[4];
		v[0] = float4(-halfWidth, -halfHeight, 0.0f, 1.0f);
		v[1] = float4(+halfWidth, -halfHeight, 0.0f, 1.0f);
		v[2] = float4(-halfWidth, +halfHeight, 0.0f, 1.0f);
		v[3] = float4(+halfWidth, +halfHeight, 0.0f, 1.0f);

		GS_OUT output;
		[unroll]
		for(int i = 0; i < 4; ++i)
		{
			output.pos = mul(v[i], WVP);
			output.texC = quadTexC[i];
			output.color = input[0].color;
			triStream.Append(output);
		}
	}
}

[maxvertexcount(4)]
void NoBillboardGS(point VS_OUT input[1], inout TriangleStream<GS_OUT> triStream)
{
	if(input[0].type =! EMITTER)
	{
		float4x4 T;
		T[0] = float4(1, 0, 0, 0);
		T[1] = float4(0, 1, 0, 0);
		T[2] = float4(0, 0, 1, 0);
		T[3] = float4(input[0].pos.xyz, 1);
		
		float4x4 RY;
		RY[0] = float4(cos(input[0].ang), 0, sin(input[0].ang),0);
		RY[1] = float4(0, 1, 0, 0);
		RY[2] = float4(-sin(input[0].ang), 0, cos(input[0].ang), 0);
		RY[3] = float4(0, 0, 0, 1);

		float4x4 W = mul(RY, T);
		float4x4 WVP = mul(W, viewProj);

		// Creating Quad
		float halfWidth = 0.5f*input[0].size.x;
		float halfHeight = 0.5f*input[0].size.y;

		float4 v[4];
		v[0] = float4(-halfWidth, 0.0f, -halfHeight, 1.0f);
		v[1] = float4(+halfWidth, 0.0f, -halfHeight, 1.0f);
		v[2] = float4(-halfWidth, 0.0f, +halfHeight, 1.0f);
		v[3] = float4(+halfWidth, 0.0f, +halfHeight, 1.0f);

		GS_OUT output;
		[unroll]
		for(int i = 0; i < 4; ++i)
		{
			output.pos = mul(v[i], WVP);
			output.texC = quadTexC[i];
			output.color = input[0].color;
			triStream.Append(output);
		}
	}
}

float4 DrawPS(GS_OUT input) : SV_TARGET
{
	return input.color * tex.Sample(triLinearSam, input.texC);
}

float4 DrawClampPS(GS_OUT input) : SV_TARGET
{
	return input.color * tex.Sample(clampSampler, input.texC);
}

//Beacon
//
technique10 BeaconSO
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, StreamOutVS() ) );
		SetGeometryShader( gsStreamOut );
		SetPixelShader ( NULL );
		SetDepthStencilState( DisableDepth, 0 );
	}
}

technique10 DrawBeacon
{
	pass P0
	{
		SetVertexShader(	CompileShader( vs_4_0, DrawVS() ) );
		SetGeometryShader(	CompileShader( gs_4_0, DrawGS() ) );
		SetPixelShader (	CompileShader( ps_4_0, DrawPS() ) );
		SetBlendState( AdditiveBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff );
		SetDepthStencilState( NoDepthWrites, 0 );
	}
}


//UpSideDownTwist
//
technique10 UsDTwistSOTech
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, StreamOutVS() ) );
		SetGeometryShader( USDTwistStreamOut );
		SetPixelShader ( NULL );
		SetDepthStencilState( DisableDepth, 0 );
	}
}

technique10 DrawUsDTwist
{
	pass P0
	{
		SetVertexShader(	CompileShader( vs_4_0, UsDTwistVS() ) );
		SetGeometryShader(	CompileShader( gs_4_0, DrawGS() ) );
		SetPixelShader (	CompileShader( ps_4_0, DrawPS() ) );
		SetBlendState( HudBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff );
		SetDepthStencilState( NoDepthWrites, 0 );
	}
}


//CirclePuls
//
technique10 CirclePulsSOTech
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, StreamOutVS() ) );
		SetGeometryShader( CirclePulsStreamOut );
		SetPixelShader ( NULL );
		SetDepthStencilState( DisableDepth, 0 );
	}
}

technique10 DrawCirclePuls
{
	pass P0
	{
		SetVertexShader(	CompileShader( vs_4_0, CirclePulsVS() ) );
		SetGeometryShader(	CompileShader( gs_4_0, DrawGS() ) );
		SetPixelShader (	CompileShader( ps_4_0, DrawPS() ) );
		SetBlendState( AdditiveBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff );
		SetDepthStencilState( NoDepthWrites, 0 );
	}
}


//Sphere
//
technique10 SphereSOTech
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, StreamOutVS() ) );
		SetGeometryShader( SphereStreamOut );
		SetPixelShader ( NULL );
		SetDepthStencilState( DisableDepth, 0 );
	}
}

technique10 DrawSphere
{
	pass P0
	{
		SetVertexShader(	CompileShader( vs_4_0, SphereVS() ) );
		SetGeometryShader(	CompileShader( gs_4_0, DrawGS() ) );
		SetPixelShader (	CompileShader( ps_4_0, DrawPS() ) );
		SetBlendState( AdditiveBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff );
		SetDepthStencilState( NoDepthWrites, 0 );
	}
}

//Fire
//
technique10 FireSOTech
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, StreamOutVS() ) );
		SetGeometryShader( gsFireSO );
		SetPixelShader ( NULL );
		SetDepthStencilState( DisableDepth, 0 );
	}
}

technique10 DrawFire
{
	pass P0
	{
		SetVertexShader(	CompileShader( vs_4_0, FireVS() ) );
		SetGeometryShader(	CompileShader( gs_4_0, DrawGS() ) );
		SetPixelShader (	CompileShader( ps_4_0, DrawPS() ) );
		SetBlendState( AdditiveBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff );
		SetDepthStencilState( NoDepthWrites, 0 );
	}
}

//Electric
//
technique10 ElectricSOTech
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, StreamOutVS() ) );
		SetGeometryShader( gsElectricSO );
		SetPixelShader ( NULL );
		SetDepthStencilState( DisableDepth, 0 );
	}
}

technique10 DrawElectric
{
	pass P0
	{
		SetVertexShader(	CompileShader( vs_4_0, ElectricVS() ) );
		SetGeometryShader(	CompileShader( gs_4_0, DrawGS() ) );
		SetPixelShader (	CompileShader( ps_4_0, DrawPS() ) );
		SetBlendState( AdditiveBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff );
		SetDepthStencilState( NoDepthWrites, 0 );
	}
}

//Aura
//
technique10 AuraSOTech
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, StreamOutVS() ) );
		SetGeometryShader( gsAuraSO );
		SetPixelShader ( NULL );
		SetDepthStencilState( DisableDepth, 0 );
	}
}

technique10 DrawAura
{
	pass P0
	{
		SetVertexShader(	CompileShader( vs_4_0, AuraVS() ) );
		SetGeometryShader(	CompileShader( gs_4_0, NoBillboardGS() ) );
		SetPixelShader (	CompileShader( ps_4_0, DrawClampPS() ) );
		SetBlendState( AdditiveBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff );
		SetDepthStencilState( NoDepthWrites, 0 );
	}
}
#endif