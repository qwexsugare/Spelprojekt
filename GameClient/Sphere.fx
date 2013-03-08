#ifndef SPHERE
#define SPHERE

#include "ParticleSystemStructs.fx"

[maxvertexcount(17)]
void SphereSO(point Particle input[1], inout PointStream<Particle> pStream)
{
	input[0].age += dt;

	if(input[0].type == EMITTER)
	{
		if(input[0].age > 0.20f)
		{
			
		
			Particle p;
			p.pos = emitPosW.xyz;
			p.vel = float3(0, 1, 0);
			p.size = size;
			p.age = 0.0f;
			p.type = PARTICLE;
			float angle = 6.28/nrOfSpawnParticles;

			float3 randVe = RandUnitVec3(0);
			randVe.x *= 0.5f;
			randVe.y *= 0.5f;

			float circleRange = 1.0;

			float x = circleRange;
			float z = 0;

			float Vx1 = cos(randVe.y)*x - sin(randVe.y)*z;
			float Vz1 = sin(randVe.y)*x + cos(randVe.y)*z;

			float Vx2 = cos(randVe.x)*x - sin(randVe.x)*z;
			float Vz2 = sin(randVe.x)*x + cos(randVe.x)*z;
				
			p.vel = float3(Vx2, 0, Vz2);
			
			p.pos.x = Vx1;// + emitPosW.x;
			p.pos.y = Vz1;
			p.pos.z = Vz2;// + emitPosW.z;
			pStream.Append(p);

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

GeometryShader SphereStreamOut = ConstructGSWithSO(
	CompileShader( gs_4_0, SphereSO() ),
	"POSITION.xyz; VELOCITY.xyz; SIZE.xy; AGE.x; TYPE.x");

//*********
// DrawTech
//*********

VS_OUT SphereVS(Particle input)
{
	VS_OUT output = (VS_OUT)0;

	float t = input.age;

	
	float velx = cos(t)*input.vel.x - sin(t)*input.vel.z;
	float velz = sin(t)*input.vel.x + cos(t)*input.vel.z;



	output.pos.x += input.pos.x + (velx * t);
	output.pos.y += input.pos.y + (velz * t);
	output.pos.z += input.pos.z + (velz * t);

	output.pos += emitPosW.xyz;

	float opacity = 1.0f - smoothstep(0.0f, 1.0f, t/1.5f);

	output.color = float4(1.0f, 1.0f, 1.0f, opacity);

	output.size = input.size;
	output.type = input.type;


	return output;
}

#endif