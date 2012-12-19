#pragma once
#include "Menu.h"
class CreateGameMenu : Menu
{
public:
	CreateGameMenu();
	~CreateGameMenu();

	void Update();

	bool StartGameIsDown();
	bool MainMenuGameIsDown();
};

