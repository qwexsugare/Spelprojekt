#pragma once
#include "Menu.h"
class CreditsMenu : Menu
{
public:
	CreditsMenu();
	~CreditsMenu();

	void Init();
	void Update();
	void ChangeStates();

	bool MainMenuGameIsDone();
};

