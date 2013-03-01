#pragma once
#include "menu.h"
#include "TextInput.h"
#include "TextLabel.h"

class CreateGameMenu :
	public Menu
{
public:
	CreateGameMenu(void);
	~CreateGameMenu(void);

	void Update(float _dt);
	bool StartGameIsDown();
	bool MainMenuGameIsDown();
	bool MainWriteGameIsDown();
	bool MainWriteIPIsDown();
	bool MainWriteNameIsDown();
	bool LevelOneIsDown();
	string getIP();
	string getPort();
	string getPlayerName();
private:
	vector<TextInput*> m_Label;
	TextLabel* m_IPLabel;
	bool	m_WriteIP,
			m_WriteName,
			m_WriteGame;
};

