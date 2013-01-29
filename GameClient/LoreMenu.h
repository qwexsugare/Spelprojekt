#pragma once
#include "menu.h"
#include "TextLabel.h"
#include <sstream>
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
	bool MainMenuIsDown();
	void Update();
	void ChangeStates();

private:
	vector<TextLabel*> m_Label;
};

