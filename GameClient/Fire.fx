#ifndef FIRE
#define FIRE

#include "ParticleSystemStructs.fx"

[maxvertexcount(17)]
void FireSO(point Particle input[1], inout PointStream<Particle> pStream)
{
	input[0].age += dt;

	if(input[0].type == EMITTER)
	{
		if(input[0].age > 0.01f)
		{
			float3 randVe = RandUnitVec3(0.0f);
			randVe.x *= 0.5f;
			randVe.y *= 0.5f;
		
			Particle p;
			p.pos = emitPosW.xyz;
			p.pos.y = 0.5;
			p.vel = 0.5f*randVe;
			p.size = float2(0.2, 0.2);//float2(15.0f, 15.0f);
			p.age = 0.0f;
			p.type = PARTICLE;

			float angle = 1.0f;

			// use local variables to find transformed components
			float Vx1 = cos(angle*2.5)*randVe.x - sin(angle*2.5)*randVe.z;
			float Vz1 = sin(angle*0.75)*randVe.x + cos(angle*0.75)*randVe.z;
			float cone = 0.1f;
			p.vel = (float3(Vx1, abs(Vz1), 0));

			pStream.Append(p);

			input[0].age = 0.0f;
		}
		pStream.Append(input[0]);
	}
	else
	{
		if(input[0].age <= 0.5f)
			pStream.Append(input[0]);
	}
}

GeometryShader gsFireSO = ConstructGSWithSO(
	CompileShader( gs_4_0, FireSO() ),
	"POSITION.xyz; VELOCITY.xyz; SIZE.xy; AGE.x; TYPE.x");

//*********
// DrawTech
//*********

VS_OUT FireVS(Particle input)
{
	VS_OUT output;

	float t = input.age;

	output.pos = input.pos + input.vel*t;

	float opacity = 1;//t*2 - t*t;
	output.color = float4(1.0f, 1.0f, 1.0f, opacity);

	output.size = input.size;
	output.type = input.type;

	return output;
}

#endif