#ifndef UPSIDEDOWNTWIST
#define UPSIDEDOWNTWIST

#include "ParticleSystemStructs.fx"

[maxvertexcount(17)]
void UsDTwistSO(point Particle input[1], inout PointStream<Particle> pStream)
{
	input[0].age += dt;

	if(input[0].type == EMITTER)
	{
		if(input[0].age > emitRate && isAlive)
		{
			float3 randVe = RandUnitVec3(0.0f);
			randVe.x *= 0.5f;
			randVe.y *= 0.5f;
		
			Particle p;
			p.vel = 4.0f*randVe;
			p.size = size;
			p.age = 0.0f;
			p.type = PARTICLE;

			p.pos = emitPosW;
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

GeometryShader USDTwistStreamOut = ConstructGSWithSO(
	CompileShader( gs_4_0, UsDTwistSO() ),
	"POSITION.xyz; VELOCITY.xyz; SIZE.xy; AGE.x; TYPE.x;");

//*********
// DrawTech
//*********

VS_OUT UsDTwistVS(Particle input)
{
	VS_OUT output = (VS_OUT)0;

	float t = input.age;

	input.vel = normalize(input.vel);
	float maxScale = 3;
	float radScale = (lifeTime/2.5f) - (t/2.5f);
	float angle = t*4;


	float4x4 RY;
	RY[0] = float4(cos(angle), 0, sin(angle),0);
	RY[1] = float4(0, 1, 0, 0);
	RY[2] = float4(-sin(angle), 0, cos(angle), 0);
	RY[3] = float4(0, 0, 0, 1);



	output.pos = mul(float4((input.vel*radScale), 1), RY);
	output.pos += input.pos;
	output.pos.y = 0.3f;

	output.vel = input.vel;


	float opacity = sin((float(180.0f/lifeTime) * t) * 3.14f/180.0f) + (input.vel.x);


	output.color = float4(input.vel.x, 0, 0, opacity);

	output.size = size * (t/(lifeTime*0.7)) + 0.1f;
	output.type = input.type;


	return output;
}

#endif