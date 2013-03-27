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
	float m_time;
	bool forthRun;
private:
	bool firstRun;
	bool secondRun;
	bool thirdRun;
	string m_graphicstext;
};

