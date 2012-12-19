#pragma once
#include "Menu.h"
class JoinGameMenu : Menu
{
public:
	JoinGameMenu();
	~JoinGameMenu();

	void Update();

	bool StartGameIsDown();
	bool MainMenuGameIsDown();
};

