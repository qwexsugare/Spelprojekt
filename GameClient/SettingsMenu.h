#pragma once
#include "menu.h"
class SettingsMenu :
	public Menu
{
public:
	SettingsMenu(void);
	~SettingsMenu(void);
	
	void Update();
	bool MainMenuGameIsDown();
	bool SaveSettingsIsDown();
};

