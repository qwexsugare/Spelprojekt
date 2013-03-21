#pragma once
#include "Enemy.h"
#include "Path.h"
#include "MeleeAttack.h"
class BigBadBoss
	:public Enemy
{
private:
	static enum WEAPON_TYPE{NO_WEAPON, RANGED, MELEE, AOE};

	WEAPON_TYPE m_weaponType;
public:
	BigBadBoss::BigBadBoss(FLOAT3 _pos);
	~BigBadBoss(void);
	FLOAT3 m_origPos; 
	bool m_isHeadingBack;
	float m_allowedMovement;
	virtual void attackHero(int heroIndex);
	void updateSpecificUnitEntity(float dt);
	void tellBossToDropGold();
	unsigned short getWeaponType();
};

