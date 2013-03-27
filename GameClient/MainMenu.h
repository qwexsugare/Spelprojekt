#pragma once
#include "Menu.h"

class MainMenu : Menu
{
public:
	MainMenu();
	~MainMenu();

	void Update();

	bool createGameIsDown();
	bool JoinGameIsDown();
	bool SettingsIsDown();
	bool LoreIsDown();
	bool CreditsIsDown();
	bool ExitIsDown();
private:
	string m_graphicstext;
};

