#pragma once
#include "Menu.h"
class JoinGameMenu : Menu
{
public:
	JoinGameMenu();
	~JoinGameMenu();

	void Init();
	void Update();
	void ChangeStates();

	bool StartGameIsDown();
	bool MainMenuGameIsDone();
};

