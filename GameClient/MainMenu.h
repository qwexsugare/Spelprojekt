#pragma once
#include "Menu.h"

class MainMenu : Menu
{
public:
	MainMenu();
	~MainMenu();

	void Update();

	bool createGameIsDown();
};

