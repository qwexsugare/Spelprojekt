#pragma once
#include "Menu.h"
class CreateGameMenu : Menu
{
public:
	CreateGameMenu();
	~CreateGameMenu();

	void Init();
	void Update();
	void ChangeStates();

	bool StartGameIsDown();
	bool MainMenuGameIsDone();
};

