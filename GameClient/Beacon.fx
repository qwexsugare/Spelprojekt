#ifndef BEACON
#define BEACON

#include "ParticleSystemStructs.fx"

[maxvertexcount(17)]
void StreamOutGS(point Particle input[1], inout PointStream<Particle> pStream)
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

GeometryShader gsStreamOut = ConstructGSWithSO(
	CompileShader( gs_4_0, StreamOutGS() ),
	"POSITION.xyz; VELOCITY.xyz; SIZE.xy; AGE.x; TYPE.x;");

//*********
// DrawTech
//*********

VS_OUT DrawVS(Particle input)
{
	VS_OUT output = (VS_OUT)0;

	float t = input.age;

	//output.angle = angle + 3.14;

	output.vel = input.vel;

	output.pos = input.pos + (input.vel*(t*speed));//0.5f*(t*t*accel);//0.5f*t*t*accel + t*input.vel + input.pos;
	//float opacity = 1.0f - smoothstep(0.0f, 1.0f, t/10.0f);
	
	float opp = 1.0/lifeTime;
	float opacity = 1;//1-(opp*t);
	//float opacity = t*2 - t*t;
	output.color = tintColor;//float4(tintColor.r, tintColor.g, tintColor.b, tintColor.a);

	output.size = input.size;
	output.type = input.type;

	output.vel = input.vel;


	return output;
}

#endif