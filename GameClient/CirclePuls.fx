#ifndef CIRCLEPULS
#define CIRCLEPULS

#include "ParticleSystemStructs.fx"

[maxvertexcount(17)]
void CirclePulsSO(point Particle input[1], inout PointStream<Particle> pStream)
{
	input[0].age += dt;

	if(input[0].type == EMITTER)
	{
		if(input[0].age > 0.5f && isAlive)
		{
			float3 randVe = RandUnitVec3(0.0f);
			randVe.x *= 0.5f;
			randVe.y *= 0.5f;
		
			Particle p;
			p.pos = emitPosW.xyz;
			p.vel = float3(0, 1, 0);
			p.size = size;
			p.age = 0.0f;
			p.type = PARTICLE;
			float angle = 6.28/nrOfSpawnParticles;
			[loop]
			for(int i = 0; i < nrOfSpawnParticles; i++)
			{
				float circleStartRadius = 0.4;

				float circleRange = 1.0;

				float x = circleStartRadius;
				float z = 0;

				float Vx1 = cos(angle*i)*x - sin(angle*i)*z;
				float Vz1 = sin(angle*i)*x + cos(angle*i)*z;

				float Vx2 = cos(angle*i)*circleRange - sin(angle*i)*z;
				float Vz2 = sin(angle*i)*circleRange + cos(angle*i)*z;
				
				p.vel = float3(Vx2, 0, Vz2);
			
				p.pos.x = Vx1;// + emitPosW.x;
				p.pos.y = 0.2;
				p.pos.z = Vz1;// + emitPosW.z;
				pStream.Append(p);
			}

			input[0].age = 0.0f;
		}
		pStream.Append(input[0]);
	}
	else
	{
		if(input[0].age <= 1.5f)
			pStream.Append(input[0]);
	}
}

GeometryShader CirclePulsStreamOut = ConstructGSWithSO(
	CompileShader( gs_4_0, CirclePulsSO() ),
	"POSITION.xyz; VELOCITY.xyz; SIZE.xy; AGE.x; TYPE.x");

//*********
// DrawTech
//*********

VS_OUT CirclePulsVS(Particle input)
{
	VS_OUT output = (VS_OUT)0;

	float t = input.age;
	
	float velx = cos(t)*input.vel.x - sin(t)*input.vel.z;
	float velz = sin(t)*input.vel.x + cos(t)*input.vel.z;


	output.pos.x = input.pos.x + (velx * t);
	output.pos.y = input.pos.y;
	output.pos.z = input.pos.z  + (velz * t);

	output.pos += emitPosW.xyz;

	float opacity = 1.0f - smoothstep(0.0f, 1.0f, t/1.5f);

	output.color = float4(1.0f, 1.0f, 0.5f, opacity);

	output.size = input.size;
	output.type = input.type;


	return output;
}

#endif