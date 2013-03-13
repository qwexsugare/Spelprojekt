#ifndef PARTICLERENDERER
#define PARTICLERENDERER

#include "ParticleSystemStructs.fx"
#include "UpSideDownTwist.fx"
#include "Beacon.fx"
#include "CirclePuls.fx"
#include "Sphere.fx"
#include "Fire.fx"

Particle StreamOutVS(Particle input)
{
	return input;
}

[maxvertexcount(4)]
void DrawGS(point VS_OUT input[1], inout TriangleStream<GS_OUT> triStream)
{
	if(input[0].type =! EMITTER)
	{
		float3 look = normalize(camPosW.xyz - input[0].pos);
		float3 right = normalize(cross(float3(0,1,0), look));
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
			output.color.g = 1;
			triStream.Append(output);
		}
	}
}

float4 DrawPS(GS_OUT input) : SV_TARGET
{
	//[branch] switch(input.color.g)
	//{
		//case 1:
			return float4(0, 1, 0, 1);
		/*case 2:
			return tex.Sample(triLinearSam, input.texC)*float4(1, 0, 0, 1);
		default:
			return tex.Sample(triLinearSam, input.texC)*float4(1, 1, 1, 1);*/
	//}
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
		SetBlendState( AdditiveBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff );
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
#endif