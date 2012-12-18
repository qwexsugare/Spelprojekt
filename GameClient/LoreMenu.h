#pragma once
#include "Menu.h"
class LoreMenu : Menu
{
public:
	LoreMenu();
	~LoreMenu();
	bool Change;
	//int Delay;
	//int DelayTime;
	int ThisPage;
	bool Minus();
	bool Plus();
	bool MainMenuGameIsDone();
	void Init();
	void Update();
	void ChangeStates();
};

