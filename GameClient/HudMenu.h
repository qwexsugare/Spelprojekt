#pragma once
#include "menu.h"
class HudMenu :
	public Menu
{
public:
	HudMenu(void);
	~HudMenu(void);

	void Update(float _dt);

private:
	int m_Time, m_NumberOfSkills, m_SkillValue;
	float m_SkillHud;
	int m_Delay;
	int m_DelayTime;
};

