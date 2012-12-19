#pragma once
#include "Menu.h"
class HudMenu : Menu
{
private:
	int m_Time;
	int m_Delay;
	int m_DelayTime;
public:
	HudMenu();
	~HudMenu();

	void Update();
};

