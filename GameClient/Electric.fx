#ifndef ELECTRIC
#define ELECTRIC

#include "ParticleSystemStructs.fx"

[maxvertexcount(17)]
void ElectricSO(point Particle input[1], inout PointStream<Particle> pStream)
{
	input[0].age += dt;

	if(input[0].type == EMITTER)
	{
		if(input[0].age > emitRate)
		{
			float3 randVe = RandUnitVec3(0.0f);
			randVe.x *= 0.5f;
			randVe.y *= 0.5f;
		
			Particle p;
			p.pos = emitPosW.xyz;
			p.pos.y = 0.5;
			p.vel = 0.5f*randVe;
			p.size = size;
			p.age = 0.0f;
			p.type = PARTICLE;

			pStream.Append(p);

			input[0].age = 0.0f;
		}
		pStream.Append(input[0]);
	}
	else
	{
		if(input[0].age <= lifeTime)
			pStream.Append(input[0]);
	}
}

GeometryShader gsElectricSO = ConstructGSWithSO(
	CompileShader( gs_4_0, ElectricSO() ),
	"POSITION.xyz; VELOCITY.xyz; SIZE.xy; AGE.x; TYPE.x;");

//*********
// DrawTech
//*********

VS_OUT ElectricVS(Particle input)
{
	VS_OUT output = (VS_OUT)0;

	float t = input.age;



	float3 up = float3(0, 0, 1);

	float angle = atan2(up.z, up.x) - atan2(input.vel.z, input.vel.x);

	//float angle = dot(up, normalize(input.vel)); 

	output.vel = input.vel;


	output.pos.xyz = emitPosW.xyz + (((input.vel)*(offset + (t*speed))));
	//output.pos.y = emitPosW.y;

	float opp = 1.0/lifeTime;
	float opacity = 1-(opp*t);
	output.color = float4(1.0f, 1.0f, 1.0f, opacity);

	output.size = input.size;
	output.type = input.type;

	return output;
}

#endif