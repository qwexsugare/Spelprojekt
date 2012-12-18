#pragma once
#include "Menu.h"
class HudMenu : Menu
{
public:
	HudMenu();
	~HudMenu();
	int m_Time;
	int m_Delay;
	int m_DelayTime;
	void Init();
	void Update();
	void ChangeStates();
};

