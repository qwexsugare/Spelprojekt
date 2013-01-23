#pragma once
#include "menu.h"
class LoreMenu :
	public Menu
{
public:
	LoreMenu(void);
	~LoreMenu(void);
	bool Change;
	int ThisPage;

	bool Minus();
	bool Plus();
	bool MainMenuGameIsDone();
	void Update();
	void ChangeStates();
};

