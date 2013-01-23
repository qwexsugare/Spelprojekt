#pragma once
#include "menu.h"
class JoinGameMenu :
	public Menu
{
public:
	JoinGameMenu(void);
	~JoinGameMenu(void);

	void Update();
	bool StartGameIsDown();
	bool MainMenuGameIsDone();
};

