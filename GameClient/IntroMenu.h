#pragma once
#include "menu.h"
#include "IntroMenu.h"
class IntroMenu :
	public Menu
{
public:
	IntroMenu(void);
	~IntroMenu(void);

	void Update(float _dt);
	bool MainMenuGameIsDown();
	float m_counter;
private:
	bool firstRun;
};

