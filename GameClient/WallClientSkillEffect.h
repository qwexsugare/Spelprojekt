#pragma once

#include "clientskilleffect.h"
#include "ClientEntityHandler.h"

class WallClientSkillEffect : public ClientSkillEffect
{
private:
	Model *m_model;
	float m_lifetime;
	Mesh* m_weapon;
	UINT m_masterId;
public:
	WallClientSkillEffect(unsigned int _masterId, FLOAT3 _position);
	~WallClientSkillEffect();

	void update(float _dt);
	bool getActive();
};

