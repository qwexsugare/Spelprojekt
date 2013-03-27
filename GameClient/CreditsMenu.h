#pragma once
#include "menu.h"
class CreditsMenu :
	public Menu
{
public:
	CreditsMenu(void);
	~CreditsMenu(void);

	void Update();
	bool MainMenuGameIsDown();
private:
	string m_graphicstext;
};

