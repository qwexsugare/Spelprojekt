#pragma once

#include "clientskilleffect.h"
#include "ClientEntityHandler.h"

class ChurchPenetratedClientSkillEffect : public ClientSkillEffect
{
private:
	ParticleEngine* pe;
	float timer;
	bool inited;
	int id;
public:
	ChurchPenetratedClientSkillEffect(unsigned int _id, FLOAT3 _position);
	~ChurchPenetratedClientSkillEffect();

	void update(float _dt);
	bool getActive();
};

