#ifndef BEACON
#define BEACON

#include "ParticleSystemStructs.fx"

[maxvertexcount(17)]
void StreamOutGS(point Particle input[1], inout PointStream<Particle> pStream)
{
	input[0].age += dt;

	if(input[0].type == EMITTER)
	{
		if(input[0].age > 0.2f)
		{
			float3 randVe = RandUnitVec3(0.0f);
			randVe.x *= 0.5f;
			randVe.y *= 0.5f;
		
			Particle p;
			p.pos = emitPosW.xyz;
			p.vel = 4.0f*randVe;
			p.size = float2(1.0, 1.0);//float2(15.0f, 15.0f);
			p.age = 0.0f;
			p.type = PARTICLE;

			pStream.Append(p);

			input[0].age = 0.0f;
		}
		pStream.Append(input[0]);
	}
	else
	{
		if(input[0].age <= 10.0f)
			pStream.Append(input[0]);
	}
}

GeometryShader gsStreamOut = ConstructGSWithSO(
	CompileShader( gs_4_0, StreamOutGS() ),
	"POSITION.xyz; VELOCITY.xyz; SIZE.xy; AGE.x; TYPE.x");

//*********
// DrawTech
//*********

VS_OUT DrawVS(Particle input)
{
	VS_OUT output;

	float t = input.age;

	output.pos = input.pos +  0.5f*(t*t*accel);//0.5f*t*t*accel + t*input.vel + input.pos;
	float opacity = 1.0f - smoothstep(0.0f, 1.0f, t/10.0f);

	output.color = float4(1.0f, 1.0f, 1.0f, opacity);

	output.size = input.size;
	output.type = input.type;


	GS_OUT gs = (GS_OUT)0;

	gs.pos = float4(0, input.pos.y + (input.age/100), 0, 1);
	//gs.color = float4(1, 1, 1, 1);//float4(input.age/100, input.age/100, input.age/10, 1);

	return output;
}

#endif