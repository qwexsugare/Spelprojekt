#pragma once
#include "Enemy.h"
#include "Path.h"
#include "MeleeAttack.h"
class MindReaver
	:public Enemy
{
private:
		static enum WEAPON_TYPE{NO_WEAPON, RANGED, MELEE, AOE};

	WEAPON_TYPE m_weaponType;
public:
	MindReaver(FLOAT3 _pos);
	~MindReaver(void);

	bool m_isHeadingBack;
	FLOAT3 m_origPos; 
	float m_allowedMovement;
	virtual void attackHero(int heroIndex);
	void updateSpecificUnitEntity(float dt);
	void tellBossToDropGold();
	unsigned short getWeaponType();
};

