#ifndef FIRE
#define FIRE

#include "ParticleSystemStructs.fx"

[maxvertexcount(17)]
void FireSO(point Particle input[1], inout PointStream<Particle> pStream)
{
	input[0].age += dt;

	if(input[0].type == EMITTER)
	{
		if(input[0].age > 0.07f)
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

			float angle = 0;//0.252f;

			//randVe.x = 0;
			randVe.z = 1;
			//randVe.y = 1;

			// use local variables to find transformed components
			float Vx1 = cos(angle)*randVe.x - sin(angle)*abs(randVe.z);
			float Vz1 = sin(angle)*randVe.x + cos(angle)*abs(randVe.z);

			float Vx2 = cos(angle)*Vx1 - sin(angle)*abs(Vz1);
			float Vz2 = sin(angle)*Vx1 + cos(angle)*abs(Vz1);

			
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
	"POSITION.xyz; VELOCITY.xyz; SIZE.xy; AGE.x; TYPE.x;");

//*********
// DrawTech
//*********

VS_OUT FireVS(Particle input)
{
	VS_OUT output = (VS_OUT)0;

	float t = input.age;

	output.pos = input.pos + input.vel*(t/2);

	output.vel = input.vel;

	float opacity = 1;//t*2 - t*t;
	output.color = tintColor;//float4(1.0f, 1.0f, 1.0f, opacity);

	output.size = input.size;
	output.type = input.type;

	return output;
}

#endif