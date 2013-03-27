#pragma once
#include "menu.h"
class ScoreMenu :
	public Menu
{
public:
	ScoreMenu(void);
	~ScoreMenu(void);
		
	void Update();
	bool MainMenuGameIsDown();
private:
	string m_graphicstext;
};

