#ifndef UPSIDEDOWNTWIST
#define UPSIDEDOWNTWIST

#include "ParticleSystemStructs.fx"

[maxvertexcount(17)]
void UsDTwistSO(point Particle input[1], inout PointStream<Particle> pStream)
{
	input[0].age += dt;

	if(input[0].type == EMITTER)
	{
		if(input[0].age > 2.0f)
		{
			float3 randVe = RandUnitVec3(0.0f);
			randVe.x *= 0.5f;
			randVe.y *= 0.5f;
		
			Particle p;
			p.pos = float3(0, -1, 0);
			p.vel = float3(0, 1, 0);//4.0f*randVe;
			p.size = float2(0.6, 0.6);//float2(15.0f, 15.0f);
			p.age = 0.0f;
			p.type = PARTICLE;
			float angle = 6.28/8;
			[loop]
			for(int i = 0; i < 8; i++)
			{
				float x = 0.5;
				float z = 0;
				// use local variables to find transformed components
				float Vx1 = cos(angle*i)*x - sin(angle*i)*z;
				float Vz1 = sin(angle*i)*x + cos(angle*i)*z;
				// store results thru the pointer
			
				
				p.pos = (float3(Vx1 , 0, Vz1));
				pStream.Append(p);
			}

			input[0].age = 0.0f;
		}
		pStream.Append(input[0]);
	}
	else
	{
		if(input[0].age <= 2.0f)
			pStream.Append(input[0]);
	}
}

GeometryShader USDTwistStreamOut = ConstructGSWithSO(
	CompileShader( gs_4_0, UsDTwistSO() ),
	"POSITION.xyz; VELOCITY.xyz; SIZE.xy; AGE.x; TYPE.x");

//*********
// DrawTech
//*********

VS_OUT UsDTwistVS(Particle input)
{
	VS_OUT output;

	float t = input.age;

	input.vel = normalize(input.vel);
	
	

	float x = input.pos.x;
	float z = input.pos.z;
	float Vx1 = cos(input.age/2)*x - sin(input.age/2)*z;
	float Vz1 = sin(input.age/2)*x + cos(input.age/2)*z;

	float3 trollVec = input.vel - float3(Vx1, 0, Vz1);
	input.vel = (0, 1, 0);
	output.pos = input.pos + (input.vel*(input.age));

	float maxAge = 2;

	//t += 2/2;

	float opacity = t*2 - t*t;

	//float opacity = smoothstep(0.0f, 1.0f, t/1.0f);

	output.color = float4(1.0f, 1.0f, 1.0f, opacity);

	output.size = input.size;
	output.type = input.type;


	return output;
}

#endif