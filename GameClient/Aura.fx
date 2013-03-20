#ifndef AURA
#define AURA

#include "ParticleSystemStructs.fx"

[maxvertexcount(17)]
void AuraSO(point Particle input[1], inout PointStream<Particle> pStream)
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
			p.vel.y = 0;
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

GeometryShader gsAuraSO = ConstructGSWithSO(
	CompileShader( gs_4_0, AuraSO() ),
	"POSITION.xyz; VELOCITY.xyz; SIZE.xy; AGE.x; TYPE.x;");

//*********
// DrawTech
//*********

VS_OUT AuraVS(Particle input)
{
	VS_OUT output = (VS_OUT)0;

	float t = input.age;
	

	output.vel = input.vel;

	output.ang = ((6.28f/lifeTime) * t) * speed;

	output.pos.xyz = emitPosW.xyz;
	output.pos.y = 0.02f;
	
	float opacity = sin((float(180.0f/lifeTime) * t) * 3.14f/180.0f);

	output.color = tintColor;
	output.color.a = opacity * tintColor.a;

	output.size = input.size;
	output.type = input.type;

	return output;
}

#endif