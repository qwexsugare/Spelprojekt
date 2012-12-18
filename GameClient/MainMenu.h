#pragma once
#include "Menu.h"
class MainMenu : Menu
{
public:
	MainMenu();
	~MainMenu();

	void Init();
	void Update();
	void ChangeStates();
	bool CreateGameIsDown();
	bool JoinGameIsDone();
	bool SettingsIsDone();
	bool LoreIsDone();
	bool CreditsIsDone();
	bool ExitIsDone();
};

