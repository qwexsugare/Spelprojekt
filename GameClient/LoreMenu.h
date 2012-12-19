#pragma once
#include "Menu.h"
class LoreMenu : Menu
{
private:
	bool m_change;
	int m_thisPage;
public:
	LoreMenu();
	~LoreMenu();


	bool Minus();
	bool Plus();
	void Update();
	void ChangeStates();
};

