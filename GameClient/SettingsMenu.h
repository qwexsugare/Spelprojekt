#pragma once
#include "Menu.h"
class SettingsMenu : Menu
{
public:
	SettingsMenu();
	~SettingsMenu();

	void Init();
	void Update();
	void ChangeStates();
	bool MainMenuGameIsDone();
	bool SaveSettingsIsDone();
};

